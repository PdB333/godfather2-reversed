// FUNC_NAME: SimManager::processUpdateLists

// Function at 0x0064e060: Main update loop for SimManager, processes three priority lists of active objects.
// Each list node has a vtable pointer, reference count at +8, and next pointer at +8 (offset 8 from start of node).
// Virtual function at vtable+0x20 (index 8) is the update/tick method.
// Virtual function at vtable+0x8 (index 2) is the destructor (called when ref count reaches 0).
// Global state: g_objectCount (int at 0x1223cb0), g_freeListHead (int* at 0x1223cb8), g_initFlag (int at 0x1223cbc bit 0).
// One-time initialization via FUN_0064f120() and registration of cleanup via atexit.

extern int g_objectCount;          // _DAT_01223cb0
extern int* g_freeListHead;        // DAT_01223cb8
extern int g_initFlag;             // _DAT_01223cbc

void __thiscall SimManager::processUpdateLists()
{
    int* listHead;
    int* currentNode;
    int* vtablePtr;
    int* refCountPtr;
    int* nextNode;

    // Process list at offset 0x78 (highest priority)
    listHead = *(int**)(this + 0x78);
    *this = &PTR_LAB_00e42e68;  // vtable setup (likely class vtable)
    while (listHead != 0) {
        currentNode = (int*)listHead;
        listHead = (int*)currentNode[2];  // next pointer at +8
        // Call virtual update function (index 8)
        (**(code**)(*(int*)*currentNode + 0x20))();
        // One-time initialization guard
        if ((g_initFlag & 1) == 0) {
            g_initFlag |= 1;
            FUN_0064f120();  // Initialize global resources
            atexit(&cleanupRoutine);  // LAB_00d513f0
        }
        // Decrement reference count
        vtablePtr = (int*)*currentNode;
        if (vtablePtr != 0) {
            refCountPtr = vtablePtr + 2;  // ref count at +8
            *refCountPtr = *refCountPtr - 1;
            if (*refCountPtr == 0) {
                // Call virtual destructor (index 2)
                (**(code**)(*vtablePtr + 8))();
            }
        }
        g_objectCount--;
        *currentNode = (int)g_freeListHead;
        g_freeListHead = currentNode;
        listHead = *(int**)(this + 0x78);  // re-read head in case list changed? Actually original uses unaff_ESI[0x78] again.
    }

    // Process list at offset 0x75 (medium priority) - same logic
    listHead = *(int**)(this + 0x75);
    while (listHead != 0) {
        currentNode = (int*)listHead;
        listHead = (int*)currentNode[2];
        (**(code**)(*(int*)*currentNode + 0x20))();
        if ((g_initFlag & 1) == 0) {
            g_initFlag |= 1;
            FUN_0064f120();
            atexit(&cleanupRoutine);
        }
        vtablePtr = (int*)*currentNode;
        if (vtablePtr != 0) {
            refCountPtr = vtablePtr + 2;
            *refCountPtr = *refCountPtr - 1;
            if (*refCountPtr == 0) {
                (**(code**)(*vtablePtr + 8))();
            }
        }
        g_objectCount--;
        *currentNode = (int)g_freeListHead;
        g_freeListHead = currentNode;
        listHead = *(int**)(this + 0x75);
    }

    // Process list at offset 0x73 (lowest priority) - same logic
    listHead = *(int**)(this + 0x73);
    while (listHead != 0) {
        currentNode = (int*)listHead;
        listHead = (int*)currentNode[2];
        (**(code**)(*(int*)*currentNode + 0x20))();
        if ((g_initFlag & 1) == 0) {
            g_initFlag |= 1;
            FUN_0064f120();
            atexit(&cleanupRoutine);
        }
        vtablePtr = (int*)*currentNode;
        if (vtablePtr != 0) {
            refCountPtr = vtablePtr + 2;
            *refCountPtr = *refCountPtr - 1;
            if (*refCountPtr == 0) {
                (**(code**)(*vtablePtr + 8))();
            }
        }
        g_objectCount--;
        *currentNode = (int)g_freeListHead;
        g_freeListHead = currentNode;
        listHead = *(int**)(this + 0x73);
    }

    // Final processing step
    FUN_00652ea0();  // Likely deferred work / sync
    return;
}