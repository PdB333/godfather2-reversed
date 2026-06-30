// FUNC_NAME: ObjectManager::validateObject
undefined4 __thiscall ObjectManager::validateObject(int pManager, int pEntry) {
    char cFlag;
    uint index;
    undefined4 result;
    uint i;
    int* pArrayIter;
    int tempNode[2]; // temporary linked-list node (data, next)
    int savedNext;   // copy of pEntry->next before modification

    i = 0;
    tempNode[0] = pEntry;
    tempNode[1] = 0; // next = null
    savedNext = 0;
    if (pEntry != 0) {
        savedNext = *(int *)(pEntry + 4); // save original pEntry+4
        *(int **)(pEntry + 4) = &tempNode; // link pEntry to stack node
    }

    index = 0xFFFFFFFF; // not found
    if (*(uint *)(pManager + 0xC) != 0) {
        pArrayIter = *(int **)(pManager + 8); // pointer to array of 2-int entries
        do {
            index = i;
            if (*pArrayIter == pEntry) break; // found matching pointer
            i = i + 1;
            pArrayIter = pArrayIter + 2; // advance to next entry (size 8)
            index = 0xFFFFFFFF;
        } while (i < *(uint *)(pManager + 0xC));
    }

    if (pEntry != 0) {
        FUN_004daf90(&tempNode); // restore or clean up the temporary link
    }

    // If entry not in manager's array and either flags bit 1 is set or subobject at +0x44 is active
    if ((index == 0xFFFFFFFF) &&
        ((*(uint *)(pManager + 0x8C) >> 1 & 1) != 0 ||
         (cFlag = FUN_00718d40(pEntry + 0x44), cFlag != '\0'))) {
        result = FUN_0074dc40(pEntry + 0x44);
        return result;
    }
    return 1;
}