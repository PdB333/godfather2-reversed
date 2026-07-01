// FUNC_NAME: EntityManager::initializePlayerEntry

void __thiscall EntityManager::initializePlayerEntry(int thisManager, int playerIndex)
{
    char cVar1;
    char *pcVar2;
    code *pFuncInitializer;
    undefined2 *pStringPtr;
    undefined4 *pVoidPtr;
    undefined4 localStack;
    code *pLocalFunc;
    undefined2 *pLocalString;
    code *pLocalCleanup;
    char playerName [64];
    char modelPrefix [256];
    undefined4 entityHandle;                          // +0x2098 in manager?
    undefined1 entityInitData [1024];                 // passed to engine init
    undefined1 physicsData [1104];                    // passed to physics init
    undefined1 modelData [1024];                      // model/rendering data

    // If index is -1, clear everything and set state to 2
    if (playerIndex == -1) {
        clearPlayerState();                            // FUN_008f3ea0
        setPlayerActiveFlag(2);                        // FUN_008f2cf0(2)
        return;
    }

    // Access the player entry structure at offset 0x38 + index * 0x558
    getPlayerEntry(thisManager + 0x38 + playerIndex * 0x558);  // FUN_008f3190

    clearPlayerState();                                // FUN_008f3ea0
    beginProfileInitialization(entityHandle);          // FUN_008f2000(local_c68)
    setDefaultEntityValues(entityInitData);            // FUN_00accd60(local_c50)
    setupRenderCamera();                               // FUN_008f39f0

    // Set spawn position type 6 using position components from manager offsets
    setSpawnPosition(6, *(undefined4 *)(thisManager + 0x30), *(undefined4 *)(thisManager + 0x34));  // FUN_008f1e20

    // Calculate length of playerName string
    pcVar2 = playerName;
    do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    FUN_004dba80(playerName, (int)pcVar2 - (int)(playerName + 1));  // likely stringLength or strcpy

    // Allocate memory of size 0x80 for entity ID data
    allocateMemory(0x80, 0);                            // FUN_004dc090

    // Use global function pointer (or null) for engine init
    pFuncInitializer = pLocalFunc;
    if (pLocalFunc == (code *)0x0) {
        pFuncInitializer = (code *)&DAT_00e2df14;       // global default function pointer
    }
    initializeEntityEngine(pFuncInitializer, &DAT_00d5d584, &DAT_00d5d584, &DAT_00d5d584);  // FUN_00accc90

    // Calculate length of modelPrefix
    pcVar2 = modelPrefix;
    do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    FUN_004dba80(modelPrefix, (int)pcVar2 - (int)(modelPrefix + 1));  // length

    // Use global string pointer (or null) for model binding
    pStringPtr = pLocalString;
    if (pLocalString == (undefined2 *)0x0) {
        pStringPtr = (undefined2 *)&DAT_00e2df14;
    }
    bindModelToEntity(pStringPtr, modelData, thisManager + 0x20a0, thisManager + 0x20a8);  // FUN_00acd1f0

    // Cleanup temporary string if it was allocated
    if (pLocalString != (undefined2 *)0x0) {
        (*pLocalCleanup)(pLocalString);                 // FUN_00acd1f0 cleanup (pLocalCleanup used)
    }

    releaseString(modelPrefix);                         // FUN_008f1f90

    // Call virtual function: vtable at +0x2098, method at index 0x2c (44)
    pVoidPtr = &localStack;
    localStack = 0;
    (**(code **)(**(int **)(thisManager + 0x2098) + 0x2c))(physicsData, 0);  // physics init with 0 flag

    // Release initializer function pointer if it was set
    if (pVoidPtr != (undefined4 *)0x0) {
        (*pLocalFunc)(pVoidPtr);                        // cleanup through function pointer
    }

    finishEntityInitialization();                       // FUN_008f2020
    return;
}