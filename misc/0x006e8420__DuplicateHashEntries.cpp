// FUNC_NAME: DuplicateHashEntries
int* __fastcall DuplicateHashEntries(void* instance) {
    uint key;
    int* globalState; // +0x0 = mode? +0x8 = count
    uint* hashNode;   // 20-byte node for first hash table (DAT_0112a99c)
    int* nodeList;    // pointer to first hash table bucket array
    uint* freeNode;   // for second hash table (DAT_0112a9a0)
    uint* secondNode; // 140-byte? structure with vtable at offset 0
    uint* bucketEntry;
    uint hashIndex;
    uint* dataArray;  // source array from FUN_004213e0
    uint localData[4]; // 16-byte data for second hash

    // Get source data pointer and key
    dataArray = (uint*)FUN_004213e0(&key, instance);
    key = *dataArray; // first uint is the key

    globalState = (int*)FUN_0049c9c0(); // global state structure
    if (*globalState == 2) { // if mode == 2 (maybe initializing)
        hashNode = (uint*)(globalState + 3); // pointer to start of bucket array? Actually +12 bytes from base
        for (int count = globalState[2]; count != 0; count--) {
            hashNode[4] = key; // store key in node field at +16
            if (hashNode[3] != 0) { // hashNode[3] is the hash value
                // Look up in first hash table (DAT_0112a99c)
                uint* bucketBase = *(uint**)(*DAT_0112a99c + (hashNode[3] % (uint)DAT_0112a99c[1]) * 4);
                while (bucketBase != nullptr && *bucketBase != hashNode[3]) {
                    bucketBase = (uint*)bucketBase[4]; // next bucket
                }
                if (bucketBase == nullptr) {
                    // Allocate new node (20 bytes)
                    freeNode = (uint*)FUN_009c8e50(0x14); // alloc 20 bytes
                    if (freeNode == nullptr) {
                        freeNode = nullptr;
                    } else {
                        *freeNode = 0;
                        *(uint16*)(freeNode + 1) = 0;
                        *(uint16*)((int)freeNode + 6) = 0;
                        freeNode[2] = 0;
                        freeNode[3] = 0;
                        freeNode[4] = 0;
                    }
                    FUN_00408260(freeNode, hashNode[3]); // initialize node with hash value
                    if (*freeNode != 0) {
                        FUN_00408900(instance + -0xc, freeNode, 0x8000); // process node with instance (offset -12)
                    }
                    // Insert into hash table
                    int* hashTable = DAT_0112a99c;
                    uint* bucketCount = (uint*)(DAT_0112a99c + 1); // address of bucket count
                    hashIndex = *freeNode % (uint)DAT_0112a99c[1];
                    // Rehash if load factor exceeds threshold
                    if (((char)DAT_0112a99c[3] != '\0') && ((uint)(DAT_0112a99c[1] * 2) <= (uint)DAT_0112a99c[2])) {
                        FUN_006e60e0(); // rehash
                        hashIndex = *freeNode % *bucketCount;
                    }
                    freeNode[4] = *(uint*)(*hashTable + hashIndex * 4); // next = head
                    *(uint**)(*hashTable + hashIndex * 4) = freeNode; // head = freeNode
                    hashTable[2] = hashTable[2] + 1; // increment count
                }
                // Update linked list in source data
                *hashNode = freeNode[2]; // copy next pointer
                hashNode[1] = 0; // prev = null
                if (freeNode[2] == 0) {
                    freeNode[3] = (uint)hashNode; // if no next, set prev to current node
                } else {
                    *(uint**)(freeNode[2] + 4) = hashNode; // set next's prev
                }
                freeNode[2] = (uint)hashNode; // set next to current node
            }
            // Process second hash table (DAT_0112a9a0)
            uint* srcEntry = hashNode + 7; // +28 bytes from hashNode
            uint index = 0;
            if (hashNode[2] != 0) { // if count != 0
                uint* srcIter = hashNode + 12; // +48 bytes
                do {
                    if (srcEntry != nullptr) {
                        // Initialize second node structure
                        srcIter[-4] = 0;
                        srcIter[-3] = 0;
                        srcIter[-2] = 0;
                        *srcEntry = (uint)&PTR_FUN_00d5faf8; // set vtable
                        srcIter[0x13] = 0;
                        srcIter[0x14] = 0;
                        *(uint8*)(srcIter + 0x77) = 0;
                    }
                    // Compute hash of 16-byte data from srcIter
                    int* secondTable = DAT_0112a9a0;
                    localData[0] = srcIter[-1];
                    localData[1] = *srcIter;
                    localData[2] = srcIter[1];
                    localData[3] = srcIter[2];
                    FUN_004d9af0(); // likely finalize hash
                    uint hashVal = FUN_004db320(&localData, 16); // compute hash of 16 bytes
                    hashVal = hashVal % (uint)secondTable[1];
                    // Rehash if needed
                    if (((char)secondTable[5] != '\0') && ((uint)(secondTable[1] * 2) <= (uint)secondTable[3])) {
                        FUN_006e6f20(); // rehash second table
                        uint rehashData[4] = { srcIter[-1], *srcIter, srcIter[1], srcIter[2] };
                        FUN_004d9af0();
                        hashVal = FUN_004db320(&rehashData, 16) % (uint)secondTable[1];
                    }
                    // Get a free node from pool
                    undefined4* secondNode = (undefined4*)secondTable[2]; // free list head
                    if (secondNode == nullptr) {
                        FUN_006e73f0(); // allocate more free nodes
                        secondNode = (undefined4*)secondTable[2];
                    }
                    secondTable[2] = (int)secondNode[1]; // remove from free list
                    secondNode[1] = 0;
                    secondTable[3] = secondTable[3] + 1; // increment used count
                    *secondNode = srcEntry;               // point to data
                    secondNode[1] = *(undefined4*)(*secondTable + hashVal * 4); // link to bucket head
                    *(undefined4**)(*secondTable + hashVal * 4) = secondNode;
                    FUN_006e7260(srcEntry); // initialize the data structure
                    index++;
                    srcEntry += 0x23; // advance by 35 uints (140 bytes)
                    srcIter += 0x23;
                } while (index < hashNode[2]);
            }
            hashNode = srcEntry; // advance to next entry
        }
    }
    return globalState;
}