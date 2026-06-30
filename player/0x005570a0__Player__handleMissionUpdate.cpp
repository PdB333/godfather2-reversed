// FUNC_NAME: Player::handleMissionUpdate
void __thiscall Player::handleMissionUpdate(int this) // 0x005570a0
{
    int in_EAX;
    int *piVar1;
    undefined4 uVar2;
    char *pcVar3;
    int iVar4;
    undefined4 uStack_7c;
    undefined4 uStack_78;
    undefined4 uStack_74;
    undefined4 uStack_70;
    undefined1 auStack_6c [12];
    undefined1 local_60 [12];
    undefined4 local_54;
    undefined4 local_44;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined4 local_34;
    undefined1 auStack_2c [8];
    undefined4 local_24;
    
    local_54 = 0;
    local_44 = 0;
    local_34 = 0;
    local_24 = DAT_00e2b1a4; // Some global constant
    
    // Call virtual function at offset 0x90 on object at this+0x44
    // This likely gets the player's current mission state
    (**(code **)(**(int **)(in_EAX + 0x44) + 0x90))(local_60, in_EAX + 0x48, 1);
    
    uStack_7c = uStack_3c;
    uStack_78 = uStack_38;
    uStack_74 = local_34;
    uStack_70 = DAT_00e2b1a4;
    
    FUN_004b59d0(auStack_6c, &stack0xffffff54); // Some string/object copy
    FUN_00aa1fc0(in_EAX); // Update player state
    
    iVar4 = *(int *)(in_EAX + 0x40); // Get current mission ID
    if (iVar4 != 0) {
        piVar1 = (int *)(**(code **)(*DAT_0113dfc8 + 0x14))(); // Get mission manager
        uVar2 = (**(code **)(*piVar1 + 0x10))(iVar4); // Get mission data
        pcVar3 = (char *)FUN_00ab06f0(&stack0xffffff53, uVar2); // Get mission name
        if (*pcVar3 == '\0') goto LAB_00557194; // Empty name means no active mission
    }
    
    if (*(int *)(in_EAX + 0x40) != 0) {
        FUN_009f17c0(&stack0xffffff54); // Handle mission completion/update
        return;
    }
    
LAB_00557194:
    iVar4 = FUN_00556e10(); // Check for available missions
    if (iVar4 != 0) {
        if (*(int *)(iVar4 + 8) != 0) {
            FUN_00aa3930(&stack0xffffff54); // Start mission
            FUN_009de610(&uStack_7c, auStack_2c, param_1, iVar4); // Initialize mission
            return;
        }
        FUN_009f4cd0(&stack0xffffff54); // Handle mission failure/cancellation
    }
    return;
}