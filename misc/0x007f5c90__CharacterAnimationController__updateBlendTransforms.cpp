//FUNC_NAME: CharacterAnimationController::updateBlendTransforms
// Address: 0x007f5c90
// This function updates blended bone transforms for a character animation controller.
// It checks flags at +0x970 and +0x974 (bit 4) to decide whether to clear and copy transforms.
// Then it performs matrix operations and optionally triggers a callback.

void __thiscall CharacterAnimationController::updateBlendTransforms(void* thisPtr, float param2)
{
    // Flags at +0x970 and +0x974 (bit 4 indicates "blend active" or similar)
    uint flags1 = *(uint*)((char*)thisPtr + 0x970);
    uint flags2 = *(uint*)((char*)thisPtr + 0x974);

    if (((flags1 >> 4) & 1) != 0 && ((flags2 >> 4) & 1) != 0)
    {
        // Clear 18 groups of 4 floats (bone transforms) starting at various offsets
        // Each group is 16 bytes (4 floats), spaced 0x30 apart? Actually offsets are:
        // 0xd10, 0xd40, 0xd70, 0xda0, 0xdd0, 0xe00, 0xe30, 0xe60, 0xe90, 0xec0, 0xef0, 0xf20, 0xf50, 0xf80,
        // 0xbf0, 0xc20, 0xc50, 0xc80
        // These likely represent bone local transforms (quaternions or positions)
        float* boneTransforms[] = {
            (float*)((char*)thisPtr + 0xd10),
            (float*)((char*)thisPtr + 0xd40),
            (float*)((char*)thisPtr + 0xd70),
            (float*)((char*)thisPtr + 0xda0),
            (float*)((char*)thisPtr + 0xdd0),
            (float*)((char*)thisPtr + 0xe00),
            (float*)((char*)thisPtr + 0xe30),
            (float*)((char*)thisPtr + 0xe60),
            (float*)((char*)thisPtr + 0xe90),
            (float*)((char*)thisPtr + 0xec0),
            (float*)((char*)thisPtr + 0xef0),
            (float*)((char*)thisPtr + 0xf20),
            (float*)((char*)thisPtr + 0xf50),
            (float*)((char*)thisPtr + 0xf80),
            (float*)((char*)thisPtr + 0xbf0),
            (float*)((char*)thisPtr + 0xc20),
            (float*)((char*)thisPtr + 0xc50),
            (float*)((char*)thisPtr + 0xc80)
        };
        for (int i = 0; i < 18; i++)
        {
            boneTransforms[i][0] = 0.0f;
            boneTransforms[i][1] = 0.0f;
            boneTransforms[i][2] = 0.0f;
            boneTransforms[i][3] = 0.0f;
        }

        // Copy source transforms to destination (likely from "blend source" to "blend output")
        // Source at +0x9d0 (4 floats) -> Destination at +0xb80
        float* src1 = (float*)((char*)thisPtr + 0x9d0);
        float* dst1 = (float*)((char*)thisPtr + 0xb80);
        dst1[0] = src1[0];
        dst1[1] = src1[1];
        dst1[2] = src1[2];
        dst1[3] = src1[3];

        // Source at +0x9e0 (4 floats) -> Destination at +0xbb0
        float* src2 = (float*)((char*)thisPtr + 0x9e0);
        float* dst2 = (float*)((char*)thisPtr + 0xbb0);
        dst2[0] = src2[0];
        dst2[1] = src2[1];
        dst2[2] = src2[2];
        dst2[3] = src2[3];
    }

    // Always clear another set of 2 groups (8 floats) at +0xb30 and +0xb60
    float* clear1 = (float*)((char*)thisPtr + 0xb30);
    clear1[0] = 0.0f; clear1[1] = 0.0f; clear1[2] = 0.0f; clear1[3] = 0.0f;
    float* clear2 = (float*)((char*)thisPtr + 0xb60);
    clear2[0] = 0.0f; clear2[1] = 0.0f; clear2[2] = 0.0f; clear2[3] = 0.0f;

    // Copy another pair of source transforms to destinations
    // Source at +0x940 -> Destination at +0xaf0
    float* src3 = (float*)((char*)thisPtr + 0x940);
    float* dst3 = (float*)((char*)thisPtr + 0xaf0);
    dst3[0] = src3[0]; dst3[1] = src3[1]; dst3[2] = src3[2]; dst3[3] = src3[3];

    // Source at +0xa60 -> Destination at +0xfa0
    float* src4 = (float*)((char*)thisPtr + 0xa60);
    float* dst4 = (float*)((char*)thisPtr + 0xfa0);
    dst4[0] = src4[0]; dst4[1] = src4[1]; dst4[2] = src4[2]; dst4[3] = src4[3];

    // Temporary buffer (28 bytes = 7 floats) for intermediate transform
    float temp[7]; // local_20

    // Perform matrix operations (likely multiply and interpolate)
    // FUN_0056d6b0: multiplyTransforms(source, blend, output, temp)
    multiplyTransforms((float*)((char*)thisPtr + 0xa40), (float*)((char*)thisPtr + 0x930), (float*)((char*)thisPtr + 0xa10), temp);
    // FUN_0056cba0: interpolateTransforms(temp, output1, output2)
    interpolateTransforms(temp, (float*)((char*)thisPtr + 0xa90), (float*)((char*)thisPtr + 0xac0));

    // Two more multiply operations
    multiplyTransforms((float*)((char*)thisPtr + 0x950), (float*)((char*)thisPtr + 0x9f0), (float*)((char*)thisPtr + 0xaa0), (float*)((char*)thisPtr + 0xb20));
    multiplyTransforms((float*)((char*)thisPtr + 0x960), (float*)((char*)thisPtr + 0xa00), (float*)((char*)thisPtr + 0xab0), (float*)((char*)thisPtr + 0xb50));

    // Check if we should trigger a callback
    int* callbackPtr = *(int**)((char*)thisPtr + 0x1bc8);
    if (callbackPtr != 0)
    {
        uint flags3 = *(uint*)((char*)thisPtr + 0x1b94);
        if (((flags3 >> 22) & 1) != 0) // bit 22
        {
            byte byteFlag1 = *(byte*)((char*)thisPtr + 0x970);
            byte byteFlag2 = *(byte*)((char*)thisPtr + 0x974);
            if ((byteFlag1 & 1) != 0 && (byteFlag2 & 1) != 0)
            {
                // Call the callback function with the pointer and param2
                FUN_007f5c00(callbackPtr, param2);
            }
        }
    }
}