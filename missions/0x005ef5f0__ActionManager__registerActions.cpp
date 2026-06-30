// FUNC_NAME: ActionManager::registerActions
void ActionManager::registerActions(int actionIndex) {
    // +0x580: pointer to some resource container
    if (*(int*)(this + 0x580) == 0) {
        return;
    }

    // Lock (likely critical section)
    FUN_00c9eac0();

    // +0x480: array of 5 action category slots (each 0xC bytes)
    int* categorySlot = (int*)(this + 0x480);
    int categoryCount = 5;

    do {
        // Each slot: [0] = pointer to array of action definitions, [1] = count, [2] = unknown
        int actionDefCount = categorySlot[1];
        if (actionDefCount != 0) {
            int* actionDefPtr = (int*)(*categorySlot + 4); // start at offset 4 of first definition
            uint index = 0;
            while (index < (uint)actionDefCount) {
                // Each action definition: 12 bytes, with a pointer at offset 4 to an object
                int* objectPtr = (int*)*actionDefPtr; // dereference the pointer at offset 4
                // Check object type ID at +0x28
                if (objectPtr[0x28 / 4] == 0x4d745030) { // "MtP0" magic
                    // Found matching action type
                    if (*(int*)(this + 4) != 0) {
                        // Clear previous action mappings for indices 0..5
                        for (uint i = 0; i < 6; i++) {
                            FUN_00ca4e90(i, 0);
                        }
                    }

                    // Hash the action name string (local_18)
                    FUN_004d3bc0(&DAT_00e3f4f4); // likely a debug string or format
                    byte* nameStr = local_18;
                    if (nameStr == nullptr) {
                        nameStr = &DAT_0120546e; // default empty string
                    }
                    int hash = 0;
                    while (*nameStr != 0) {
                        byte c = *nameStr;
                        nameStr++;
                        if (c >= 'A' && c <= 'Z') {
                            c += 0x20; // tolower
                        }
                        hash = hash * 0x1003f + c;
                    }

                    // Resolve hash to an ID via global lookup table
                    uint resolvedId = DAT_00e2b1a4;
                    if (*(int*)(DAT_01223508 + 0xC) != 0) {
                        int* hashPtr = &hash;
                        resolvedId = *(uint*)FUN_005df050(&hashPtr);
                    }

                    // Cleanup name string if needed
                    if (local_18 != nullptr) {
                        local_c(local_18); // function pointer for deallocation
                    }

                    // Register the action mapping
                    int finalIndex = actionIndex;
                    if (*(int*)(this + 4) == 1) {
                        // Special case: mode 1
                        if (actionIndex == 0) {
                            FUN_00ca4e90(0, resolvedId);
                            finalIndex = 3;
                        } else if (actionIndex == 1) {
                            FUN_00ca4e90(2, resolvedId);
                            finalIndex = 4;
                        }
                    }
                    FUN_00ca4e90(finalIndex, resolvedId);
                }
                index++;
                actionDefPtr += 3; // move to next definition (12 bytes)
            }
        }
        categorySlot += 3; // move to next category slot (12 bytes)
        categoryCount--;
    } while (categoryCount != 0);

    // Unlock
    FUN_00c9eae0();
}