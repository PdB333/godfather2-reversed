// FUNC_NAME: EARSObject::releaseNode
void __fastcall EARSObject::releaseNode(EARSObject* this) {
    int nodeId = *(int*)((uint8_t*)this + 0x14); // +0x14: node index/identifier
    // Set vtable to base class (likely a shared pool handler)
    *(void**)this = (void*)&PTR_FUN_00e37ae0;

    if (nodeId != 0) {
        // Global pool manager at DAT_012068e8, +0x14 points to free list head pointer
        int** freeListHeadPtr = (int**)((uint8_t*)DAT_012068e8 + 0x14);
        int* freeListHead = *freeListHeadPtr;

        // Push this node's id onto the free list
        *freeListHeadPtr = (int*)((uint8_t*)freeListHead + 4);
        *(int*)*((int**)((uint8_t*)DAT_012068e8 + 0x14)) = nodeId;
        *freeListHeadPtr = (int*)((uint8_t*)*freeListHeadPtr + 4);

        // Clear local node id
        *(int*)((uint8_t*)this + 0x14) = 0;
    }

    // Release an owned resource (e.g., allocated memory)
    int* ownedPtr = *(int**)((uint8_t*)this + 0x1C); // +0x1C: pointer to another allocation
    if (ownedPtr != 0) {
        FUN_009c8f10(ownedPtr); // Memory::deallocate
    }

    // Final vtable assignment (likely restores original vtable or points to a sentinel)
    *(void**)this = (void*)&PTR_LAB_00e37304;
}