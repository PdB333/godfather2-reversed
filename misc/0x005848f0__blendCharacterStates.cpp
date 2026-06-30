// FUNC_NAME: blendCharacterStates
int blendCharacterStates(void* sourceA, void* sourceB, float blendFactor, uint flags)
{
    // Validate inputs
    if (!sourceA || !sourceB) return 0;
    void* dest = getBlendDestination(); // FUN_0056fdd0
    if (!dest) return 0;

    // If flag 4 is set, skip the main blend and go to final section
    if ((flags & 4) != 0) goto finalSection;

    // Get element counts from the two sources (stored at +0x38 -> +0x0C as int)
    int countA = *(int*)(*(int*)((char*)sourceA + 0x38) + 0x0C);
    int countB = *(int*)(*(int*)((char*)sourceB + 0x38) + 0x0C);
    int minCount = (countA < countB) ? countA : countB;

    // Lock the source buffers (increment reference counts)
    lockBuffer(sourceB); // FUN_0056f800
    lockBuffer(sourceA);
    // Lock the buffer with the larger count (to ensure it stays valid)
    if (countB > countA) {
        lockBuffer(sourceB);
    } else {
        lockBuffer(sourceA);
    }

    // Pointers to data arrays
    // Source A: byte array at +0x34+0x14, block32 array at +0x38+0x10
    char* bytePtrA = (char*)(*(int*)((char*)sourceA + 0x34) + 0x14);
    char* block32PtrA = (char*)(*(int*)((char*)sourceA + 0x38) + 0x10);

    // Destination: byte array at dest+0x34+0x14, block32 at dest+0x38+0x10
    char* byteDest = (char*)(*(int*)((char*)dest + 0x34) + 0x14);
    char* block32Dest = (char*)(*(int*)((char*)dest + 0x38) + 0x10);

    // Check if destination has a 16-byte block array (at +0x3C)
    if (*(int*)((char*)dest + 0x3C) == 0) {
        // Simple case: only byte and 32-byte blocks
        char* bytePtrB = (char*)(*(int*)((char*)sourceB + 0x34) + 0x14);
        char* block32PtrB = (char*)(*(int*)((char*)sourceB + 0x38) + 0x10);
        char* byteDest2 = byteDest; // alias for clarity
        char* block32Dest2 = block32Dest;

        // Check if both sources have a flag at +0x10 indicating special blend mode
        bool useSpecialBlend = (*(char*)((char*)sourceA + 0x10) != 0) && (*(char*)((char*)sourceB + 0x10) != 0);
        if (!useSpecialBlend) {
            // Simple lerp for each element
            for (int i = 0; i < minCount; i++) {
                lerpByteAndBlock32(&bytePtrB, blendFactor); // FUN_00584860
                bytePtrA++;
                bytePtrB++;
                byteDest2++;
                block32PtrA += 0x20;
                block32PtrB += 0x20;
                block32Dest2 += 0x20;
            }
        } else {
            // Special blend with weight preparation
            prepareBlend(); // FUN_0056f620
            for (int i = 0; i < minCount; i++) {
                lerpByteWithWeight(&bytePtrA, blendFactor); // FUN_005830d0
                bytePtrA++;
                bytePtrB++;
                byteDest2++;
                block32PtrA += 0x20;
                block32PtrB += 0x20;
                block32Dest2 += 0x20;
            }
        }

        // Copy remaining elements from the longer source
        if (minCount < countA) {
            int remaining = countA - minCount;
            memcpy(byteDest2, bytePtrA, remaining);
            memcpy(block32Dest2, block32PtrA, remaining * 0x20);
        } else if (minCount < countB) {
            int remaining = countB - minCount;
            memcpy(byteDest2, bytePtrB, remaining);
            memcpy(block32Dest2, block32PtrB, remaining * 0x20);
        }
    } else {
        // Complex case: also includes 16-byte blocks
        char* block16PtrA = (char*)(*(int*)((char*)sourceA + 0x3C) + 0x10);
        char* bytePtrB = (char*)(*(int*)((char*)sourceB + 0x34) + 0x14);
        char* block16PtrB = (char*)(*(int*)((char*)sourceB + 0x3C) + 0x10);
        char* block32PtrB = (char*)(*(int*)((char*)sourceB + 0x38) + 0x10);
        char* byteDest2 = byteDest;
        char* block16Dest = (char*)(*(int*)((char*)dest + 0x3C) + 0x10);
        char* block32Dest2 = block32Dest;

        bool useSpecialBlend = (*(char*)((char*)sourceA + 0x10) != 0) && (*(char*)((char*)sourceB + 0x10) != 0);
        if (!useSpecialBlend) {
            for (int i = 0; i < minCount; i++) {
                lerpByteBlock32Block16(&bytePtrB, &block32PtrA, &bytePtrA, blendFactor); // FUN_005865e0
                block16PtrA += 0x10;
                block16PtrB += 0x10;
                block16Dest += 0x10;
                bytePtrA++;
                bytePtrB++;
                byteDest2++;
                block32PtrA += 0x20;
                block32PtrB += 0x20;
                block32Dest2 += 0x20;
            }
        } else {
            prepareBlend();
            for (int i = 0; i < minCount; i++) {
                lerpByteWithWeight(&bytePtrA, blendFactor); // FUN_005830d0
                lerpBlock16(&bytePtrB, blendFactor); // FUN_00583100
                block16PtrA += 0x10;
                block16PtrB += 0x10;
                block16Dest += 0x10;
                bytePtrA++;
                bytePtrB++;
                byteDest2++;
                block32PtrA += 0x20;
                block32PtrB += 0x20;
                block32Dest2 += 0x20;
            }
        }

        // Copy remaining elements from the longer source
        if (minCount < countA) {
            int remaining = countA - minCount;
            memcpy(byteDest2, bytePtrA, remaining);
            memcpy(block32Dest2, block32PtrA, remaining * 0x20);
            memcpy(block16Dest, block16PtrA, remaining * 0x10);
        } else if (minCount < countB) {
            int remaining = countB - minCount;
            memcpy(byteDest2, bytePtrB, remaining);
            memcpy(block32Dest2, block32PtrB, remaining * 0x20);
            memcpy(block16Dest, block16PtrB, remaining * 0x10);
        }
    }

finalSection:
    // Blend float arrays at +0x40
    if (*(int*)((char*)dest + 0x40) != 0) {
        int floatCount = *(int*)(*(int*)((char*)dest + 0x40) + 0x0C); // number of floats
        float* floatSrcA = (float*)(*(int*)((char*)sourceA + 0x40) + 0x10);
        float* floatSrcB = (float*)(*(int*)((char*)sourceB + 0x40) + 0x10);
        float* floatDest = (float*)(*(int*)((char*)dest + 0x40) + 0x10);

        // Linear interpolation for each float
        for (int i = 0; i < floatCount; i++) {
            floatDest[i] = floatSrcA[i] + (floatSrcB[i] - floatSrcA[i]) * blendFactor;
        }
    }

    // Blend integer pair arrays at +0x44 (special handling)
    float threshold = DAT_00e2b1a4; // some global threshold
    if (*(int*)((char*)dest + 0x44) != 0) {
        int pairCount = minCount; // reuse minCount from earlier? Actually the count is stored at +0x44+0x0C? The code uses local_44 which is minCount. So it uses the same count as the byte/block arrays.
        int* intPairSrcA = (int*)(*(int*)((char*)sourceA + 0x44) + 0x10);
        int* intPairSrcB = (int*)(*(int*)((char*)sourceB + 0x44) + 0x10);
        int* intPairDest = (int*)(*(int*)((char*)dest + 0x44) + 0x10);

        // Process in groups of 4 pairs (8 ints) for efficiency
        int i = 0;
        for (; i + 4 <= pairCount; i += 4) {
            // Process 4 pairs per iteration
            for (int j = 0; j < 4; j++) {
                int idx = i + j;
                int valA = intPairSrcA[idx * 2];
                int valB = intPairSrcB[idx * 2];
                float timeA = (float)intPairSrcA[idx * 2 + 1];
                float timeB = (float)intPairSrcB[idx * 2 + 1];

                intPairDest[idx * 2] = valB; // default to sourceB value
                if (blendFactor > 0.0f) {
                    if (blendFactor >= threshold) {
                        intPairDest[idx * 2] = valB;
                    } else if (valA != valB) {
                        if (valB == -1) {
                            intPairDest[idx * 2] = 7; // special sentinel
                            timeB = threshold;
                        } else {
                            intPairDest[idx * 2] = valB;
                        }
                    }
                } else {
                    intPairDest[idx * 2] = valA;
                }
                intPairDest[idx * 2 + 1] = (int)((timeB - timeA) * blendFactor + timeA);
            }
        }
        // Handle remaining pairs
        for (; i < pairCount; i++) {
            int valA = intPairSrcA[i * 2];
            int valB = intPairSrcB[i * 2];
            float timeA = (float)intPairSrcA[i * 2 + 1];
            float timeB = (float)intPairSrcB[i * 2 + 1];

            intPairDest[i * 2] = valB;
            if (blendFactor > 0.0f) {
                if (blendFactor >= threshold) {
                    intPairDest[i * 2] = valB;
                } else if (valA != valB) {
                    if (valB == -1) {
                        intPairDest[i * 2] = 7;
                        timeB = threshold;
                    } else {
                        intPairDest[i * 2] = valB;
                    }
                }
            } else {
                intPairDest[i * 2] = valA;
            }
            intPairDest[i * 2 + 1] = (int)((timeB - timeA) * blendFactor + timeA);
        }

        // Copy remaining pairs if one source is longer (using the same minCount logic)
        if (minCount < countA) {
            int remaining = countA - minCount;
            memcpy(intPairDest + minCount * 2, intPairSrcA + minCount * 2, remaining * 8);
        } else if (minCount < countB) {
            int remaining = countB - minCount;
            memcpy(intPairDest + minCount * 2, intPairSrcB + minCount * 2, remaining * 8);
        }
    }

    // Final section: blend root data at +0x30 and +0x10 (if flag 8 not set)
    if ((flags & 8) == 0) {
        char* rootSrcA = (char*)sourceA + 0x30;
        char* rootSrcB = (char*)sourceB + 0x30;
        char* rootDest = (char*)dest + 0x30;

        char* extraSrcA = (char*)sourceA + 0x10;
        char* extraSrcB = (char*)sourceB + 0x10;
        char* extraDest = (char*)dest + 0x10;

        if ((flags & 0x100) == 0) {
            // Simple blend of root data
            lerpByteAndBlock32(&rootSrcB, blendFactor); // FUN_00584860
            return (int)dest;
        } else {
            // Copy from sourceB directly and set a flag
            *rootDest = 2;
            *(int*)(extraDest + 0) = *(int*)(extraSrcB + 0);
            *(int*)(extraDest + 4) = *(int*)(extraSrcB + 4);
            *(int*)(extraDest + 8) = *(int*)(extraSrcB + 8);
            *(int*)(extraDest + 12) = *(int*)(extraSrcB + 12);
            *(int*)(extraDest + 16) = *(int*)(extraSrcB + 16);
            *(int*)(extraDest + 20) = *(int*)(extraSrcB + 20);
            *(int*)(extraDest + 24) = *(int*)(extraSrcB + 24);
            *(int*)(extraDest + 28) = *(int*)(extraSrcB + 28);
        }
    }

    return (int)dest;
}