// FUNC_NAME: ControlsManager::loadRmpFile
void ControlsManager::loadRmpFile(void)
{
    undefined *pPathString;
    undefined4 pathLen;
    undefined2 **ppRmpData;
    undefined2 *pRmpData;
    undefined2 *localRmpCopy[3]; // +0x00
    code *pDestructor; // stack
    int allocResult; // local_20
    undefined4 allocParam; // local_1c
    code *pAllocDestructor; // local_14 (0x14 offset)
    int tempInt; // local_10
    undefined4 tempU4; // local_c
    code *pCleanupFunc; // pcStack_4

    // Pointer to "controls/rmp" string (from global)
    pPathString = PTR_u_controls_rmp_00e50c74;

    // Check if control system is already initialized (offset 0x2264 in global manager)
    if (*(int *)(DAT_01129828 + 0x2264) == 0) {
        // Not initialized, perform early setup
        FUN_006a0480();
        return;
    }

    // Get length of path string
    pathLen = FUN_004dbef0(pPathString);
    // Probably copy or format the path
    FUN_004dba00(pPathString, pathLen);

    // Get the actual control data pointer (offset 0x2260), default to empty placeholder
    pRmpData = *(undefined2 **)(DAT_01129828 + 0x2260);
    if (pRmpData == (undefined2 *)0x0) {
        pRmpData = &DAT_00e2df14; // empty placeholder
    }

    // Get its length and process similarly
    pathLen = FUN_004dbef0(pRmpData);
    FUN_004dba00(pRmpData, pathLen);

    // Allocate or prepare a temporary buffer (related to DAT_00e36ef4)
    FUN_004dbf70(&DAT_00e36ef4, 1, tempInt, tempU4);
    allocResult = FUN_004dbd90(0, 0, allocParam);
    if (allocResult != 0) {
        // Call destructor on allocResult? (vtable function at local_14)
        (*pAllocDestructor)(allocResult);
    }

    // localRmpCopy is a copy of the control data or a new allocation
    pRmpData = localRmpCopy[0];
    if (localRmpCopy[0] == (undefined2 *)0x0) {
        pRmpData = &DAT_00e2df14;
    }

    // Append to vector or list (function at 0x00699080)
    ppRmpData = (undefined2 **)FUN_00699080(&localRmpCopy, pRmpData, 3);
    if (localRmpCopy != ppRmpData) {
        pRmpData = *ppRmpData;
        if (pRmpData == (undefined2 *)0x0) {
            pRmpData = &DAT_00e2df14;
        }
        // Set value (index 0, data from ppRmpData[1])
        FUN_004dbb10(pRmpData, 0, ppRmpData[1]);
    }

    // Cleanup allocated temporary
    if (allocResult != 0) {
        (*pAllocDestructor)(allocResult);
    }

    pRmpData = localRmpCopy[0];
    if (localRmpCopy[0] == (undefined2 *)0x0) {
        pRmpData = &DAT_00e2df14;
    }
    // Free memory or finalize
    FUN_00497470(pRmpData);

    // Destroy local copy if it was allocated
    if (localRmpCopy[0] != (undefined2 *)0x0) {
        (*pDestructor)(localRmpCopy[0]);
    }

    // Destroy temporary buffer if allocated
    if (tempInt != 0) {
        (*pCleanupFunc)(tempInt);
    }

    return;
}