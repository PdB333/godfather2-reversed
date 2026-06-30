// FUNC_NAME: ObjectManager::handleObjectMessage
void __thiscall ObjectManager::handleObjectMessage(int param_2) {
    // param_1: this pointer, param_2: pointer to message data
    // +0x00: message ID (magic)
    // +0x04: payload (varies)

    // Lock mutex
    FUN_00ab4db0(&DAT_00e2e3d4);

    int* msgData = reinterpret_cast<int*>(param_2);
    int msgId = *msgData;

    if (msgId == 0x30b00adf) { // Ghost remove / update
        // Structure offsets in this:
        // +0x20: numEntries (uint)
        // +0x1c: entries (array of Entry, each 0x28 bytes)
        // +0x70: updateMode (bool)

        uint numEntries = *(uint*)(this + 0x20);
        int* entryArray = *(int**)(this + 0x1c);
        int* targetEntry = nullptr; // entry to match
        uint i = 0;

        // Search for matching entry by first 4 ints (GhostID? or key)
        for (; i < numEntries; ++i) {
            int* entry = entryArray + i * 10; // 10 ints per entry
            if (entry[0] == msgData[3] && entry[1] == msgData[4] &&
                entry[2] == msgData[5] && entry[3] == msgData[6]) {
                targetEntry = entry;
                break;
            }
        }

        if (*(char*)(this + 0x70) != '\0') {
            // Update mode: modify found entry
            targetEntry[9] = msgData[2]; // set some field
            FUN_00462ec0(targetEntry); // process update
            FUN_00ab4e70(); // unlock mutex
            return;
        }

        // Removal mode: find overlapping entry (if any) to compact
        int* overlapEntry = nullptr;
        if (numEntries != 0) {
            for (uint j = 0; j < numEntries; ++j) {
                int* entry = entryArray + j * 10;
                // Skip the exact match, but find entry that matches targetEntry's first 4 ints
                if (!(entry[0] == msgData[3] && entry[1] == msgData[4] &&
                      entry[2] == msgData[5] && entry[3] == msgData[6]) &&
                    (entry[0] == targetEntry[0] && entry[1] == targetEntry[1] &&
                     entry[2] == targetEntry[2] && entry[3] == targetEntry[3])) {
                    overlapEntry = entryArray + j * 10;
                    break;
                }
            }
        }

        if (targetEntry[7] != 0) {
            FUN_00462880(this, targetEntry, overlapEntry); // handle removal callback
        }
        FUN_005708f0(); // some stats update

        int index = (targetEntry - entryArray) / 10;
        if (index != static_cast<int>(numEntries) - 1) {
            // Swap with last entry (compact the array)
            int* lastEntry = entryArray + (numEntries - 1) * 10;
            int* curEntry = entryArray + index * 10;
            curEntry[0] = lastEntry[0];
            curEntry[1] = lastEntry[1];
            curEntry[2] = lastEntry[2];
            curEntry[3] = lastEntry[3];
            curEntry[4] = lastEntry[4];
            curEntry[5] = lastEntry[5];
            FUN_00463790(); // update internal state after swap
            curEntry[9] = lastEntry[9];
        }
        *(int*)(this + 0x20) = *(int*)(this + 0x20) - 1; // decrement count

        // Check if the now-last entry has a non-zero field at offset 0x18 (slot 6)
        int lastMemory = *(int*)(entryArray + (numEntries - 1) * 10 + 6); // index 6 = offset 0x18
        if (lastMemory != 0) {
            FUN_009c8f10(lastMemory); // free memory
            FUN_00ab4e70(); // unlock mutex
            return;
        }
    }
    else if (msgId == 0x38860031) { // Object remove (connection/controller)
        // Structure:
        // +0x20: numEntries
        // +0x1c: entryArray
        // +0x14: numChildren (global)
        // +0x10: childArray (global)
        // +0x0c: vtablePtr (pointer to object with vtable)

        int objectId = msgData[2]; // ID to remove
        uint numEntries = *(uint*)(this + 0x20);
        int* entryArray = *(int**)(this + 0x1c);
        uint i = 0;

        // Remove objectId from each entry's child list
        for (; i < numEntries; ++i) {
            int* entry = entryArray + i * 10;
            uint childCount = *(uint*)(entry + 7); // offset 0x1c
            if (childCount != 0) {
                int* childList = *(int**)(entry + 6); // offset 0x18
                uint j = 0;
                for (; j < childCount; ++j) {
                    if (childList[j] == objectId) {
                        // Remove child entry
                        FUN_005707f0(objectId); // pre-remove cleanup
                        if (j != childCount - 1) {
                            childList[j] = childList[childCount - 1]; // compact
                        }
                        *(int*)(entry + 7) = childCount - 1;
                        break;
                    }
                }
            }
        }

        // Remove objectId from global child list
        uint globalChildCount = *(uint*)(this + 0x14);
        int* globalChildList = *(int**)(this + 0x10);
        uint k = 0;
        for (; k < globalChildCount; ++k) {
            if (globalChildList[k] == objectId) {
                if (k != globalChildCount - 1) {
                    globalChildList[k] = globalChildList[globalChildCount - 1];
                }
                *(int*)(this + 0x14) = globalChildCount - 1;
                break;
            }
        }

        // Cleanup the object itself
        int* vtablePtr = *(int**)(this + 0xc); // pointer to an object with vtable
        FUN_00573cb0(); // lock something
        int** objData = *(int***)(objectId + 0x30);
        FUN_00573910(); // unlock something
        FUN_009c8f10(*objData[0]); // free first element of objData
        FUN_005875f0(); // cleanup

        // Call virtual destructor? vtable[1] with argument 0
        (**(code**)(*vtablePtr + 4))(*(int*)(objectId + 0x28), 0);
        *(int*)(objectId + 0x28) = 0;
        *(int*)(objectId + 0x30) = 0;
        *(int*)(objectId + 0x2c) = 0;
    }

    FUN_00ab4e70(); // unlock mutex
    return;
}