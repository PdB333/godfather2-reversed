// FUNC_NAME: EntityManager::processCommandList
// Address: 0x00849b10
// Role: Processes a command list containing pairs of (objectID, value) and performs an action (cmd == 1) on matching objects.

int __thiscall EntityManager::processCommandList(void* param_2, int* pMsg) {
    int cmd = *pMsg;                         // First int: command opcode
    int itemCount = pMsg[1];                 // Second int: number of ID/value pairs
    int* pData = pMsg + 2;                   // Pointer to start of pairs

    if (itemCount != 0) {
        do {
            itemCount--;                     // Decrement remaining count
            int* pCurrentPair = pData + 1;   // Points to the value part of the pair (pData[0]=ID, pData[1]=value)
            uint idx = 0;

            // Search the object array (this+0x0c holds pointer array, this+0x10 is count)
            if (*(uint*)(this + 0x10) != 0) {
                int** arr = *(int***)(this + 0x0c);
                do {
                    // Check if object's ID (offset +0x50) matches the current pair ID
                    if ((*arr)[0x50/4] == *pData) {
                        // Check if the pointer at this index is non-null (always true for valid indices)
                        if ((-1 < (int)idx) && (*(int*)(*(int*)(this + 0x0c) + idx * 4) != 0)) {
                            if (cmd == 1) {
                                int value = *pCurrentPair;          // The value from the pair
                                pCurrentPair = pData + 2;           // Advance to next pair (but pCurrentPair will be overwritten)
                                FUN_008490e0(value);                 // Perform action with the value
                            }
                            goto advance;                           // Skip to next iteration
                        }
                        break;                                      // If pointer is null, stop searching for this ID
                    }
                    idx++;
                    arr++;
                } while (idx < *(uint*)(this + 0x10));
            }

            // If no match found or pointer was null, still need to advance
            if (cmd == 1) {
                pCurrentPair = pData + 2;   // Skip the current pair
            }

advance:
            pData = pCurrentPair;           // Move to next pair
        } while (itemCount != 0);
        itemCount = 0;                      // Redundant but present in original
    }

    // Always returns 1 (success)
    return CONCAT31((int3)((uint)itemCount >> 8), 1);
}