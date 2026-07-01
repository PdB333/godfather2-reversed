// FUNC_NAME: GodfatherGameManager::updateCleanup
void __fastcall GodfatherGameManager::updateCleanup(int this)
{
    int iVar1;
    int *piVar2;
    undefined4 *puVar3;
    int iVar4;
    
    // Check if bit 1 (0x2) is set in flags at +0x2c6c - cleanup pending for some resource
    if ((*(uint *)(this + 0x2c6c) >> 1 & 1) != 0) {
        FUN_004086d0(&DAT_012069b4);  // Release/destroy resource at DAT_012069b4
        *(uint *)(this + 0x2c6c) = *(uint *)(this + 0x2c6c) & 0xfffffffd;  // Clear bit 1
    }
    // Check if bit 5 (0x20) is set - cleanup pending for two resources
    if ((*(uint *)(this + 0x2c6c) >> 5 & 1) != 0) {
        FUN_004086d0(&DAT_011302b8);  // Release first resource
        FUN_004086d0(&DAT_01130248);  // Release second resource
        FUN_00408310(&DAT_011302b8);  // Deallocate/free first resource
        FUN_00408310(&DAT_01130248);  // Deallocate/free second resource
        *(uint *)(this + 0x2c6c) = *(uint *)(this + 0x2c6c) & 0xffffffdf;  // Clear bit 5
    }
    // Check if bit 2 (0x4) is set - cleanup pending for object at +0x10
    if ((*(uint *)(this + 0x2c6c) >> 2 & 1) != 0) {
        FUN_0083c9b0(this + 0x10);  // Destroy/release object at +0x10
        *(uint *)(this + 0x2c6c) = *(uint *)(this + 0x2c6c) & 0xfffffffb;  // Clear bit 2
    }
    // Check if bit 3 (0x8) is set - another cleanup pending for object at +0x10
    if ((*(uint *)(this + 0x2c6c) >> 3 & 1) != 0) {
        FUN_0083c9b0(this + 0x10);  // Destroy/release object at +0x10
        *(uint *)(this + 0x2c6c) = *(uint *)(this + 0x2c6c) & 0xfffffff7;  // Clear bit 3
    }
    // Process pending action queue at +0x1a3c (count) and +0x193c (current action)
    if (*(int *)(this + 0x1a3c) != 0) {
        do {
            iVar4 = *(int *)(this + 0x193c);  // Get current action
            if (iVar4 == *(int *)(this + 0x2c74)) {  // Check if it matches pending action
                *(undefined4 *)(this + 0x2c74) = 0;  // Clear pending action
            }
            iVar1 = *(int *)(this + 0x1a3c);  // Get action count
            if (iVar1 != 0) {
                if (iVar1 != 1) {
                    *(undefined4 *)(this + 0x193c) = *(undefined4 *)(this + 0x1938 + iVar1 * 4);  // Shift actions
                }
                *(int *)(this + 0x1a3c) = *(int *)(this + 0x1a3c) + -1;  // Decrement count
            }
            FUN_00788c50();  // Update/process something
            (**(code **)(*(int *)(this + 0x1914) + 4))(iVar4, 0);  // Call action handler
        } while (*(int *)(this + 0x1a3c) != 0);
    }
    // Process global object list at DAT_00e52468
    if (DAT_00e52468 != -1) {
        puVar3 = (undefined4 *)FUN_0043c2c0(DAT_00e52468);  // Get object list
        piVar2 = (int *)*puVar3;
        while (piVar2 != (int *)0x0) {
            if (*piVar2 == 0) {
                iVar4 = 0;
            }
            else {
                iVar4 = FUN_0043b870(DAT_0112af58);  // Get some context/manager
            }
            (*(code *)**(undefined4 **)(iVar4 + 0x1c))(0);  // Call update/render on object
            piVar2 = (int *)*puVar3;
        }
    }
    return;
}