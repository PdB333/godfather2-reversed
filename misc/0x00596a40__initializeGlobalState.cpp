//FUNC_NAME: initializeGlobalState
void initializeGlobalState(int gameManager)
{
    int iVar1;
    int *puVar2;

    g_gameManager = gameManager;

    // Release existing subsystems if they exist (vtable+4 likely destructor)
    if (*(int **)(gameManager + 4) != (int *)0x0) {
        (**(code **)(**(int **)(gameManager + 4) + 4))(0x20, 0x20, 0x40);
    }
    if (*(int **)(g_gameManager + 8) != (int *)0x0) {
        (**(code **)(**(int **)(g_gameManager + 8) + 4))();
    }
    if (*(int **)(g_gameManager + 0xc) != (int *)0x0) {
        (**(code **)(**(int **)(g_gameManager + 0xc) + 4))();
    }
    if (*(int **)(g_gameManager + 0x10) != (int *)0x0) {
        (**(code **)(**(int **)(g_gameManager + 0x10) + 4))();
    }

    // Clear a 256-element array (likely event flags or input states)
    puVar2 = &g_clearArray;
    for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
    }

    g_globalFlag = 0;

    // Initialize 64 slots (each 0x74 bytes) with subsystem pointers from gameManager
    puVar2 = &g_slotArray;
    do {
        initializeSlot();  // Per-slot initialization (likely constructor)
        puVar2[-1] = *(int *)(gameManager + 4);   // +0x4: subsystem1
        *puVar2 = *(int *)(gameManager + 0x10);   // +0x10: subsystem4
        puVar2[1] = *(int *)(gameManager + 0xc);  // +0xc: subsystem3
        puVar2[2] = *(int *)(gameManager + 8);    // +0x8: subsystem2
        puVar2 = puVar2 + 0x74;                   // Advance to next slot (0x74 bytes each)
    } while ((int)puVar2 < 0x119c890);            // End of slot array
}