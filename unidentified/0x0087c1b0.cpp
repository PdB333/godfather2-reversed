// FUN_0087c1b0: SimObject::registerInstance
void __thiscall SimObject::registerInstance(int this) {
    int iNode;
    int oldPrevNext;
    
    // If the global head is a valid node (not null, not sentinel 0x48),
    // update its vtable pointer at offset 0x110 to a secondary vtable.
    if ((g_pInstanceListHead != 0) && (g_pInstanceListHead != 0x48)) {
        *(int *)(g_pInstanceListHead + 0x110) = (int)&LAB_00877130; // secondary vtable
    }
    
    // The embedded list node starts at offset 0x48 in the object.
    if (this == 0) {
        iNode = 0;
    } else {
        iNode = this + 0x48;
    }
    
    // If the node is not already the head, remove the old head and insert this node as the new head.
    if (g_pInstanceListHead != iNode) {
        if (g_pInstanceListHead != 0) {
            listRemoveHead(&g_pInstanceListHead); // FUN_004daf90: removes current head from intrusive list
        }
        g_pInstanceListHead = iNode;
        if (iNode != 0) {
            // Save the old "prev_next" pointer (address of the pointer that points to this node)
            oldPrevNext = *(int *)(iNode + 4);
            // Set this node's prev_next to point to the global head pointer,
            // enabling O(1) removal via *prev_next = next.
            *(int **)(iNode + 4) = &g_pInstanceListHead;
        }
    }
    
    // Set the primary vtable pointer at offset 0x158.
    *(int *)(this + 0x158) = (int)&LAB_008770b0; // primary vtable
    
    // Debug logging: if a global flag is set, log an error code 2.
    if (someDebugCheck() != 0) { // FUN_005466a0
        debugLog(2); // FUN_009f3cc0
    }
}