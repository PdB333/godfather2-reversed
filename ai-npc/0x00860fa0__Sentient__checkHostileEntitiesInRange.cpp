// FUNC_NAME: Sentient::checkHostileEntitiesInRange
bool Sentient::checkHostileEntitiesInRange(Vector3* position) // parameter is likely a position (3 floats/int32s)
{
    int iVar1;
    int iVar2;
    int* piVar5;
    int* puVar3;
    uint uVar4;
    int iCount;
    int iTmpCounter;
    int aMatrix[6];            // local_c0
    int aMatrix2[?];           // actually 6 ints? from initialization
    int local_98;
    int aHandle[2];            // local_84
    char acStringBuffer[12];   // auStack_7c
    char acMatrixData[32];     // local_70
    int aMatrixCopy[19];       // local_50 (19 dwords)

    iVar1 = this; // this pointer from ECX (iStack_d4)

    // Get the simulation manager (singleton)
    iVar2 = getSimManager(); // FUN_005466a0
    // Get vtable for something (maybe world or spatial system)
    piVar5 = *(int**)(iVar2 + 0x10);

    // Initialize matrix to identity (or zero)
    aMatrix[0] = gZeroMatrix;  // _DAT_00d5780c
    aMatrix[1] = 0;
    aMatrix[2] = 0;
    aMatrix[3] = 0;
    aMatrix[4] = 0;
    aMatrix[5] = gZeroMatrix;  // _DAT_00d5780c
    local_98 = gZeroMatrix;    // _DAT_00d5780c
    aHandle[0] = 0;
    int local_88 = 0;
    int local_8c = 0;
    int local_90 = 0;          // will be set later

    // Get a default matrix/transform from pool
    puVar3 = getDefaultMatrix(); // FUN_00471610
    // Copy 16 dwords into local buffer (matrix?)
    for (int i = 0; i < 16; i++) {
        aMatrixCopy[i] = puVar3[i];
    }
    // Overwrite with position from parameter
    local_90 = position->x;    // *param_1
    local_8c = position->y;    // param_1[1]
    local_88 = position->z;    // param_1[2]
    aHandle[0] = gZeroMatrix;  // _DAT_00d5780c

    // Compute final transformation
    multiplyMatrix(aMatrixCopy, aMatrix); // FUN_004b59d0

    // Call a virtual method on the world/system (offset 0x1c) to set transform?
    (**(code**)(*piVar5 + 0x1c))(aMatrix, 0, acMatrixData);

    // Check if the list of cached entities is allocated
    if (*(int*)(this + 0xf94) == 0) {
        // TLS: get thread-local value for allocation
        TlsGetValue(gTlsIndex); // DAT_01139810
        // Allocate memory for list (size 0xd0, flags 0x31)
        iVar2 = allocateMemory(0xd0, 0x31); // FUN_00aa2680
        *(short*)(iVar2 + 4) = 0xd0;
        uVar4 = createString(0xb, 0x1f, 0); // FUN_00540c60 - maybe a string table entry
        // Build the list object from string
        iVar2 = constructListObject(acStringBuffer, uVar4); // FUN_009f59e0
        *(int*)(this + 0xf94) = iVar2;
        if ((iVar2 != 0) && (*(int*)(iVar2 + 8) == 0)) {
            initializeListObject(iVar2); // FUN_009e7450
        }
    } else {
        // Update the list object string
        updateListString(acStringBuffer); // FUN_009f5240
    }

    // Get count of entities in the list (offset 0xc4)
    iCount = *(int*)(*(int*)(this + 0xf94) + 0xc4);
    if (0 < iCount) {
        int* pEntityArray = *(int**)(*(int*)(this + 0xf94) + 0xc0);
        int iTmp = iCount;
        do {
            iVar2 = *pEntityArray;
            if ((iVar2 != 0) && (*(char*)(iVar2 + 0x10) + iVar2 != 0)) {
                // Resolve entity from handle? (0x2001 = type tag)
                queryEntity(aHandle, 0x2001); // FUN_004af8c0
                iVar2 = 0;
                if (aHandle[0] != 0) {
                    iVar2 = aHandle[0];
                }
                // Skip if entity is null, or if it's ourselves, or if it has negative "hostile" flag
                if ((iVar2 != 0) && ((*(char*)(iVar2 + 0x15e) < '\0' || (iVar2 == iVar1)))) {
                    iCount--;
                }
            }
            pEntityArray++;
            iTmp--;
        } while (iTmp != 0);
    }

    // Update some per-frame callback
    onFrameUpdate(); // FUN_0085f170

    return 0 < iCount; // true if any hostile entities remain
}