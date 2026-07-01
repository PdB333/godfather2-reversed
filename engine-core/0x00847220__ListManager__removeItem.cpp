// FUNC_NAME: ListManager::removeItem

void __thiscall ListManager::removeItem(int param_1, int param_2)
{
    uint i;
    uint idx;
    int *entryPtr;
    int node;
    int savedNext;
    
    // Determine node pointer: either null or param_2 + 0x48 (offset where node struct is embedded)
    if (param_2 == 0) {
        node = 0;
    } else {
        node = param_2 + 0x48;
    }
    // Save the next pointer from node+4 and then set it to point to the local variable (temporary head)
    savedNext = 0;
    if (node != 0) {
        savedNext = *(int *)(node + 4);      // +0x04 = next pointer in node
        *(int **)(node + 4) = &node;         // overwrite with stack address, marking removal
    }
    // Search in a dynamic array at this+0x10c (pointer to entries) with count at this+0x110
    i = 0;
    idx = 0xffffffff;
    if (*(uint *)(param_1 + 0x110) != 0) {  // count
        entryPtr = *(int **)(param_1 + 0x10c); // base of array (each entry is 8 bytes: first = pointer, second = ?)
        do {
            idx = i;
            if (*entryPtr == node) break;   // first element of entry is the node pointer
            i++;
            entryPtr = entryPtr + 2;        // advance by 2 ints (8 bytes)
            idx = 0xffffffff;
        } while (i < *(uint *)(param_1 + 0x110));
    }
    // Destroy the node (likely operator delete)
    if (node != 0) {
        FUN_004daf90(&node);                // presumed to free node pointer
    }
    // If node not found in the index array, repeat removal with an additional step
    if ((int)idx < 0) {
        // Recompute node (identical to above)
        if (param_2 == 0) {
            node = 0;
        } else {
            node = param_2 + 0x48;
        }
        savedNext = 0;
        if (node != 0) {
            savedNext = *(int *)(node + 4);
            *(int **)(node + 4) = &node;
        }
        // Additional removal from a secondary list
        FUN_004b10d0(&node);
        if (node != 0) {
            FUN_004daf90(&node);
        }
    }
    return;
}