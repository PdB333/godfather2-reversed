// FUNC_NAME: SimManager::tickUpdateLists
void SimManager::tickUpdateLists() {
    // Process three update lists: active (offset 0x78), pending (offset 0x75), deferred (offset 0x73)
    // Each list node is an UpdateNode: {Object* pObject, int unknown, UpdateNode* pNext}

    // List 1: +0x1E0 (0x78 * 4)
    int* pCurrent = *(int**)((char*)this + 0x1E0);
    this->vtable = &PTR_LAB_00e42e68; // Set vtable (class marker)
    while (pCurrent != nullptr) {
        int* pNode = (int*)*(int*)((char*)this + 0x1E0); // Node pointer
        *(int*)((char*)this + 0x1E0) = pNode[2]; // Advance to next node (offset 8)
        Object* pObject = (Object*)*pNode; // Object pointer at node offset 0
        // Call update method at vtable+0x20
        (*(void(__thiscall**)(Object*))(*(int*)pObject + 0x20))(pObject);

        // Static initialization guard for global state
        if ((g_GlobalFlags & 1) == 0) {
            g_GlobalFlags |= 1;
            initGlobalState(); // FUN_0064f120
            atexit(cleanupGlobalState);
        }

        // Decrement reference count on object
        int* pObjectVtable = (int*)*pObject;
        if (pObjectVtable != nullptr) {
            int* refCount = pObjectVtable + 2; // +0x8
            *refCount = *refCount - 1;
            if (*refCount == 0) {
                // Call destructor at vtable+0x8
                (*(void(__thiscall**)(Object*))(*(int*)pObject + 8))(pObject);
            }
        }

        // Return node to free list
        g_iNodeCount--;
        *pNode = (int)g_pNodeFreeList;
        g_pNodeFreeList = pNode;

        pCurrent = *(int**)((char*)this + 0x1E0);
    }

    // List 2: +0x1D4 (0x75 * 4) - identical processing
    pCurrent = *(int**)((char*)this + 0x1D4);
    while (pCurrent != nullptr) {
        int* pNode = (int*)*(int*)((char*)this + 0x1D4);
        *(int*)((char*)this + 0x1D4) = pNode[2];
        Object* pObject = (Object*)*pNode;
        (*(void(__thiscall**)(Object*))(*(int*)pObject + 0x20))(pObject);

        if ((g_GlobalFlags & 1) == 0) {
            g_GlobalFlags |= 1;
            initGlobalState();
            atexit(cleanupGlobalState);
        }

        int* pObjectVtable = (int*)*pObject;
        if (pObjectVtable != nullptr) {
            int* refCount = pObjectVtable + 2;
            *refCount = *refCount - 1;
            if (*refCount == 0) {
                (*(void(__thiscall**)(Object*))(*(int*)pObject + 8))(pObject);
            }
        }

        g_iNodeCount--;
        *pNode = (int)g_pNodeFreeList;
        g_pNodeFreeList = pNode;

        pCurrent = *(int**)((char*)this + 0x1D4);
    }

    // List 3: +0x1CC (0x73 * 4) - identical processing
    pCurrent = *(int**)((char*)this + 0x1CC);
    while (pCurrent != nullptr) {
        int* pNode = (int*)*(int*)((char*)this + 0x1CC);
        *(int*)((char*)this + 0x1CC) = pNode[2];
        Object* pObject = (Object*)*pNode;
        (*(void(__thiscall**)(Object*))(*(int*)pObject + 0x20))(pObject);

        if ((g_GlobalFlags & 1) == 0) {
            g_GlobalFlags |= 1;
            initGlobalState();
            atexit(cleanupGlobalState);
        }

        int* pObjectVtable = (int*)*pObject;
        if (pObjectVtable != nullptr) {
            int* refCount = pObjectVtable + 2;
            *refCount = *refCount - 1;
            if (*refCount == 0) {
                (*(void(__thiscall**)(Object*))(*(int*)pObject + 8))(pObject);
            }
        }

        g_iNodeCount--;
        *pNode = (int)g_pNodeFreeList;
        g_pNodeFreeList = pNode;

        pCurrent = *(int**)((char*)this + 0x1CC);
    }

    // Finalize update phase
    finalizeUpdate(); // FUN_00652ea0
}