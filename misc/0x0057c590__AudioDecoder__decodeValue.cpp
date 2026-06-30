// FUNC_NAME: AudioDecoder::decodeValue
// Address: 0x0057c590
// Decodes a single compressed value from an audio bitstream.
// Returns pointer to next byte after the decoded symbol.
// Outputs the decoded float value via outValue.

byte* AudioDecoder::decodeValue(byte* data, float residual, uint bitIndex, float* outValue)
{
    byte headerByte = *data;
    uint nibbleType = headerByte & 0xF;                  // low nibble indicates type
    uint count = (data[1] << 4) | (headerByte >> 4);     // high nibble + second byte = count or length

    if (nibbleType == 5) {
        // Type 5: variable-length run of symbols
        byte* endOfBlock = data + *(uint16*)(data + 2);  // +2 short gives block size
        data += 4;                                       // skip header (2 bytes type+count, 2 bytes size)
        while (count != 0) {
            byte nextHeader = *data;
            uint symbolLength = (data[1] << 4) | (nextHeader >> 4);
            uint subType = nextHeader & 0xF;
            uint lengthMinusOne = symbolLength - 1;
            count--;

            if (bitIndex < symbolLength) {
                // Not enough bits remaining – handle early termination
                byte* blockStart = endOfBlock; // save original block start before any header reads
                switch (subType) {
                    case 0xC:
                        *outValue = 0.0f;
                        return blockStart;
                    case 0xD:
                        *outValue = sEpsilon;           // DAT_00e2b1a4 (approximately 1.0f)
                        return blockStart;
                    case 0x0: // bit test? Actually (nextHeader & 0xF) == 0 means subType==0
                        audioDecodeZero();               // FUN_0057c0f0
                        *outValue = residual;
                        return blockStart;
                    case 0xE:
                        if ( (data[(bitIndex >> 3) + 2] >> (bitIndex & 7) & 1) == 0 ) {
                            *outValue = 0.0f;
                        } else {
                            *outValue = sEpsilon;
                        }
                        return blockStart;
                    default:
                        audioDecodeUnknown(subType, residual); // FUN_0057c260
                        data = blockStart; // fall through to continue? Actually original sets pbVar1 to blockStart
                        // loop continues, but here we just return to caller? The original returns pbVar1 after call.
                        // The code after the break sets param_1 = pbVar1 and then loop checks count again.
                        // Since we are in the breakout path, we set data to blockStart and then loop condition (count) will be decremented? Actually original: after call, param_1 = pbVar1; then it loops back to while(uVar4...), but uVar4 was decremented? Wait, in original, after the call, it sets param_1 = pbVar1 and then the loop condition checks uVar4 (which was already decremented). So it will continue the loop with new data. But here we are in the breakout path (bitIndex < symbolLength), so we skip the loop and return. So this default case within the breakout leads to param_1 = pbVar1 and then no return, so it goes to the loop top again. To mimic that, we need to adjust.
                        // Actually from original:
                        // if ((bVar2 & 0xf) == 0) { ... return pbVar1; }
                        // else if (uVar5 == 0xe) { ... return pbVar1; }
                        // else { FUN_0057c260(uVar5,param_2); param_1 = pbVar1; }
                        // So only for subType 0 and 0xE it returns; for default it sets data and continues.
                        // The loop will then check count (already decremented). So we simulate that.
                        audioDecodeUnknown(subType, residual);
                        data = blockStart; // continue loop
                        continue;
                }
            }

            // Normal processing: advance pointer based on subtype
            uint size;
            if (subType == 0xE) {
                size = (symbolLength + 7) >> 3; // aligned to byte boundary
            } else {
                size = sNibbleSizeTable[subType] * symbolLength;
            }
            // Advance by offset + compressed data size
            data += sNibbleOffsetTable[subType] + size;

            bitIndex -= lengthMinusOne;
            // Update residual using precomputed float table and a constant
            residual -= (sFloatTable[lengthMinusOne >> 8] * sQuantFactor + sFloatTable[lengthMinusOne & 0xFF]);
        }
        return data; // after loop, return current position
    }

    // Non-type-5: single symbol
    float value;
    if (nibbleType == 0xC) {
        value = 0.0f;
    } else if (nibbleType == 0xD) {
        value = sEpsilon;
    } else {
        if ( (headerByte & 0xF) == 0 ) {
            // Subtype 0: read a 24-bit value (3 bytes) shifted left 8 => 32-bit
            value = (float)( (uint)*(uint24*)(data + 2) << 8 );
        } else if (nibbleType == 0xE) {
            // Bit test at position bitIndex
            if ( (data[(bitIndex >> 3) + 2] >> (bitIndex & 7) & 1) == 0 ) {
                value = 0.0f;
            } else {
                value = sEpsilon;
            }
            // Advance pointer including a fixed offset plus aligned count
            return data + HEADER_OFFSET + ((count + 7) >> 3);
        } else {
            audioDecodeUnknown(nibbleType, residual);
            // Fall through to LAB_0057c5c9 (advance with table)
        }
    }
    *outValue = value;
    // LAB_0057c5c9: advance by offset and size from tables
    return data + sNibbleOffsetTable[nibbleType] + sNibbleSizeTable[nibbleType] * count;
}