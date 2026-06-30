// FUNC_NAME: ParticleEffect::update
void __thiscall ParticleEffect::update(int thisPtr, float deltaTime)
{
    // Thread-local storage for per-frame context (likely a slot index)
    int *contextBase = *(int **)(__readfsdword(0x2c));
    int slotIndex = *(int *)(contextBase + 8); // thread-specific slot offset

    // Check if already updated this frame
    if ((*(byte *)(*(int *)(thisPtr + 0x10) + slotIndex) & 1) != 0) {
        return;
    }

    // Update fade timer at +0x38
    float *timer = (float *)(thisPtr + 0x38);
    if (*timer > 0.0f) {
        *timer -= deltaTime;
        if (*timer <= 0.0f) {
            *timer = 0.0f;
            // Signal that timer has expired (set flag)
            uint *flagPtr = (uint *)(*(int *)(thisPtr + 0x10) + slotIndex);
            *flagPtr |= 1;
        }
    }

    // Particle list: pointer at +0x40, count at +0x58 (relative to that pointer)
    int listPtr = *(int *)(thisPtr + 0x40);
    uint itemCount = *(uint *)(listPtr + 0x58 + slotIndex);
    float *currentPos = (float *)(*(int *)(thisPtr + 0x10) + 0x80 + slotIndex);
    float posX = currentPos[0];
    float posY = currentPos[1];
    float posZ = currentPos[2];
    float posW = currentPos[3]; // uninitialized in this path

    // Iterate backwards over list items
    uint idx = itemCount;
    while (idx > 0) {
        idx--;
        int itemBase = listPtr + slotIndex;
        int itemPtr = *(int *)(itemBase + 8 + idx * 8);
        uint itemData = *(uint *)(itemBase + 0xc + idx * 8);

        if (itemPtr == 0) {
            // Remove the item from the list (shift last into this slot)
            uint count = *(uint *)(itemBase + 0x58);
            if (idx < count) {
                if (idx < count - 1) {
                    *(int *)(itemBase + 8 + idx * 8) = *(int *)(itemBase + 8 + (count - 1) * 8);
                    *(uint *)(itemBase + 0xc + idx * 8) = *(uint *)(itemBase + 0xc + (count - 1) * 8);
                }
                *(int *)(itemBase + 0x58) = *(int *)(itemBase + 0x58) - 1;
                int *lastSlot = (int *)(itemBase + 8 + *(int *)(itemBase + 0x58) * 8);
                if (lastSlot != 0) {
                    lastSlot[0] = 0;
                    lastSlot[1] = 0;
                }
            }
            continue;
        }

        // Check if the item is still valid (some internal object reference)
        int internalPtr = *(int *)(itemPtr + 0x24 + slotIndex);
        if (internalPtr == 0) {
            // Destroy item
            FUN_004f7bc0(itemPtr, itemData);
            // Remove from list (similar logic as above)
            int base2 = slotIndex + 8 + *(int *)(thisPtr + 0x40);
            uint count2 = *(uint *)(base2 + 0x50); // note: different offset? In this path it's +0x50
            if (idx < count2) {
                if (idx < count2 - 1) {
                    *(undefined4 *)(base2 + idx * 8) = *(undefined4 *)(base2 + -8 + count2 * 8);
                    *(undefined4 *)(base2 + 4 + idx * 8) = *(undefined4 *)(base2 + -4 + count2 * 8);
                }
                *(int *)(base2 + 0x50) = *(int *)(base2 + 0x50) - 1;
                uint *last = (uint *)(base2 + *(int *)(base2 + 0x50) * 8);
                if (last) {
                    last[0] = 0;
                    last[1] = 0;
                }
            }
        }
        else {
            // Compute squared distance from current position to item's position
            float dx = posX - *(float *)(internalPtr + 0x70);
            float dy = posY - *(float *)(internalPtr + 0x74);
            float dz = posZ - *(float *)(internalPtr + 0x78);
            // Get a threshold from some config
            float threshold = *(float *)(*(int *)(*(int *)(thisPtr + 4) + 0x10) + 0x20) + *(float *)(internalPtr + 0x28);
            if (threshold * threshold <= dx*dx + dy*dy + dz*dz) {
                // Too far: destroy item
                FUN_004f7bc0(itemPtr, itemData);
                FUN_004fc010();
            }
        }
    }

    // Second pass: call a function for each active item?
    int countAfter = *(int *)(*(int *)(thisPtr + 0x40) + 0x58 + slotIndex);
    char checkResult = FUN_004fc270(global_DAT_01205510, *(int *)(thisPtr + 0x40) + slotIndex);
    float constZero = DAT_00e2b1a4; // 0.0f
    if ((checkResult == 1) &&
        (countAfter < *(int *)(*(int *)(thisPtr + 0x40) + 0x58 + slotIndex))) {
        do {
            int itemPtr2 = *(int *)(*(int *)(thisPtr + 0x40) + 8 + countAfter * 8 + slotIndex);
            if (itemPtr2 != 0) {
                itemPtr2 += slotIndex;
                int someVal = *(int *)(itemPtr2 + 0x10);
                if (someVal < 1) {
                    someVal = *(int *)(*(int *)(thisPtr + 0x3c) + 0x8c);
                }
                else if (*(float *)(*(int *)(itemPtr2 + 0x24) + 0x3c) == constZero) {
                    goto nextIter;
                }
                if (someVal > 0) {
                    FUN_00519450(someVal);
                    constZero = DAT_00e2b1a4;
                }
            }
nextIter:
            slotIndex = *(int *)(slotIndex + 0); // actually slotIndex is from earlier?? careful
            // The code uses iVar13 which is slotIndex from earlier? This part is messy
            // Actually the original uses iVar13 as slotIndex from the start? need to re-evaluate.
        } while (countAfter < ... );
    }

    // Process property A (offset +0x150 type, +0x154 value)
    int propAType = *(int *)(thisPtr + 0x150);
    float propAValue;
    switch (propAType) {
        case 0:
            propAValue = *(float *)(thisPtr + 0x154);
            break;
        case 1:
            if (*(int *)(thisPtr + 0x154) != 0)
                propAValue = *(float *)(*(int *)(thisPtr + 0x154) + 0x10);
            break;
        case 2: {
            int idx2 = *(int *)(thisPtr + 0x154) + 0xc;
            int base3 = *(int *)(thisPtr + 4) + idx2 * 0x14;
            float localVal = 0.0f;
            if (*(int *)(base3 + 4) != 0) {
                (**(code **)(**(int **)(base3 + 4) + 0x2c))(0, &localVal);
                propAValue = localVal;
            }
            else
                propAValue = 0.0f;
            break;
        }
        default:
            propAValue = 0.0f;
    }
    // Write to slot+0x5c
    *(float *)(slotIndex + 0x5c + *(int *)(thisPtr + 0x40)) = propAValue;

    // Process property B (+0x158 type, +0x15c value)
    int propBType = *(int *)(thisPtr + 0x158);
    float propBValue;
    switch (propBType) {
        case 0:
            propBValue = *(float *)(thisPtr + 0x15c);
            break;
        case 1:
            if (*(int *)(thisPtr + 0x15c) != 0)
                propBValue = *(float *)(*(int *)(thisPtr + 0x15c) + 0x10);
            break;
        case 2: {
            int idx3 = *(int *)(thisPtr + 0x15c) + 0xc;
            int base4 = *(int *)(thisPtr + 4) + idx3 * 0x14;
            float localVal2 = 0.0f;
            if (*(int *)(base4 + 4) != 0) {
                (**(code **)(**(int **)(base4 + 4) + 0x2c))(0, &localVal2);
                propBValue = localVal2;
            }
            else
                propBValue = 0.0f;
            break;
        }
        default:
            propBValue = 0.0f;
    }
    *(float *)(slotIndex + 0x84 + *(int *)(thisPtr + 0x40)) = propBValue;

    // If flags indicate, write array of 9 floats and 9 ints
    int flags = *(int *)(*(int *)(thisPtr + 0x3c) + 0x50);
    if ((flags & 3) != 0) {
        int i = 1;
        int offset = 0x88; // index for int array
        do {
            float floatVal = 0.0f;
            float indexFloat = (float)i * global_DAT_00e44944;
            if ((flags & 1) != 0) {
                // Evaluate property A again with index
                switch (*(int *)(thisPtr + 0x150)) {
                    case 0:
                        floatVal = *(float *)(thisPtr + 0x154);
                        break;
                    case 1:
                        if (*(int *)(thisPtr + 0x154) != 0)
                            floatVal = *(float *)(*(int *)(thisPtr + 0x154) + 0x10);
                        break;
                    case 2: {
                        int idx4 = *(int *)(thisPtr + 0x154) + 0xc;
                        int base5 = *(int *)(thisPtr + 4) + idx4 * 0x14;
                        float local3 = 0.0f;
                        if (*(int *)(base5 + 4) != 0) {
                            (**(code **)(**(int **)(base5 + 4) + 0x2c))(&indexFloat, &local3);
                            floatVal = local3;
                        }
                        break;
                    }
                }
                // Write to float array starting at +0x60
                *(float *)(slotIndex + (offset - 0x28) + *(int *)(thisPtr + 0x40)) = floatVal;
            }
            int intVal = 0;
            if ((flags & 2) != 0) {
                // Evaluate property B with index
                switch (*(int *)(thisPtr + 0x158)) {
                    case 0:
                        intVal = *(int *)(thisPtr + 0x15c);
                        break;
                    case 1:
                        if (*(int *)(thisPtr + 0x15c) != 0)
                            intVal = *(int *)(*(int *)(thisPtr + 0x15c) + 0x10);
                        break;
                    case 2: {
                        int idx5 = *(int *)(thisPtr + 0x15c) + 0xc;
                        int base6 = *(int *)(thisPtr + 4) + idx5 * 0x14;
                        int local4 = 0;
                        if (*(int *)(base6 + 4) != 0) {
                            (**(code **)(**(int **)(base6 + 4) + 0x2c))(&indexFloat, &local4);
                            intVal = local4;
                        }
                        break;
                    }
                }
                // Write to int array starting at +0x88
                *(int *)(slotIndex + offset + *(int *)(thisPtr + 0x40)) = intVal;
            }
            offset += 4;
            i++;
        } while (offset < 0xa9);
    }

    // Update accumulated time and velocities
    float *accTime = (float *)(thisPtr + 0x160);
    *accTime += deltaTime;

    float *velA = (float *)(thisPtr + 0x168);
    float configA = *(float *)(*(int *)(thisPtr + 0x3c) + 0x44);
    if (configA != 0.0f) {
        *velA = configA * deltaTime + *velA;
        if (*velA <= DAT_00e2b1a4) {
            if (*velA < 0.0f)
                *velA = 0.0f;
        }
        else {
            *velA = 0.0f;
        }
    }

    float *velB = (float *)(thisPtr + 0x164);
    float configB = *(float *)(*(int *)(thisPtr + 0x3c) + 0x48);
    if (configB != 0.0f) {
        *velB = configB * deltaTime + *velB;
        if (*velB <= DAT_00e2b1a4) {
            if (*velB < 0.0f)
                *velB = 0.0f;
        }
        else {
            *velB = 0.0f;
        }
    }

    // Process follow target if present (+0x16c)
    int followTarget = *(int *)(thisPtr + 0x16c);
    if (followTarget != 0) {
        if (*(int *)(followTarget + 0x10) == 0) {
            // Cleanup
            if (*(int *)(followTarget + 8) != 0) {
                *(int *)(followTarget + 8) = 0;
                *(int *)(followTarget + 8) = 0;
            }
            // Mark as updated
            uint *flagPtr2 = (uint *)(*(int *)(thisPtr + 0x10) + slotIndex);
            *flagPtr2 |= 1;
            return;
        }

        // Iterate over list again, compute distance to target
        slotIndex = *(int *)(slotIndex + 0); // ???
        int idxList = 0;
        int listCount = *(int *)(*(int *)(thisPtr + 0x40) + 0x58 + slotIndex);
        if (listCount > 0) {
            do {
                float *listItemPtr = *(float **)(*(int *)(thisPtr + 0x40) + 8 + idxList * 8 + slotIndex);
                if (listItemPtr != 0) {
                    float val1 = *(float *)((int)listItemPtr + 0x2c + slotIndex);
                    float val2 = *(float *)((int)listItemPtr + 0x28 + slotIndex);
                    float diff = val1 - val2;
                    if (diff < 0.0f) diff = 0.0f;
                    // LCG for pseudo-random
                    int randIdx = global_DAT_0119478c - 1;
                    int randIdx2 = global_DAT_0119478c + 2;
                    if (randIdx < 0) randIdx = 0x13;
                    else if (randIdx2 > 0x13) randIdx2 = global_DAT_0119478c - 0x12;
                    global_DAT_01194790[randIdx] += global_DAT_01194790[randIdx2];
                    float randVal = (float)(global_DAT_01194790[randIdx] & 0x7fffff | 0x3f800000);
                    diff = (randVal - 1.0f) * val2 + diff;
                    global_DAT_0119478c = randIdx;

                    if ((*(int *)((int)listItemPtr + 0x14 + slotIndex) != 0) ||
                        (*(int *)((int)listItemPtr + 0x24 + slotIndex) != 0)) {
                        float thisItemPtr = (float)listItemPtr;
                        int internalPtr2;
                        if (*(int *)((int)listItemPtr + 0x1c + slotIndex) == 0) {
                            internalPtr2 = *(int *)((int)listItemPtr + 0x14 + slotIndex);
                            int maybe = 0;
                            if (internalPtr2 != 0) maybe = internalPtr2 + slotIndex;
                            if (maybe != 0) goto label1;
                            char result = (**(code **)(**(int **)((int)listItemPtr + 0x24 + slotIndex) + 0x18))(someStackArray, diff);
                            // reset constants
                        }
                        else {
label1:
                            result = FUN_00518f00(*(int *)((int)listItemPtr + 0x24 + slotIndex) + 0x30);
                        }
                        if (result != 0) {
                            FUN_00414aa0();
                            int matrixPtr = *(int *)((int)listItemPtr + 0x24 + slotIndex);
                            // Multiply position by bone matrix
                            float transformedX = posX * *(float *)(matrixPtr + 0x40) + posY * *(float *)(matrixPtr + 0x50) + posZ * *(float *)(matrixPtr + 0x60) + *(float *)(matrixPtr + 0x70);
                            float transformedY = posX * *(float *)(matrixPtr + 0x44) + posY * *(float *)(matrixPtr + 0x54) + posZ * *(float *)(matrixPtr + 0x64) + *(float *)(matrixPtr + 0x74);
                            float transformedZ = posX * *(float *)(matrixPtr + 0x48) + posY * *(float *)(matrixPtr + 0x58) + posZ * *(float *)(matrixPtr + 0x68) + *(float *)(matrixPtr + 0x78);
                            float transformedW = posX * *(float *)(matrixPtr + 0x4c) + posY * *(float *)(matrixPtr + 0x5c) + posZ * *(float *)(matrixPtr + 0x6c) + *(float *)(matrixPtr + 0x7c);
                            // Prepare data for movement
                            float dirX = transformedX - currentPos[0];
                            float dirY = transformedY - currentPos[1];
                            float dirZ = transformedZ - currentPos[2];
                            float distSq = dirX*dirX + dirY*dirY + dirZ*dirZ;
                            float invDist = 0.0f;
                            if (distSq > global_DAT_00e2cbe0) {
                                invDist = 1.0f / sqrt(distSq);
                            }
                            dirX *= invDist;
                            dirY *= invDist;
                            dirZ *= invDist;
                            // Call movement function
                            FUN_0051c430(*(int *)(thisPtr + 0x16c), &transformedX);
                        }
                    }
                }
                idxList++;
            } while (idxList < listCount);
        }
    }
}