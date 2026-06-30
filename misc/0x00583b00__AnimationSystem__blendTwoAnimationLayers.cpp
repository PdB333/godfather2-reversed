// FUNC_NAME: AnimationSystem::blendTwoAnimationLayers
int AnimationSystem::blendTwoAnimationLayers(int animA, int animB, byte flags)
{
    // resultAnim obtained from some pool/manager
    int resultAnim = FUN_0056fdd0();
    if (animA == 0 || animB == 0 || resultAnim == 0) {
        return 0;
    }

    // If flags has bit 2 set, skip the main per-bone blending
    if ((flags & 4) != 0) {
        goto processRootTransform;
    }

    // Get number of bones from each animation's transform container
    // Container at +0x38: header with count at +0x0c
    int numBonesA = *(int*)(*(int*)(animA + 0x38) + 0x0c);
    int numBonesB = *(int*)(*(int*)(animB + 0x38) + 0x0c);
    int minBones = (numBonesA < numBonesB) ? numBonesA : numBonesB;

    // Reference/lock the animation sources
    FUN_0056f800(animB);
    FUN_0056f800(animA);
    int largerCountAnim = (numBonesB <= numBonesA) ? animB : animA;
    FUN_0056f800(largerCountAnim);

    // If the third auxiliary container (at +0x3c) is null, we blend without it
    if (*(int*)(resultAnim + 0x3c) == 0) {
        // Pointers to per-bone data for bone weights (1 byte each) and bone transforms (32 bytes each)
        char* boneWeightsA = (char*)(*(int*)(animA + 0x34) + 0x14);
        char* boneWeightsB = (char*)(*(int*)(animB + 0x34) + 0x14);
        char* boneWeightsResult = (char*)(*(int*)(resultAnim + 0x34) + 0x14);

        void* boneTransformsA = (void*)(*(int*)(animA + 0x38) + 0x10);
        void* boneTransformsB = (void*)(*(int*)(animB + 0x38) + 0x10);
        void* boneTransformsResult = (void*)(*(int*)(resultAnim + 0x38) + 0x10);

        int count = minBones;
        if (*(char*)(*(int*)(animA + 0x34) + 0x10) == 0 || 
            *(char*)(*(int*)(animB + 0x34) + 0x10) == 0) {
            // Simple copy/weighted blend case
            for (; count > 0; count--) {
                FUN_00583aa0();
                boneWeightsA++;
                boneWeightsB++;
                boneWeightsResult++;
                boneTransformsA = (void*)((int)boneTransformsA + 0x20);
                boneTransformsB = (void*)((int)boneTransformsB + 0x20);
                boneTransformsResult = (void*)((int)boneTransformsResult + 0x20);
            }
        } else {
            // Additive blend case
            FUN_0056f620();
            for (; count > 0; count--) {
                FUN_00582ea0(&boneWeightsResult);
                boneWeightsA++;
                boneWeightsB++;
                boneWeightsResult++;
                boneTransformsA = (void*)((int)boneTransformsA + 0x20);
                boneTransformsB = (void*)((int)boneTransformsB + 0x20);
                boneTransformsResult = (void*)((int)boneTransformsResult + 0x20);
            }
        }

        // Copy remaining bones from the larger source if any
        if (minBones < numBonesA) {
            memcpy(boneTransformsResult, boneTransformsA, (numBonesA - minBones) * 0x20);
            memcpy(boneWeightsResult, boneWeightsA, numBonesA - minBones);
        } else if (minBones < numBonesB) {
            memcpy(boneTransformsResult, boneTransformsB, (numBonesB - minBones) * 0x20);
            memcpy(boneWeightsResult, boneWeightsB, numBonesB - minBones);
        }
    } else {
        // There is a third auxiliary buffer (at +0x3c) for additional per-bone data (16 bytes each)
        char* boneWeightsResult = (char*)(*(int*)(resultAnim + 0x34) + 0x14);
        void* boneTransformsResult = (void*)(*(int*)(resultAnim + 0x38) + 0x10);
        float* auxResult = (float*)(*(int*)(resultAnim + 0x3c) + 0x10);

        char* boneWeightsA = (char*)(*(int*)(animA + 0x34) + 0x14);
        void* boneTransformsA = (void*)(*(int*)(animA + 0x38) + 0x10);
        float* auxA = (float*)(*(int*)(animA + 0x3c) + 0x10);

        char* boneWeightsB = (char*)(*(int*)(animB + 0x34) + 0x14);
        void* boneTransformsB = (void*)(*(int*)(animB + 0x38) + 0x10);
        float* auxB = (float*)(*(int*)(animB + 0x3c) + 0x10);

        int count = minBones;
        if (*(char*)(*(int*)(animA + 0x34) + 0x10) == 0 || 
            *(char*)(*(int*)(animB + 0x34) + 0x10) == 0) {
            // Simple blend (likely copy or linear interpolation)
            for (; count > 0; count--) {
                FUN_00586400(&boneWeightsResult);
                auxB += 4; auxA += 4; auxResult += 4;
                boneWeightsA++; boneWeightsB++; boneWeightsResult++;
                boneTransformsA = (void*)((int)boneTransformsA + 0x20);
                boneTransformsB = (void*)((int)boneTransformsB + 0x20);
                boneTransformsResult = (void*)((int)boneTransformsResult + 0x20);
            }
        } else {
            // Additive blend with elementwise multiplication of aux data
            // This looks like blending weighting values
            float* localAuxResult = auxResult;
            FUN_0056f620();
            for (; count > 0; count--) {
                FUN_00582ea0(&boneWeightsResult);
                float a0 = auxA[0], a1 = auxA[1], a2 = auxA[2], a3 = auxA[3];
                float b0 = auxB[0], b1 = auxB[1], b2 = auxB[2], b3 = auxB[3];
                boneWeightsA++; boneWeightsB++; boneWeightsResult++;
                boneTransformsA = (void*)((int)boneTransformsA + 0x20);
                boneTransformsB = (void*)((int)boneTransformsB + 0x20);
                boneTransformsResult = (void*)((int)boneTransformsResult + 0x20);
                *localAuxResult = a0 * b0;
                localAuxResult[1] = a1 * b1;
                localAuxResult[2] = a2 * b2;
                localAuxResult[3] = a3 * b3;
                localAuxResult[3] = DAT_00e2b1a4;  // some constant (maybe scale or bias)
                auxA += 4; auxB += 4;
                auxResult = localAuxResult + 4;
                localAuxResult = auxResult;
            }
        }

        // Copy remaining bones from the larger source
        if (minBones < numBonesA) {
            int remaining = numBonesA - minBones;
            memcpy(boneWeightsResult, boneWeightsA, remaining);
            memcpy(boneTransformsResult, boneTransformsA, remaining * 0x20);
            memcpy(auxResult, auxA, remaining * 0x10);
        } else {
            if (minBones < numBonesB) {
                int remaining = numBonesB - minBones;
                memcpy(boneWeightsResult, boneWeightsB, remaining);
                memcpy(boneTransformsResult, boneTransformsB, remaining * 0x20);
                memcpy(auxResult, auxB, remaining * 0x10);
            }
        }
    }

processRootTransform:
    // Handle additional additive data arrays at +0x40 and +0x44
    if (*(int*)(resultAnim + 0x40) != 0) {
        // +0x40: an array of 4 floats per element; perform addition from A and B into result
        float* resultAdditive = *(float**)(resultAnim + 0x40);
        float* additiveA = *(float**)(animA + 0x40);
        float* additiveB = *(float**)(animB + 0x40);

        // Get count from float at index 3? (seems odd but it's what the code does)
        int additiveCount = (int)resultAdditive[3] >> 2; // likely number of elements
        float* ptrA = additiveA + 4;
        float* ptrB = additiveB + 4;
        float* ptrResult = resultAdditive + 4;

        while (additiveCount > 0) {
            ptrResult[0] = ptrA[0] + ptrB[0];
            ptrResult[1] = ptrA[1] + ptrB[1];
            ptrResult[2] = ptrA[2] + ptrB[2];
            ptrResult[3] = ptrA[3] + ptrB[3];
            ptrA += 4;
            ptrB += 4;
            ptrResult += 4;
            additiveCount--;
        }

        // Handle remainder (if count not multiple of 4)
        int rem = (int)resultAdditive[3] & 3;
        if (rem > 3) {
            int loop = (rem - 4) / 4 + 1;
            rem = rem - loop * 4;
            do {
                ptrResult[0] = ptrA[0] + ptrB[0];
                ptrResult[1] = ptrA[1] + ptrB[1];
                ptrResult[2] = ptrA[2] + ptrB[2];
                ptrResult[3] = ptrA[3] + ptrB[3];
                ptrA += 4;
                ptrB += 4;
                ptrResult += 4;
                loop--;
            } while (loop != 0);
        }
        for (; rem > 0; rem--) {
            *ptrResult = *ptrA + *ptrB;
            ptrA++;
            ptrB++;
            ptrResult++;
        }
    }

    if (*(int*)(resultAnim + 0x44) != 0) {
        // +0x44: array of int pairs (8 bytes per element); pick source based on -1 sentinel
        int* intFromA = (int*)(*(int*)(animA + 0x44) + 0x10);
        int* intFromB = (int*)(*(int*)(animB + 0x44) + 0x10);
        int* intResult = (int*)(*(int*)(resultAnim + 0x44) + 0x10);
        int count = minBones;  // reuse minBones for this array; it was stored in iVar23/local_28? Actually iVar23 was reused as loop counter.

        // Unrolled loop picking from B if element == -1 else from A
        int* pSrcA = intFromA;
        int* pSrcB = intFromB;
        int* pDst = intResult;
        int loopCount = count;

        // Process 4 pairs at a time (since 8 ints per iteration)
        if (count > 3) {
            int times = (count - 4U) / 4 + 1;
            loopCount = count - times * 4;
            do {
                pDst[0] = (pSrcB[0] == -1) ? pSrcA[0] : pSrcB[0];
                pDst[1] = (pSrcB[1] == -1) ? pSrcA[1] : pSrcB[1];
                pDst[2] = (pSrcB[2] == -1) ? pSrcA[2] : pSrcB[2];
                pDst[3] = (pSrcB[3] == -1) ? pSrcA[3] : pSrcB[3];
                pDst[4] = (pSrcB[4] == -1) ? pSrcA[4] : pSrcB[4];
                pDst[5] = (pSrcB[5] == -1) ? pSrcA[5] : pSrcB[5];
                pDst[6] = (pSrcB[6] == -1) ? pSrcA[6] : pSrcB[6];
                pDst[7] = (pSrcB[7] == -1) ? pSrcA[7] : pSrcB[7];
                pSrcA += 8;
                pSrcB += 8;
                pDst += 8;
                times--;
            } while (times != 0);
        }

        // Remainder single pairs
        for (; loopCount > 0; loopCount--) {
            pDst[0] = (pSrcB[0] == -1) ? pSrcA[0] : pSrcB[0];
            pDst[1] = (pSrcB[1] == -1) ? pSrcA[1] : pSrcB[1];
            pSrcA += 2;
            pSrcB += 2;
            pDst += 2;
        }

        // Copy remaining pairs from the longer array
        if (minBones < numBonesA) {
            memcpy(pDst, pSrcA, (numBonesA - minBones) * 8);
        } else if (minBones < numBonesB) {
            memcpy(pDst, pSrcB, (numBonesB - minBones) * 8);
        }
    }

processRootTransform:
    // Handle root transform (quaternion and translation) at +0x10..+0x2c
    if ((flags & 8) != 0) {
        return resultAnim;
    }

    bool isAnimBStatic = (*(char*)(animB + 0x30) != 2);
    *(char*)(resultAnim + 0x30) = 2; // default to additive?

    if (*(char*)(animA + 0x30) == 2) {
        // animA is additive; if animB is not additive, copy animA's root transform
        if (isAnimBStatic) {
            *(float4*)(resultAnim + 0x10) = *(float4*)(animA + 0x10); // quaternion
            *(float3*)(resultAnim + 0x20) = *(float3*)(animA + 0x20); // translation
            return resultAnim;
        }
        // both additive: blend via quaternion multiplication and translation addition
        FUN_0056cba0((undefined4*)(animA + 0x10), (undefined4*)(animB + 0x10), (undefined4*)(resultAnim + 0x10));
        *(float3*)(resultAnim + 0x20) = *(float3*)(animA + 0x20) + *(float3*)(animB + 0x20);
        *(float*)(resultAnim + 0x2c) = DAT_00e2b1a4; // constant
        return resultAnim;
    }

    if (isAnimBStatic) {
        *(char*)(resultAnim + 0x30) = 0; // mark as static
        return resultAnim;
    }

    // animA is static, animB is additive: copy animB's root transform
    *(char*)(resultAnim + 0x30) = 2;
    *(float4*)(resultAnim + 0x10) = *(float4*)(animB + 0x10);
    *(float3*)(resultAnim + 0x20) = *(float3*)(animB + 0x20);
    return resultAnim;
}