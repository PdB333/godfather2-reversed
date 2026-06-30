// FUNC_NAME: GameManager::clearSen0References
void __fastcall GameManager::clearSen0References(int this)
{
    uint itemIndex;
    int *groupPtr;
    int *currentItemPtr;
    int *extraArrayBase;
    int localBuffer[3];
    
    *(char *)(this + 8) = 0; // some boolean flag (offset +0x8)
    if (*(int *)(this + 0x580) != 0 && *(int *)(this + 0x56c) != 0) { // network manager and another manager must be valid
        beginLock(); // FUN_00c9eac0
        groupPtr = (int *)(this + 0x480); // start of group array (5 entries, each 0xC bytes)
        int groupCount = 5;
        do {
            itemIndex = 0;
            if (groupPtr[1] != 0) { // group->count
                currentItemPtr = (int *)(*groupPtr + 4); // point to the first item in the group's item array (struct size 0xC)
                do {
                    // Check if the object at this item is of type "Sen0" (hash 0x53656e30)
                    if (*(int *)(*currentItemPtr + 0x28) == 0x53656e30) {
                        if ((int)itemIndex >= 0 && *(int *)(groupPtr[-4] + itemIndex * 4) != 0) {
                            // Call utility to clear the reference
                            int handle = findHashId(0x53656e30); // FUN_00c9cd50
                            sendClearMessage(*(int *)(this + 0x580), handle, 0, localBuffer); // FUN_00c9cbe0
                            localBuffer[0] = 0;
                            releaseId(0, localBuffer); // FUN_00c9cd40
                        }
                        break;
                    }
                    itemIndex++;
                    currentItemPtr += 3; // advance to next item (each item is 3 ints = 12 bytes)
                } while (itemIndex < (uint)groupPtr[1]); // count
            }
            groupPtr += 0xc; // next group (12 bytes apart)
            groupCount--;
        } while (groupCount != 0);
        endLock(); // FUN_00c9eae0
    }
    return;
}