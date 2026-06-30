// FUN_004977b0: ListManager::traverseNodes
void __thiscall ListManager::traverseNodes(void) {
    int* pHead;       // local_4
    int* pCurrent;    // iVar1

    // Check if the object pointed to by the first member of 'this' is null
    if (*(int**)this == 0) {
        pHead = 0;
        pCurrent = 0;
    }
    else {
        // Read head pointer from offset 0x30 of the object pointed to by 'this'
        // *this + 0x30 is a pointer to a pointer; dereference twice to get head
        pHead = *(int**)(*(int*)this + 0x30);
        pCurrent = pHead;
    }

    // Traverse linked list (each node has a 'next' pointer at offset 0x30)
    while (pCurrent != 0) {
        // Process the current node; may modify pHead (passed by address)
        FUN_00498740(&pHead, pCurrent);

        // Copy 16 bytes from current node to new head (offsets +8 and +0x10)
        *(int64_t*)(pHead + 2) = *(int64_t*)(pCurrent + 2);   // +8
        *(int64_t*)(pHead + 4) = *(int64_t*)(pCurrent + 4);   // +0x10

        // Move to next node (offset 0x30 holds pointer to next node)
        // Note: Original decompile shows double dereference; likely a Ghidra casting artifact.
        pCurrent = *(int**)(pCurrent + 0x30);
    }
}