// FUNC_NAME: CharacterPhysics::collectContactPairs
void __thiscall CharacterPhysics::collectContactPairs(void)
{
    // Global default value (likely for invalid/uninitialized floats)
    float defaultVal = DAT_00e2eff4;

    // Store the input object pointer in the first field of this object (+0x00)
    *(int*)this = in_EAX;

    // Initialize some fields
    this->field_04 = 0;
    this->field_08 = 0;
    *(byte*)((int)this + 0x13) = 0;  // byte flag at +0x13

    // Get a pointer to the source data (from input object at +0x10)
    int* sourceData = *(int**)(in_EAX + 0x10);

    // Count of stored contact pairs (initially 0)
    uint pairCount = 0;
    // Index for iterating over source elements
    uint elementIndex = 0;

    // If the source data has elements (short at +0x5a)
    if (*(short*)(sourceData + 0x5a) != 0) {
        // Pointer to the array of pair floats (starting at this+3, i.e., offset 12)
        float* outputPair = (float*)(this + 3);
        // Loop over each element (size 0x30)
        do {
            // Get current element base
            int* element = *(int**)(sourceData + 0x38) + elementIndex * 0x30;
            // Number of sub-elements (ushort at +0x2e)
            uint subCount = *(unsigned short*)(element + 0x2e);
            if (subCount != 0) {
                // Array of pointers to sub-elements (at +0x28)
                int** subArray = *(int***)(element + 0x28);
                float bestMag0 = defaultVal;
                float bestMag1 = defaultVal;
                // Loop over sub-elements
                do {
                    // Assume each sub-element is a pointer to a struct: first float value, second is a pointer
                    float* subStruct = (float*)*subArray;
                    float mag0 = bestMag0;
                    // Check if the pointer at subStruct[1] +4 contains a magic constant (0x1f32d7d5)
                    if (*(int*)((int)subStruct[1] + 4) == 0x1f32d7d5) {
                        float val = *subStruct;
                        float squared = val * val;  // Square the first float
                        mag0 = squared;
                        // Check type field at subStruct+2 (short) – if not 2 and equals 3, update bestMag1
                        if (*(short*)(subStruct + 2) != 2 && *(short*)(subStruct + 2) == 3) {
                            bestMag1 = squared;
                        }
                    }
                    subArray++;
                    subCount--;
                    bestMag0 = mag0;
                } while (subCount != 0);

                // If both bestMag0 and bestMag1 are valid (>= 0)
                if (bestMag0 >= 0.0f && bestMag1 >= 0.0f) {
                    uint dupIndex = 0;
                    // Check if this pair already exists in the collected list (up to 8 pairs)
                    if (pairCount > 3) {
                        float* pair = (float*)(this + 6); // This seems to start at offset 24? Actually this+6 is 24 bytes, but earlier we have array at +12. Possibly a different check.
                        // Loop over groups of 8 floats (4 pairs)
                        do {
                            if ((pair[-3] == bestMag0 && pair[-2] == bestMag1) ||
                                (pair[-1] == bestMag0 && pair[0] == bestMag1) ||
                                (pair[1] == bestMag0 && pair[2] == bestMag1) ||
                                (pair[3] == bestMag0 && pair[4] == bestMag1)) {
                                break; // Found duplicate
                            }
                            dupIndex += 4;
                            pair += 8;
                        } while (dupIndex < pairCount - 3);
                    }

                    if (dupIndex < pairCount) {
                        // Check remaining pairs individually
                        float* pair = (float*)(this + dupIndex * 2 + 3);
                        do {
                            if (pair[0] == bestMag0 && pair[1] == bestMag1) break;
                            dupIndex++;
                            pair += 2;
                        } while (dupIndex < pairCount);
                    }

                    // If not duplicate and list not full, add the pair
                    if (dupIndex == pairCount && pairCount < 8) {
                        *outputPair = bestMag0;
                        outputPair[1] = bestMag1;
                        pairCount++;
                        outputPair += 2;
                    }
                }
            }
            elementIndex++;
        } while (elementIndex < *(unsigned short*)(sourceData + 0x5a));
    }

    // Store the final count at +0x4d
    *(byte*)((int)this + 0x4d) = (byte)pairCount;

    // If not all 8 slots used, fill remaining with default value
    if (pairCount < 8) {
        float* fillPair = (float*)(this + pairCount * 2 + 3);
        int remaining = 8 - pairCount;
        do {
            fillPair[1] = defaultVal;
            *fillPair = defaultVal;
            fillPair += 2;
            remaining--;
        } while (remaining != 0);
    }
}