// FUNC_NAME: Apt::submitCommandAux
void Apt::submitCommandAux(uint param_2) // 0x0059ecb0
{
    int *piVar1;
    code *pcVar2;
    uint uVar3;
    uint *puVar4;
    undefined4 uVar5;
    int unaff_FS_OFFSET;
    undefined4 uVar6;
    uint *puVar7;
    undefined4 uVar8;
    undefined4 uVar9;
    char *sourceFile; // local_14 - "..\\source\\Apt\\Apt.cpp"
    char *assertionExpr; // local_10 - "bAptIsInitialized"
    undefined4 assertionLine; // local_c - 0x23b (571)
    int assertLevel; // local_8 - 2
    undefined1 *assertFlag; // local_4 - pointer to assertion flag

    // Check if Apt system is not initialized
    if (DAT_012055b0 != 0) goto skipInitializationCheck;
    sourceFile = "bAptIsInitialized";
    assertionExpr = "..\\source\\Apt\\Apt.cpp";
    assertionLine = 0x23b; // 571
    assertLevel = 2;
    assertFlag = &DAT_01128f42;
    if (DAT_01128f42 == '\0') goto skipInitializationCheck; // If assertion already failed, skip

    // Get thread-local storage for assertion handling
    piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
    uVar3 = 1;
    if (piVar1 == (int *)0x0) {
LAB_0059ed23:
        if ((uVar3 & 2) != 0) {
            *assertFlag = 0; // Clear assertion flag
        }
    }
    else {
        uVar3 = (**(code **)(*piVar1 + 8))(&sourceFile, "bAptIsInitialized"); // Call assertion handler
        if (assertFlag != (undefined1 *)0x0) goto LAB_0059ed23;
    }

    // Handle assertion failure (debug break)
    if (((piVar1 != (int *)0x0) || (assertLevel != 4)) &&
       (((uVar3 & 1) != 0 || ((assertLevel == 0 || (assertLevel == 1)))))) {
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
    }

skipInitializationCheck:
    // Allocate command object (8 bytes)
    puVar4 = (uint *)(*DAT_0119caf0)(8, 0);
    if (puVar4 == (uint *)0x0) {
        puVar4 = (uint *)0x0;
    }
    else {
        // Initialize command header
        *puVar4 = *puVar4 & 0xffff8006 | 6; // Set command type to 6
        *(undefined2 *)((int)puVar4 + 2) = 0;
        *puVar4 = *puVar4 | 0x8000; // Set high bit (command flags)
        puVar4[1] = param_2; // Store parameter
    }

    // Check if this is a new command queue
    if (puVar4 != DAT_0119cbbc) {
        uVar3 = *puVar4 & 0x7fff; // Extract command type
        // Validate command type (skip certain invalid ones)
        if ((uVar3 != 0x19) &&
           (((~(byte)(*puVar4 >> 0xf) & 1) != 0 ||
            (((uVar3 != 0xb && (uVar3 != 0x18)) && (uVar3 != 0x17)))))) {
            FUN_0059c230(puVar4); // Process/add command to queue
        }
    }

    // Submit command to the command stream
    uVar9 = 1;
    uVar8 = 1;
    uVar6 = 0;
    puVar7 = puVar4;
    uVar5 = FUN_0059e2f0(0, param_1, puVar4, 1, 1); // Enqueue command
    FUN_005ad5b0(uVar5, uVar6, param_1, puVar7, uVar8, uVar9); // Notify listeners
    (**(code **)(&DAT_0103aee0 + (*puVar4 & 0x7fff) * 4))(puVar4); // Dispatch command to handler
    
    return;
}