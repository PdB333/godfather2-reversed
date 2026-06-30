// FUNC_NAME: Animation::blendTransforms
// Address: 0x004cd4b0
// This function blends transformation data from a source buffer into a global blend buffer.
// It handles different data sizes based on an index (0-4) and a blend flag.
// The global buffer at 0x01164080 is used as the output destination.

undefined4* __fastcall Animation::blendTransforms(int index, bool blendFlag, float* blendWeights, int sourceData, int count)
{
    float* dstFloat;
    float fVar1, fVar2, fVar3, fVar8, fVar9, fVar10;
    uint8_t uVar4;
    uint16_t uVar5, uVar6;
    uint32_t uVar7;
    float* srcFloat;
    float* srcFloat2;
    uint8_t* dstByte;
    uint8_t* srcByte;
    int localCount;

    // Global blend buffer (0x01164080)
    // +0x00: start of blend data
    // +0x08: secondary start (used for index 0)
    #define BLEND_BUFFER 0x01164080
    #define BLEND_BUFFER2 0x01164088

    if (index == 0)
    {
        if (!blendFlag)
        {
            // Non-blended copy: add blendWeights to source data and store to buffer
            if (count != 0)
            {
                dstFloat = (float*)BLEND_BUFFER2;  // +0x08
                srcFloat = (float*)(sourceData + 8); // source data offset by 8
                do
                {
                    // Write 5 floats: first 3 from source+blend, last 2 from source
                    // dstFloat[-2] = source at same relative offset + blendWeights[-2]
                    dstFloat[-2] = *(float*)(sourceData - 0x1164088 + (int)dstFloat) + blendWeights[-2];
                    dstFloat[-1] = srcFloat[-1] + blendWeights[-1];
                    dstFloat[0] = srcFloat[0] + blendWeights[0];
                    dstFloat[1] = srcFloat[1];
                    dstFloat[2] = srcFloat[2];
                    srcFloat += 5;
                    dstFloat += 5;
                    blendWeights += 4;
                    count--;
                } while (count != 0);
            }
        }
        else
        {
            // Blended copy: copy 3 ints (12 bytes) from source to buffer, calling helper each time
            if (count != 0)
            {
                uint32_t* srcInt = (uint32_t*)(sourceData + 8);
                localCount = count;
                do
                {
                    FUN_004cd380(); // likely clears or prepares buffer
                    // Copy one int from source to buffer at offset 0x08
                    *(uint32_t*)((int)srcInt + ((int)&BLEND_BUFFER - sourceData)) = *srcInt;
                    srcInt += 3; // advance 12 bytes
                    localCount--;
                } while (localCount != 0);
                return (undefined4*)BLEND_BUFFER;
            }
        }
    }
    else if ((index != 0) && (index < 5))
    {
        if (!blendFlag)
        {
            // Non-blended copy: 8 floats per element
            if (count != 0)
            {
                dstFloat = (float*)BLEND_BUFFER;
                srcFloat = (float*)(sourceData + 0x10); // source data offset by 0x10
                do
                {
                    // Read from source at same relative offset as destination
                    float* srcRel = (float*)(sourceData - 0x1164080 + (int)dstFloat);
                    fVar1 = srcRel[1];
                    fVar2 = srcRel[2];
                    fVar3 = srcRel[3];
                    fVar8 = blendWeights[1];
                    fVar9 = blendWeights[2];
                    fVar10 = blendWeights[3];
                    // First 4 floats: blend weights added to source relative data
                    dstFloat[0] = blendWeights[0] + srcRel[0];
                    dstFloat[1] = fVar8 + fVar1;
                    dstFloat[2] = fVar9 + fVar2;
                    dstFloat[3] = fVar3;
                    // Next 4 floats: copied directly from source offset 0x10
                    dstFloat[4] = srcFloat[0];
                    dstFloat[5] = srcFloat[1];
                    dstFloat[6] = srcFloat[2];
                    dstFloat[7] = srcFloat[3];
                    dstFloat += 8;
                    srcFloat += 8;
                    blendWeights += 4;
                    count--;
                } while (count != 0);
                return (undefined4*)BLEND_BUFFER;
            }
        }
        else
        {
            // Blended copy: copy 16 bytes per element, calling helper each time
            if (count != 0)
            {
                dstByte = (uint8_t*)(BLEND_BUFFER + 3); // +0x03
                srcByte = (uint8_t*)(sourceData + 7);   // source offset by 7
                localCount = count;
                do
                {
                    FUN_004cd380();
                    // Copy 16 bytes: 1 byte, 4 bytes, 2 bytes, 2 bytes (total 9? Actually 1+4+2+2=9, but offset increments by 16)
                    // This is a structured copy with padding
                    uVar4 = srcByte[-1];
                    uVar7 = *(uint32_t*)(srcByte + 1);
                    dstByte[-1] = srcByte[-1];
                    uVar5 = *(uint16_t*)(srcByte + 5);
                    *dstByte = uVar4;
                    uVar6 = *(uint16_t*)(srcByte + 7);
                    *(uint32_t*)(dstByte + 1) = uVar7;
                    *(uint16_t*)(dstByte + 5) = uVar5;
                    *(uint16_t*)(dstByte + 7) = uVar6;
                    srcByte += 0x10;
                    dstByte += 0x10;
                    localCount--;
                } while (localCount != 0);
                return (undefined4*)BLEND_BUFFER;
            }
        }
    }
    return (undefined4*)BLEND_BUFFER;
}