// FUNC_NAME: EARSAnimationDecoder::DecodePackedKeyframe
// Role: Decompress variable-length encoded animation keyframe data.
// Reads a packed byte stream, seeks to the requested frame index, and outputs two float values (likely a vec2 or keyframe value and tangent).
// Returns pointer to next data after the processed chunk.
// Global tables: gBlockSizeTable[16] (at 0xe2c2a4), gBlockLengthTable[16] (at 0xe2c2e0), gTimeTable[256] (at 0xe2c320), gTimeScale (0xe445d0), gConstantOne (0xe2b1a4)

byte* __fastcall DecodePackedKeyframe(byte* inputBuffer, uint frameIndex, float inTime, float* outKeyframe)
{
    byte* pbResult;
    byte bTemp;
    byte* pbCurrent;
    uint uBlockLen;
    uint uBlockCount;
    uint uSubBlockLen;
    uint uSubBlockSize;
    float fConstantOne;
    float fBitValue;

    fConstantOne = DAT_00e2b1a4;  // constant 1.0f (or similar)
    bTemp = *inputBuffer;
    uBlockCount = bTemp & 0xf;                              // type (4 bits)
    uBlockLen = (uint)inputBuffer[1] << 4 | (uint)(bTemp >> 4); // length/offset (12 bits)

    if (uBlockCount == 5) {  // type 5: hierarchical block structure
        pbCurrent = inputBuffer + 4;  // skip first 4 bytes? Actually base is after header
        pbResult = (byte*)((*(ushort*)(inputBuffer + 2) - 2) + (int)(inputBuffer + 2)); // relative offset from header
        if (uBlockLen != 0) {
            while (true) {
                bTemp = *pbCurrent;
                uSubBlockSize = (uint)pbCurrent[1] << 4 | (uint)(bTemp >> 4); // sub-block length
                uSubBlockLen = uSubBlockSize - 1; // convert to 0-based length
                uBlockCount = bTemp & 0xf;        // sub-block type
                uBlockLen = uBlockLen - 1;         // decrement remaining blocks

                if (frameIndex < uSubBlockLen) break; // found the block containing the desired frame

                // else skip forward
                if (uBlockCount == 0xe) {
                    uSubBlockSize = (uSubBlockSize + 7) >> 3; // bit packed block
                } else {
                    uSubBlockSize = *(int*)(&gBlockLengthTable + uBlockCount * 4) * uSubBlockSize;
                }
                pbCurrent = pbCurrent + *(int*)(&gBlockSizeTable + uBlockCount * 4) + uSubBlockSize;
                frameIndex = frameIndex - uSubBlockLen;
                inTime = inTime - (*(float*)(&gTimeTable + (uSubBlockLen >> 8) * 4) * gTimeScale +
                                  *(float*)(&gTimeTable + (uSubBlockLen & 0xff) * 4));
                if (uBlockLen == 0) {
                    return pbCurrent; // no more blocks, return current pointer
                }
            }

            // Found the specific sub-block with the requested frame
            if (uBlockCount == 0xc) {
                outKeyframe[0] = 0.0f;
                outKeyframe[4] = 0.0f;  // actual struct has two floats at offsets 0 and 16? (padding)
                return pbResult;
            }
            if (uBlockCount == 0xd) {
                outKeyframe[0] = fConstantOne;
                outKeyframe[4] = fConstantOne;
                return pbResult;
            }
            if ((bTemp & 0xf) == 0) {
                FUN_0057c0f0(); // error handler?
                outKeyframe[0] = inTime;
                outKeyframe[4] = inTime;
                return pbResult;
            }
            if (uBlockCount == 0xe) {
                // Bitfield: two bits starting at frameIndex
                fBitValue = fConstantOne;
                if ((pbCurrent[(frameIndex >> 3) + 2] >> ((byte)frameIndex & 7) & 1) == 0) {
                    fBitValue = 0.0f;
                }
                outKeyframe[0] = fBitValue;
                fBitValue = 0.0f;
                if ((pbCurrent[((frameIndex + 1) >> 3) + 2] >> (((byte)frameIndex + 1) & 7) & 1) != 0) {
                    fBitValue = fConstantOne;
                }
                outKeyframe[4] = fBitValue;
                return pbResult;
            }
            FUN_0057c390(uBlockCount, inTime); // unknown decode function
            return pbResult; // or pbCurrent? original: pbVar3 = pbVar1; return pbVar3 (which is pbVar1)
        }
        return pbCurrent; // empty block
    }

    // Non-type-5: direct literal encoding
    if (uBlockCount == 0xc) {
        fConstantOne = 0.0f;
    }
    else if (uBlockCount != 0xd) {
        if ((bTemp & 0xf) == 0) {
            outKeyframe[0] = (float)((uint)*(uint3*)(inputBuffer + 2) << 8); // 3-byte integer shifted
            outKeyframe[4] = outKeyframe[0];
        }
        else {
            if (uBlockCount == 0xe) {
                fBitValue = fConstantOne;
                if ((inputBuffer[(frameIndex >> 3) + 2] >> ((byte)frameIndex & 7) & 1) == 0) {
                    fBitValue = 0.0f;
                }
                outKeyframe[0] = fBitValue;
                fBitValue = 0.0f;
                if ((inputBuffer[((frameIndex + 1) >> 3) + 2] >> (((byte)frameIndex + 1) & 7) & 1) != 0) {
                    fBitValue = fConstantOne;
                }
                outKeyframe[4] = fBitValue;
                return inputBuffer + 0x????? + (uBlockLen + 7 >> 3); // unknown fixed offset
            }
            FUN_0057c390(uBlockCount, inTime);
        }
        goto LAB_RETURN;
    }
    outKeyframe[0] = fConstantOne;
    outKeyframe[4] = fConstantOne;

LAB_RETURN:
    return inputBuffer + *(int*)(&gBlockSizeTable + uBlockCount * 4) + *(int*)(&gBlockLengthTable + uBlockCount * 4) * uBlockLen;
}