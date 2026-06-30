// FUNC_NAME: SimManager::removeEntity
void __thiscall SimManager::removeEntity(int thisPtr, int entityNode) {
    // Reset a pointer at offset 0x88 in this object (likely a head or tail of a list)
    *reinterpret_cast<int*>(thisPtr + 0x88) = DAT_01205228;

    // entityNode is a pointer to some entity; its sub-structure at offset 0x48 is a list node
    int* listNode;
    if (entityNode == 0) {
        listNode = 0;
    } else {
        listNode = reinterpret_cast<int*>(entityNode + 0x48);
    }

    // If the list node exists, perform linked list removal (node->next is at +4)
    if (listNode != 0) {
        int oldNext = listNode[1];               // node->next
        *reinterpret_cast<int**>(listNode + 1) = &listNode; // extremely suspect: setting node->next to address of local pointer
        // This likely is a decompiler artifact; real code probably does something like:
        // *prevPtr = node->next; (but prevPtr is not visible here)
    }

    // Call cleanup function on another member (at offset 0x6c, possibly a resource list)
    int someList = *reinterpret_cast<int*>(thisPtr + 0x6c);
    FUN_00408a00(&someList, 0);   // likely destructor or finalizer

    // Free the list node if it existed
    if (listNode != 0) {
        FUN_004daf90(&listNode);  // takes address of pointer, probably operator delete
    }
    return;
}