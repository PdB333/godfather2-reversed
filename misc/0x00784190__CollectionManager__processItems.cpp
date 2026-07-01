// FUNC_NAME: CollectionManager::processItems
// Address: 0x00784190
// Role: Processes a collection of items. Two paths based on bit1 of flags at +0x74:
//   - If bit1 clear: manipulates a singly-linked list using the node at +0x40 and calls a callback at +0x1c
//   - If bit1 set: iterates an array at +0x64 (count at +0x68), adjusts pointers by -0x48, and calls FUN_00784020 on each.

void CollectionManager::processItems() {
    // Offset +0x74: flags (bit1 = 0x02)
    uint flags = *(uint *)(this + 0x74);
    if ((flags >> 1 & 1) == 0) {
        // Fast path: linked list mode
        int *currentNode = *(int **)(this + 0x40); // +0x40: pointer to current linked list node
        
        // Stack structure (probably a temporary scoped object)
        undefined4 temp1;
        undefined ***temp2;
        undefined1 temp3;
        undefined **temp4;
        int temp5;            // local_20
        int savedNext;        // local_1c
        undefined4 temp6;     // local_18
        undefined8 temp7;     // local_14
        undefined4 temp8;     // local_c
        undefined1 temp9;     // local_8
        undefined4 temp10;    // local_4
        
        // Initialize stack variables
        temp8 = 0;
        temp7 = 0;
        temp4 = &PTR_FUN_00d5dbbc; // global function pointer table
        savedNext = 0;
        temp6 = 0;
        temp9 = 0;
        temp10 = DAT_01205228;      // global constant
        temp5 = -0x3e7f38d7;        // negative constant (likely sentinel)
        
        if (currentNode != 0 && currentNode != (int *)0x48 && currentNode != 0) {
            // Check for valid node (0x48 might be a marker)
            temp6 = *(undefined4 *)(currentNode + 1); // offset 4: next pointer
            *(int **)(currentNode + 1) = &savedNext;   // link node to stack variable
            savedNext = (int)currentNode;              // make stack variable point to current node
        }
        
        int *globalPtr = (int *)FUN_00471610(); // likely global singleton
        temp9 = 1;
        temp7 = *(undefined8 *)(globalPtr + 0x30);
        temp8 = *(undefined4 *)(globalPtr + 0x38);
        temp2 = &temp4;
        temp1 = DAT_0112ad8c;                      // global constant
        temp3 = 0;
        FUN_00408a00(&temp1, 0);                   // construct a temporary object on stack
        
        // Call the callback stored at +0x1c
        (*(void (*)(int))(**(int **)(this + 0x1c)))(1);
        
        if (temp5 != 0) {
            FUN_004daf90(&temp5);                  // destructor for temporary object
            return;
        }
    } else {
        // Slow path: array iteration mode
        uint count = *(uint *)(this + 0x68);       // +0x68: number of items
        uint idx = 0;
        if (count != 0) {
            do {
                // Array at +0x64, each element is 8 bytes (pointer + maybe ID)
                int *arrayBase = *(int **)(this + 100); // offset 0x64
                int *itemPtr = (int *)*(arrayBase + idx * 2); // read pointer (first 4 bytes of element)
                if (itemPtr != 0) {
                    int *adjustedPtr = (int *)((char *)itemPtr - 0x48); // header offset by 0x48
                    if (adjustedPtr != 0) {
                        FUN_00784020(adjustedPtr, 1);
                    }
                }
                idx++;
            } while (idx < count);
        }
    }
    return;
}