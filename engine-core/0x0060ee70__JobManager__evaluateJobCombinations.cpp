// FUNC_NAME: JobManager::evaluateJobCombinations
int JobManager::evaluateJobCombinations() {
    int bestPriority = 4; // Default priority (lower=higher? 4 is baseline)
    uint outerIndex = 0;

    // static arrays: g_jobTypePriorities[4] and g_jobSubTypePriorities[6]
    static uint g_jobTypePriorities[4]; // DAT_00e2ac50
    static uint g_jobSubTypePriorities[6]; // DAT_00e2ac28
    // These arrays are initialized elsewhere

    do {
        uint typePriority = *(uint*)((int)&g_jobTypePriorities + outerIndex);
        uint innerIndex = 0;
        do {
            uint subTypePriority = *(uint*)((int)&g_jobSubTypePriorities + innerIndex);

            // Local struct for combination evaluation
            struct JobCombo {
                uint typePriority;
                int unused1;
                int unused2;
                int unused3;
            } combo;
            combo.typePriority = typePriority;
            combo.unused1 = 0;
            combo.unused2 = 0;
            combo.unused3 = 0;

            // Evaluate this combination against the job manager's current state
            int result = FUN_0060ed60(*this, &combo); // Returns 9 if match? 0-9 scale

            if (result == 9) {
                // Check if a certain flag is set (field at +0x0C)
                if (*(char*)(this + 3) == '\0' && combo.unused1 == 0) {
                    if (bestPriority < 6) {
                        bestPriority = 5; // Set to 5 if no flag
                    }
                } else {
                    int subResult = FUN_0060ecb0(); // Further evaluation
                    if (subResult == 9) {
                        // Reallocate dynamic array at offset +0x140 (capacity), +0x144 (size), +0x148 (capacity)
                        int currentCapacity = this->field_0x148;
                        if (this->field_0x144 == currentCapacity) {
                            int newCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
                            FUN_0060fcb0(&this->field_0x140, newCapacity); // Grow array
                        }
                        // Add new entry at buffer[ size ] = { typePriority, subTypePriority }
                        uint* arrayBuffer = (uint*)this->field_0x140;
                        uint* entry = arrayBuffer + this->field_0x144 * 5; // 5 ints per entry? Actually offset 0x14 per entry (20 bytes)
                        this->field_0x144++;
                        if (entry != NULL) {
                            entry[0] = combo.typePriority;
                            entry[1] = subTypePriority;
                            FUN_006099f0(&combo.unused1); // Initialize something in combo
                        }
                        if (bestPriority < 10) {
                            bestPriority = 9;
                        }
                    } else {
                        if (bestPriority <= subResult) {
                            bestPriority = subResult;
                        }
                    }
                }
            } else {
                if (bestPriority <= result) {
                    bestPriority = result;
                }
            }

            if (combo.unused1 != 0) {
                FUN_009c8f10(combo.unused1); // Free temporary resource
            }
            innerIndex += 4;
        } while (innerIndex < 0x18); // 6 iterations
        outerIndex += 4;
    } while (outerIndex < 0x10); // 4 iterations

    return bestPriority;
}