// FUNC_NAME: BitStreamDecoder::decodeTwoValues
void BitStreamDecoder::decodeTwoValues(void* decompContext, short* outputValues)
{
    // decompContext: pointer to decompression state, with fields at offsets:
    // +0x104: prevDelta1 (short)
    // +0x106: prevDelta2 (short)
    // +0x108: lastDecoded1 (short)
    // +0x10a: lastDecoded2 (short)
    // BitReaderState* g_bitReader (global or in ESI register)
    // BitReaderState structure: offset 0: byte* bufferPtr, offset 4: short nibbleFlag

    char cVar1;
    byte bVar2;
    short sVar3;
    uint modeBits;
    uint uVar4;
    byte *pbVar5;

    // First output value
    uVar4 = (modeBits = /*in_EAX*/) & 3; // Extracted mode bits from EAX (lower 2 bits)
    if (uVar4 == 1) {
        if (g_bitReader->nibbleFlag == 0) {
            bVar2 = *g_bitReader->bufferPtr;
            g_bitReader->nibbleFlag = 1;
            bVar2 = bVar2 >> 4; // high nibble
        } else {
            bVar2 = *g_bitReader->bufferPtr & 0xf; // low nibble
            g_bitReader->nibbleFlag = 0;
            g_bitReader->bufferPtr++;
        }
        outputValues[0] = (short)bVar2 + *(short*)(decompContext + 0x104) - 8; // delta decode
    } else if (uVar4 == 2) {
        if (g_bitReader->nibbleFlag == 0) {
            cVar1 = *(char*)g_bitReader->bufferPtr;
            g_bitReader->bufferPtr++;
        } else {
            cVar1 = *(char*)g_bitReader->bufferPtr;
            pbVar5 = (byte*)((char*)g_bitReader->bufferPtr + 1);
            g_bitReader->bufferPtr = pbVar5;
            cVar1 = (*pbVar5 >> 4) + cVar1 * 0x10; // combine nibbles
        }
        if ((unsigned short)((short)cVar1 + 8) < 0x10) {
            sVar3 = decodeHuffmanValue(0); // FUN_00679360
            outputValues[0] = sVar3;
        } else {
            outputValues[0] = *(short*)(decompContext + 0x104) + (short)cVar1;
        }
    } else if (uVar4 == 3) {
        sVar3 = decodeDirectValue(); // FUN_006792b0
        outputValues[0] = sVar3 + *(short*)(decompContext + 0x104);
    }
    // Update previous value buffer for first output
    *(short*)(decompContext + 0x108) = *(short*)(decompContext + 0x104);
    // Now decode second output with mode from bits 2-3
    uVar4 = (modeBits & 0xffff) >> 2 & 3;
    *(short*)(decompContext + 0x104) = outputValues[0];
    if (uVar4 == 1) {
        if (g_bitReader->nibbleFlag == 0) {
            bVar2 = *g_bitReader->bufferPtr;
            g_bitReader->nibbleFlag = 1;
            bVar2 = bVar2 >> 4;
        } else {
            bVar2 = *g_bitReader->bufferPtr & 0xf;
            g_bitReader->nibbleFlag = 0;
            g_bitReader->bufferPtr++;
        }
        sVar3 = (short)bVar2 + *(short*)(decompContext + 0x106) - 8;
    } else if (uVar4 == 2) {
        if (g_bitReader->nibbleFlag == 0) {
            cVar1 = *(char*)g_bitReader->bufferPtr;
            g_bitReader->bufferPtr++;
        } else {
            cVar1 = *(char*)g_bitReader->bufferPtr;
            pbVar5 = (byte*)((char*)g_bitReader->bufferPtr + 1);
            g_bitReader->bufferPtr = pbVar5;
            cVar1 = (*pbVar5 >> 4) + cVar1 * 0x10;
        }
        if ((unsigned short)((short)cVar1 + 8) <= 0xf) {
            sVar3 = decodeHuffmanValue(1); // second call with parameter 1
        } else {
            outputValues[1] = *(short*)(decompContext + 0x106) + (short)cVar1;
            goto updateState;
        }
    } else {
        if (uVar4 != 3) goto updateState;
        sVar3 = decodeDirectValue();
        sVar3 = sVar3 + *(short*)(decompContext + 0x106);
    }
    outputValues[1] = sVar3;

updateState:
    // Update previous value buffer for second output
    *(short*)(decompContext + 0x10a) = *(short*)(decompContext + 0x106);
    *(short*)(decompContext + 0x106) = outputValues[1];
    return;
}