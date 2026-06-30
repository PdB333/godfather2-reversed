// FUNC_NAME: ActionManager::processEventActions
// Address: 0x005ef5f0
// This function processes action groups stored at this+0x480 (5 groups of 12 bytes each).
// Each group has a count and a pointer to an array of 12-byte items (ActionItem).
// Each ActionItem contains a pointer to an object; if the object's tag at offset 0x28 equals 0x4d745030
// and a flag at this+0x470[index] is non-zero, it performs a hash-based lookup and dispatches a value.
// Constants used: FUN_00c9eac0/00c9eae0 (critical section), FUN_004d3bc0 (string op), FUN_005df050 (hash table lookup).
void ActionManager::processEventActions(int32_t actionIndex) {
    // Check if this manager is active (flag at +0x580)
    if (*(int32_t*)(this + 0x580) == 0) {
        return;
    }

    // Enter critical section (likely EARS lock)
    FUN_00c9eac0();

    // Begin iterating over 5 action groups starting at offset 0x480
    int32_t* groupPtr = (int32_t*)(this + 0x480);
    for (int32_t groupIdx = 0; groupIdx < 5; ++groupIdx) {
        int32_t itemCount = groupPtr[1];
        if (itemCount == 0) {
            goto nextGroup;
        }

        // Pointer to the start of the item array (base + 4)
        int32_t* itemArray = (int32_t*)(*groupPtr + 4);
        for (int32_t itemIdx = 0; itemIdx < itemCount; ++itemIdx) {
            // Each item: [objectPointer, field4, field8] (12 bytes)
            int32_t* objPtr = (int32_t*)(*itemArray);
            // Check magic tag at object offset 0x28
            if (objPtr != nullptr && *(int32_t*)(objPtr + 0x0A) == 0x4d745030) { // 0x28/4 = 0x0A
                // Check flag at this+0x470[itemIdx]
                int32_t* flags = (int32_t*)(this + 0x470);
                if (itemIdx >= 0 && flags[itemIdx] != 0) {
                    int32_t* savedGroupPtr = groupPtr;

                    // If this+4 is non-zero, clear callbacks for indices 0..5
                    if (*(int32_t*)(this + 4) != 0) {
                        for (int32_t idx = 0; idx < 6; ++idx) {
                            FUN_00ca4e90(idx, 0); // Set callback to zero
                        }
                    }

                    // Perform string operation (format or copy) with a static string
                    FUN_004d3bc0(&DAT_00e3f4f4);

                    // Hash a string (source unknown, possibly from object at some offset)
                    // local_18 is likely the string to hash; if null, use default
                    uint8_t* strToHash = /* local_18, perhaps from objPtr */ nullptr;
                    if (strToHash == nullptr) {
                        strToHash = (uint8_t*)&DAT_0120546e; // fallback ASCII
                    }
                    int32_t hash = 0;
                    for (uint8_t c = *strToHash; c != 0; ++strToHash) {
                        // Convert uppercase letters to lowercase
                        if (c >= 'A' && c <= 'Z') {
                            c += 0x20;
                        }
                        hash = hash * 0x1003f + c;
                    }

                    // Default value from global
                    uint32_t value = DAT_00e2b1a4;
                    // Lookup value from hash table if global pointer is valid
                    if (*(int32_t*)(DAT_01223508 + 0xC) != 0) {
                        uint32_t* result = (uint32_t*)FUN_005df050(&hash);
                        value = *result;
                    }

                    // If original string was non-null, call a function pointer (from local_c)
                    // Note: local_c is assigned below, but decompilation may be incomplete.
                    // For now, the call exists but no effect.
                    if (strToHash != /* original pointer, not saved */ nullptr) {
                        // (*local_c)(strToHash); // local_c unknown
                    }

                    // Determine final action index based on condition
                    int32_t finalIndex = actionIndex;
                    if (*(int32_t*)(this + 4) == 1) {
                        if (actionIndex == 0) {
                            FUN_00ca4e90(0, value);
                            finalIndex = 3;
                        } else if (actionIndex == 1) {
                            FUN_00ca4e90(2, value);
                            finalIndex = 4;
                        }
                    }
                    FUN_00ca4e90(finalIndex, value);

                    // Restore group pointer (though not used further)
                    groupPtr = savedGroupPtr;
                }
                break; // Found match, exit inner loop
            }
            itemArray += 3; // Move to next item (3 ints)
        }

    nextGroup:
        groupPtr += 3; // Move to next action group (3 ints)
    }

    // Leave critical section
    FUN_00c9eae0();
}