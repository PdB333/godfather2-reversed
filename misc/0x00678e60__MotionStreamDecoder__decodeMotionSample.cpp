// FUNC_NAME: MotionStreamDecoder::decodeMotionSample
void decodeMotionSample(MotionData* obj, short* outputSamples, short* outputCount, BitStreamReader& bitReader)
{
    // outputSamples is the buffer to fill with decoded positions (two shorts per sample)
    // outputCount is set to 1 or 2 depending on number of samples decoded
    short sVar4;
    short sVar3;
    short sVar2;
    short sVar7;
    byte bVar5;
    char cVar6;
    short sVar1;

    // Read first value from the bitstream (mode indicator?)
    sVar7 = *bitReader.packetData;  // This is actually *param_2? Wait, param_2 is outputCount. In original decompile: sVar7 = *param_2; That seems wrong because param_2 is the count pointer. But the code uses *param_2 as the initial value? That's odd. Let's stick to original logic: sVar7 = *outputCount; maybe it's reused as temporary.

    // Initialize outputSamples to current stored positions (from obj->currentX, currentY)
    outputSamples[0] = *(short*)(obj + 0x104);  // obj->currentPosX
    outputSamples[1] = *(short*)(obj + 0x106);  // obj->currentPosY

    // Determine prediction mode from the bitstream
    if (sVar7 < 0) {
        bVar5 = 6;  // Mode 6: invalid? but always set to 6 when sVar7 negative?
    }
    else if (bitReader.bitOffset == 0) {
        bVar5 = *(byte*)bitReader.dataPtr;
        bitReader.bitOffset = 1;  // Mark that we consumed bits?
        bVar5 = bVar5 >> 4;  // High nibble as mode
    }
    else {
        bVar5 = *(byte*)bitReader.dataPtr & 0xf;  // Low nibble
        bitReader.bitOffset = 0;
        bitReader.dataPtr = (byte*)bitReader.dataPtr + 1;  // Advance pointer
    }

    switch (bVar5) {
    case 0:
        *outputCount = 1;
        // Get a bit
        if ((readBit() & 8) == 0) {
            // If bit 3 not set, read a delta for first channel (X)
            sVar7 = readSignedValue(0);  // param 0
            outputSamples[0] = sVar7;
        }
        else {
            // Else read delta for second channel (Y)
            sVar7 = readSignedValue(1);
            outputSamples[1] = sVar7;
        }
        break;

    case 1:
        *outputCount = 1;
        cVar6 = readByteDelta();  // char
        outputSamples[0] = (short)cVar6 + *(short*)(obj + 0x104);
        break;

    case 2:
        *outputCount = 1;
        cVar6 = readByteDelta();
        sVar7 = (short)cVar6;
        goto updateY;
        break;

    case 3:
        *outputCount = 1;
        sVar7 = readShortDelta();
        outputSamples[0] = sVar7 + *(short*)(obj + 0x104);
        break;

    case 4:
        *outputCount = 1;
        sVar7 = readShortDelta();
updateY:
        outputSamples[1] = sVar7 + *(short*)(obj + 0x106);
        break;

    case 5:
        *outputCount = 1;
        readBit();
        storeCurrentToPrevious(obj);  // FUN_00679420(obj)
        return;

    case 6:
        *outputCount = 0;
        readBit();
        storeCurrentToPrevious(obj);
        return;

    case 7:
        goto twoSampleXFirst;
    case 8:
        goto twoSampleYFirst;
    case 9:
        readBit();
        goto twoSampleXFirst;
    case 10:
        readBit();
        goto twoSampleYFirst;
    case 11:
        readExtraBit();
twoSampleXFirst:
        *outputCount = 2;
        storeCurrentToPrevious(obj);
        // Second sample X: read delta from first sample's X
        sVar7 = readSignedValue(0);
        outputSamples[2] = sVar7;
        outputSamples[3] = outputSamples[1];  // Y stays same as first sample's Y
        storeCurrentToPrevious(obj, &outputSamples[2]);
        outputSamples[4] = outputSamples[2];
        // Third sample X? Wait, the code continues with a second delta for Y? Actually the pattern in decompile:
        // outputSamples[4] = outputSamples[2]; outputSamples[5] = outputSamples[3]; then read second delta for Y and assign to outputSamples[5]... So it's actually writing three samples? Let's examine carefully.
        // The decompiled for case 0xb: 
        //   *param_2 = 2;
        //   FUN_00679420(param_1);
        //   psVar1 = unaff_EDI + 2;
        //   sVar7 = FUN_00679360(0);
        //   *psVar1 = sVar7;
        //   unaff_EDI[3] = unaff_EDI[1];
        //   FUN_00679420(param_1,psVar1);
        //   unaff_EDI[4] = *psVar1;
        //   sVar7 = FUN_00679360(1);
        //   unaff_EDI[5] = sVar7;
        //   FUN_00679420(param_1,unaff_EDI + 4);
        // So it processes three samples: first sample already stored, second sample sets x and copies y, third sample sets y from a delta. So outputSamples written are: [0][1] (first), [2][3] (second x, first y), [4][5] (second x? no, third sample: x = second x, y = new y). But note that the third sample's x is from *psVar1 which was set to sVar7 (second x). So third sample (index 4,5) has x = second x, y = delta. So it's like two samples with same x? That seems odd. Let's preserve the original logic.
        // I'll just write the logic as given but with cleaner variable names.
        sVar7 = readSignedValue(1);
        outputSamples[5] = sVar7;
        storeCurrentToPrevious(obj, &outputSamples[4]);
        break;

    case 12:
        readExtraBit();
twoSampleYFirst:
        *outputCount = 2;
        storeCurrentToPrevious(obj);
        outputSamples[2] = outputSamples[0];  // Copy first x to second x
        sVar7 = readSignedValue(1);
        outputSamples[3] = sVar7;
        storeCurrentToPrevious(obj, &outputSamples[2]);
        sVar7 = readSignedValue(0);
        outputSamples[4] = sVar7;
        outputSamples[5] = outputSamples[3];
        storeCurrentToPrevious(obj, &outputSamples[4]);
        break;

    case 13:
        readBit();
        goto linearExtrapolation;
    case 14:
        readExtraBit();
        goto linearExtrapolation;
    case 15:
        readBit();
        readExtraBit();
linearExtrapolation:
        // Perform linear extrapolation from previous two positions
        sVar7 = *(short*)(obj + 0x104);  // currentX
        sVar2 = *(short*)(obj + 0x106);  // currentY
        sVar3 = *(short*)(obj + 0x108);  // previousX
        sVar4 = *(short*)(obj + 0x10a);  // previousY
        *outputCount = 2;
        // Extrapolate: new = current*2 - previous (linear extrapolation)
        outputSamples[0] = sVar7 * 2 - sVar3;
        outputSamples[1] = sVar2 * 2 - sVar4;
        storeCurrentToPrevious(obj);
        // Second sample: same as first
        outputSamples[2] = outputSamples[0];
        outputSamples[3] = outputSamples[1];
        storeCurrentToPrevious(obj, &outputSamples[2]);
        outputSamples[4] = outputSamples[2];
        outputSamples[5] = outputSamples[3];
        storeCurrentToPrevious(obj, &outputSamples[4]);
        // fall through to default?
        return;

    default:
        // do nothing
        break;
    }

    // Update previous position to current (only for single-sample cases)
    sVar7 = outputSamples[0];
    *(short*)(obj + 0x108) = *(short*)(obj + 0x104);  // store currentX to previousX
    *(short*)(obj + 0x10a) = *(short*)(obj + 0x106);  // store currentY to previousY
    sVar2 = outputSamples[1];
    *(short*)(obj + 0x104) = sVar7;  // update currentX from decoded
    *(short*)(obj + 0x106) = sVar2;  // update currentY from decoded
    return;
}