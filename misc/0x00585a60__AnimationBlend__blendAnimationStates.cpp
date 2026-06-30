// FUNC_NAME: AnimationBlend::blendAnimationStates
int AnimationBlend::blendAnimationStates(void* sourceA, void* sourceB, float blendFactor)
{
    // +0x38 points to a sub-structure containing bone count at +0x0c and position data at +0x10
    // +0x34 points to a sub-structure containing flag at +0x10 (masking)
    // +0x3c points to optional scale/quaternion data (if non-zero)
    // +0x40 points to optional extra channel (e.g. rotation)
    // +0x44 points to optional integer channel (e.g. bone indices or weights)

    // Get destination buffer from animation manager
    int destBuffer = FUN_0056fdd0();  // returns pointer to blend output structure
    if (sourceB == 0 || destBuffer == 0)
        return 0;

    int bonesA = *(int*)(*(int*)(sourceA + 0x38) + 0xc);
    int bonesB = *(int*)(*(int*)(sourceB + 0x38) + 0xc);
    int minBones = bonesA;
    if (bonesB <= bonesA)
        minBones = bonesB;

    // Free old data in source buffers? (possibly decrement ref counts)
    FUN_0056f800(sourceB);
    FUN_0056f800(sourceA);

    // Choose the source with fewer bones for later memcpy
    int remainingSource = sourceB;
    if (bonesB <= bonesA)
        remainingSource = sourceA;

    FUN_0056f800(remainingSource);

    float t = blendFactor;

    // Branch based on presence of extra 4th component (scale/quaternion)
    if (*(int*)(destBuffer + 0x3c) == 0)
    {
        // No extra component – only blend position and (implied) rotation?
        // Position data: offset 0x14 in sub-structure at +0x34? Actually accessing as count increment.
        // More clearly: code accesses arrays via pointers derived from +0x34/+0x38
        void* srcABase = (void*)(*(int*)(sourceA + 0x34) + 0x14);
        void* srcBBase = (void*)(*(int*)(sourceB + 0x34) + 0x14);
        float* srcBNext = (float*)(*(int*)(sourceB + 0x38) + 0x10);
        float* srcANext = (float*)(*(int*)(sourceA + 0x38) + 0x10);
        void* dstBase = (void*)(*(int*)(destBuffer + 0x34) + 0x14);
        float* dstNext = (float*)(*(int*)(destBuffer + 0x38) + 0x10);
        int count = minBones;

        // Check mask flags at +0x10 of the sub-structures
        bool maskA = (*(char*)(*(int*)(sourceA + 0x34) + 0x10) != '\0');
        bool maskB = (*(char*)(*(int*)(sourceB + 0x34) + 0x10) != '\0');

        if (!maskA || !maskB)
        {
            // Simple interpolation using 8 floats per bone (position + rotation?)
            for (; count > 0; count--)
            {
                FUN_005859d0(&srcBBase, t);  // blend step (increments pointers)
                srcBNext += 8;
                srcABase = (void*)((int)srcABase + 1);
                srcBBase = (void*)((int)srcBBase + 1);
                dstBase = (void*)((int)dstBase + 1);
                srcANext = ((float*)srcANext) + 8;
                dstNext = ((float*)dstNext) + 8;
            }
        }
        else
        {
            // Both masked – use advanced interpolation with base frame fallback
            float* savedDstNext = dstNext;
            float* savedSrcANext = srcANext;
            FUN_0056f620();  // some setup (maybe cache flush)
            int iter = minBones;
            if (0 < minBones)
            {
                srcABase = (void*)((int)srcABase + minBones);
                dstBase = (void*)((int)dstBase + minBones);
                srcBBase = (void*)((int)srcBBase + minBones);
                do {
                    FUN_005781f0(dstNext, t);  // interpolate first 4 floats?
                    srcBNext += 8;
                    iter--;
                    srcANext += 8;
                    dstNext = savedDstNext + 8;
                    t = blendFactor;
                } while (0 < iter);
            }
        }

        if (minBones < bonesA)
        {
            // SourceA has more bones – copy remaining from sourceA
            memcpy(dstBase, srcABase, bonesA - minBones);
            memcpy(dstNext, srcANext, (bonesA - minBones) * 0x20); // 32 bytes per bone (8 floats)
        }
        else
        {
            if (bonesB <= minBones)
                goto LAB_00585e3b;
            // SourceB has more bones – copy remaining from sourceB
            memcpy(dstBase, srcBBase, bonesB - minBones);
            memcpy(dstNext, srcBNext, (bonesB - minBones) * 0x20);
        }
    }
    else
    {
        // Has extra component (scale/quaternion) – blend 4component arrays
        void* srcAExtra = (void*)(*(int*)(sourceA + 0x34) + 0x14);
        float* srcAExtraData = (float*)(*(int*)(sourceA + 0x3c) + 0x10);
        void* srcBExtra = (void*)(*(int*)(sourceB + 0x34) + 0x14);
        float* srcBNext = (float*)(*(int*)(sourceB + 0x38) + 0x10);
        float* srcBExtraData = (float*)(*(int*)(sourceB + 0x3c) + 0x10);
        void* dstBase = (void*)(*(int*)(destBuffer + 0x34) + 0x14);
        float* dstNext = (float*)(*(int*)(sourceA + 0x38) + 0x10);
        float* dstExtraNext = (float*)(*(int*)(destBuffer + 0x38) + 0x10);
        float* dstExtraData = (float*)(*(int*)(destBuffer + 0x3c) + 0x10);
        int count = minBones;

        bool maskA = (*(char*)(*(int*)(sourceA + 0x34) + 0x10) != '\0');
        bool maskB = (*(char*)(*(int*)(sourceB + 0x34) + 0x10) != '\0');

        if (!maskA || !maskB)
        {
            for (; count > 0; count--)
            {
                FUN_005867d0(&dstBase, &srcAExtra, &srcBExtra, t);
                srcBNext += 8;
                srcAExtra = (void*)((int)srcAExtra + 1);
                srcBExtra = (void*)((int)srcBExtra + 1);
                dstBase = (void*)((int)dstBase + 1);
                srcAExtraData += 4;
                srcBExtraData += 4;
                dstExtraData += 4;
                dstNext = ((float*)dstNext) + 8;
                dstExtraNext = ((float*)dstExtraNext) + 8;
            }
        }
        else
        {
            float* savedDstNext = dstNext;
            float* savedDstExtraNext = dstExtraNext;
            FUN_0056f620();
            int iter = minBones;
            if (0 < minBones)
            {
                srcAExtra = (void*)((int)srcAExtra + minBones);
                dstBase = (void*)((int)dstBase + minBones);
                srcBExtra = (void*)((int)srcBExtra + minBones);
                // Store blendFactor in stack for componentwise interpolation
                float bf[4] = {t, t, t, t};
                do {
                    FUN_005781f0(dstExtraNext, t);
                    // Interpolate 4float component (scale/quaternion) linearly
                    float srcA0 = srcAExtraData[1];
                    float srcA1 = srcAExtraData[2];
                    float srcA2 = srcAExtraData[3];
                    float srcB0 = srcBExtraData[1];
                    float srcB1 = srcBExtraData[2];
                    float srcB2 = srcBExtraData[3];
                    dstExtraData[0] = (srcBExtraData[0] - srcAExtraData[0]) * bf[0] + srcAExtraData[0];
                    dstExtraData[1] = (srcB0 - srcA0) * bf[1] + srcA0;
                    dstExtraData[2] = (srcB1 - srcA1) * bf[2] + srcA1;
                    dstExtraData[3] = (srcB2 - srcA2) * bf[3] + srcA2;
                    srcBNext += 8;
                    iter--;
                    srcAExtraData += 4;
                    srcBExtraData += 4;
                    dstExtraData += 4;
                    dstNext += 8;
                    dstExtraNext += 8;
                    t = blendFactor;
                } while (0 < iter);
            }
        }

        if (minBones < bonesA)
        {
            memcpy(dstBase, srcAExtra, bonesA - minBones);
            memcpy(dstExtraNext, dstNext, (bonesA - minBones) * 0x20);
        }
        else
        {
            if (bonesB <= minBones)
                goto LAB_00585e3b;
            memcpy(dstBase, srcBExtra, bonesB - minBones);
            memcpy(dstExtraNext, srcBNext, (bonesB - minBones) * 0x20);
        }
        // Copy remaining extra data (4 floats per bone) to destination
        memcpy(dstExtraData, srcAExtraData, (bonesA - minBones) * 0x10);  // 16 bytes per extra element
    }

LAB_00585e3b:
    // Handle additional integer channel at offset 0x44 with special interpolation
    float threshold = DAT_00e2b1a4;  // global constant (maybe 1.0 or small)
    if (*(int*)(destBuffer + 0x44) != 0)
    {
        int* srcAInt = (int*)(*(int*)(sourceA + 0x44) + 0x10);
        int* srcBInt = (int*)(*(int*)(sourceB + 0x44) + 0x10);
        int* dstInt = (int*)(*(int*)(destBuffer + 0x44) + 0x10);
        int remaining = minBones;
        // Process in chunks of 4 bones (8 ints per bone: pair of floor/weight?)
        if (3 < minBones)
        {
            int chunkCount = (minBones - 4U >> 2) + 1;
            remaining = minBones + chunkCount * -4;
            do {
                // Interpolate 4 bones per iteration (each bone uses 2 ints: id and weight)
                // Blend with special rules: if t>0 and t<threshold, interpolate; if t>=threshold, take sourceB; handle -1 sentinel
                int idB0 = *srcBInt;
                int idA0 = *srcAInt;
                float weightA0 = (float)srcAInt[1];
                float weightB0 = (float)srcBInt[1];
                dstInt[0] = idB0;
                if (0.0f < t)
                {
                    if (threshold <= t)
                    {
                        dstInt[0] = idB0;  // keep
                    }
                    else if (idA0 != idB0)
                    {
                        if (idB0 != -1)
                            dstInt[0] = idB0;
                        else
                        {
                            dstInt[0] = 7;  // clamp to 7
                            weightB0 = threshold;  // use threshold as weight?
                        }
                    }
                }
                else
                {
                    dstInt[0] = idA0;
                }
                dstInt[1] = (int)((weightB0 - weightA0) * t + weightA0);
                // Repeat for each of the 4 bones in group (offsets 2,4,6)
                // ... (similar pattern)
                srcAInt += 8;
                srcBInt += 8;
                dstInt += 8;
                chunkCount--;
            } while (chunkCount != 0);
        }
        // Handle remaining bones (<4)
        for (; 0 < remaining; remaining--)
        {
            int idB = *srcBInt;
            int idA = *srcAInt;
            float wA = (float)srcAInt[1];
            float wB = (float)srcBInt[1];
            *dstInt = idB;
            if (0.0f < t)
            {
                if (threshold <= t)
                {
                    *dstInt = idB;
                }
                else if (idA != idB)
                {
                    if (idB != -1)
                        *dstInt = idB;
                    else
                    {
                        *dstInt = 7;
                        wB = threshold;
                    }
                }
            }
            else
            {
                *dstInt = idA;
            }
            dstInt[1] = (int)((wB - wA) * t + wA);
            srcAInt += 2;
            srcBInt += 2;
            dstInt += 2;
        }

        if (minBones < bonesA)
        {
            memcpy(dstInt, srcAInt, (bonesA - minBones) * 8);  // 8 bytes per bone (2 ints)
            return destBuffer;
        }
        if (minBones < bonesB)
        {
            memcpy(dstInt, srcBInt, (bonesB - minBones) * 8);
        }
    }
    return destBuffer;
}