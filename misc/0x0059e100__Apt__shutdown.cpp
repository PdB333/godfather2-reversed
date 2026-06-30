// FUNC_NAME: Apt::shutdown
void Apt::shutdown(void)
{
    int *piVar1;
    int *piVar2;
    code *pcVar3;
    int iVar4;
    uint uVar5;
    int unaff_FS_OFFSET;
    char *local_28;
    char *local_24;
    undefined4 local_20;
    int local_1c;
    undefined1 *local_18;
    char *local_14;
    char *local_10;
    undefined4 local_c;
    int local_8;
    undefined1 *local_4;
    
    // Get thread-local storage pointer (EA debug system)
    piVar1 = *(int **)(unaff_FS_OFFSET + 0x2c);
    
    // Check if Apt is initialized
    if (DAT_012055b0 == 0) {
        // Debug assertion: "bAptIsInitialized" at Apt.cpp line 0x8b
        local_28 = "bAptIsInitialized";
        local_24 = "..\\source\\Apt\\Apt.cpp";
        local_20 = 0x8b;
        local_1c = 2;
        local_18 = &DAT_01128f3a;
        if (DAT_01128f3a != '\0') {
            piVar2 = *(int **)(*piVar1 + 0x30);
            uVar5 = 1;
            if (piVar2 == (int *)0x0) {
LAB_0059e16f:
                if ((uVar5 & 2) != 0) {
                    *local_18 = 0;
                }
            }
            else {
                uVar5 = (**(code **)(*piVar2 + 8))(&local_28, "bAptIsInitialized");
                if (local_18 != (undefined1 *)0x0) goto LAB_0059e16f;
            }
            if (((piVar2 != (int *)0x0) || (local_1c != 4)) &&
               (((uVar5 & 1) != 0 || ((local_1c == 0 || (local_1c == 1)))))) {
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
            }
        }
    }
    
    // Check if pool exists
    if (DAT_0119a9cc != 0) goto LAB_0059e213;
    local_14 = "gpPool";
    local_10 = "..\\source\\Apt\\Apt.cpp";
    local_c = 0x8d;
    local_8 = 2;
    local_4 = &DAT_01128f3b;
    if (DAT_01128f3b == '\0') goto LAB_0059e213;
    piVar1 = *(int **)(*piVar1 + 0x30);
    uVar5 = 1;
    if (piVar1 == (int *)0x0) {
LAB_0059e1f2:
        if ((uVar5 & 2) != 0) {
            *local_4 = 0;
        }
    }
    else {
        uVar5 = (**(code **)(*piVar1 + 8))(&local_14, "gpPool");
        if (local_4 != (undefined1 *)0x0) goto LAB_0059e1f2;
    }
    if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
       (((uVar5 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
    }
    
LAB_0059e213:
    // Cleanup pool
    iVar4 = DAT_0119a9cc;
    if (DAT_0119a9cc != 0) {
        FUN_005a5c30(DAT_0119a9cc);  // AptPool::destroy
        (*DAT_0119caf8)(iVar4, 0x3124);  // Free memory (size 0x3124)
    }
    iVar4 = DAT_0119caec;
    DAT_0119a9cc = 0;
    
    // Cleanup renderer
    if (DAT_0119caec != 0) {
        FUN_005a0f10();  // AptRenderer::shutdown
        FUN_005a11e0(iVar4);  // AptFont::cleanup
        (*DAT_0119caf8)(iVar4, 0x18);  // Free memory (size 0x18)
    }
    DAT_0119caec = 0;
    
    // Cleanup textures
    if (DAT_0119a9c8 != 0) {
        FUN_005a1860();  // AptTexture::cleanup
    }
    iVar4 = DAT_0119cae4;
    DAT_0119a9c8 = 0;
    
    // Cleanup display
    if (DAT_0119cae4 != 0) {
        FUN_005a0fb0();  // AptDisplay::cleanup
        (*DAT_0119caf8)(iVar4, 0x4c);  // Free memory (size 0x4c)
    }
    DAT_0119cae4 = 0;
    
    // Final cleanup
    FUN_005aa020();  // Apt::finalCleanup
    DAT_012055b0 = 0;  // Mark as uninitialized
    return;
}