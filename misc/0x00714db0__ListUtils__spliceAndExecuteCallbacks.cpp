// FUNC_NAME: ListUtils::spliceAndExecuteCallbacks
void ListUtils::spliceAndExecuteCallbacks(intptr_t node1, intptr_t node2, uint32_t callbackParam)
{
    // Temporary sentinel nodes for safe list manipulation
    int sentinel1_next = 0;
    int savedPrev1 = 0;
    int sentinel2_next = 0;
    int savedPrev2 = 0;
    int unused = 0;

    // Backup and splice node1 out of its list
    if (node1 != 0 && (node1 + 0x48) != 0) {
        // node1 + 0x4c holds a pointer to the previous node's next pointer
        savedPrev1 = *(int*)(node1 + 0x4c);
        *(int**)(node1 + 0x4c) = &sentinel1_next;
        sentinel1_next = node1 + 0x48;
    }

    // Prepare node2: advance to its next node pointer (offset 0x48)
    if (node2 == 0) {
        node2 = 0;
    } else {
        node2 = node2 + 0x48;
    }

    // Backup and splice node2 out, inserting a sentinel
    if (node2 != 0) {
        savedPrev2 = 0;
        sentinel2_next = node2;
        if (node2 != 0) {
            savedPrev2 = *(int*)(node2 + 4);       // +4 from node2 = +0x4c from original node
            *(int**)(node2 + 4) = &sentinel2_next;
        }
    }

    // Build a temporary callback list structure on the stack
    void* callbackFunctionTable = PTR_FUN_00d61a80;  // global function pointer table
    uint32_t globalData = DAT_0112ac90;               // some global data
    char callbackFlag = 0;

    struct {
        uint32_t data1;           // local_30 -> globalData
        char flag;                // local_28 -> 0
        void** funcTable;         // local_2c -> &local_24
        void* funcEntry;          // local_24 -> callbackFunctionTable
    } callbackList = { globalData, callbackFlag, &callbackList.funcEntry, callbackFunctionTable };

    // Get the global manager instance and fetch callback list pointers
    int mgr = FUN_00471610();                         // e.g., MemoryManager::getInstance()
    intptr_t previousCB = *(intptr_t*)(mgr + 0x30);
    intptr_t nextCB = *(intptr_t*)(mgr + 0x38);
    // Store them in unused stack slots (not shown in decomp, but implied by local_c/local_4)
    // local_c = previousCB; local_4 = nextCB; (these are not used later)

    // Process the callback list (the temporary one) with the given parameter
    FUN_00408a00(&callbackList, 0);

    // Restore the original list links by removing the sentinel nodes
    if (sentinel2_next != 0) {
        FUN_004daf90(&sentinel2_next);
    }
    if (sentinel1_next != 0) {
        FUN_004daf90(&sentinel1_next);
    }
}