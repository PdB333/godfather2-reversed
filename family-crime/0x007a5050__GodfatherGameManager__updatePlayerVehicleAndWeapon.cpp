// FUNC_NAME: GodfatherGameManager::updatePlayerVehicleAndWeapon
void __fastcall GodfatherGameManager::updatePlayerVehicleAndWeapon(int this)
{
    int *piVar1;
    undefined4 *puVar2;
    int iVar3;
    undefined4 local_50;
    undefined4 local_4c;
    undefined4 local_48;
    undefined1 local_44[4];
    undefined4 *local_40;
    int local_3c[9];
    undefined4 local_18;
    undefined4 local_14;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;
    
    local_48 = 0;
    local_4c = 0;
    local_50 = 0;
    // Initialize some structure with parameters from global data
    FUN_008c9650(this, &local_50, _DAT_00e544b0, _DAT_00e544ac, 0);
    
    // Handle vehicle slot at +0x7e4
    piVar1 = (int *)(this + 0x7e4);
    if (*(int *)(this + 0x7e4) == 0) {
        local_c = _DAT_00d5ca1c;
        local_8 = DAT_00e44634;
        local_4 = 2; // Vehicle type
        iVar3 = FUN_008ca3b0(local_44);
        if (*piVar1 != iVar3) {
            if (*piVar1 != 0) {
                FUN_004daf90(piVar1); // Release previous vehicle
            }
            *piVar1 = iVar3;
            if (iVar3 != 0) {
                *(undefined4 *)(this + 0x7e8) = *(undefined4 *)(iVar3 + 4);
                *(int **)(iVar3 + 4) = piVar1;
            }
        }
    }
    
    // Handle weapon slot 1 at +0x7fc
    piVar1 = (int *)(this + 0x7fc);
    if (*(int *)(this + 0x7fc) == 0) {
        local_18 = *(undefined4 *)(this + 0x2050);
        local_14 = *(undefined4 *)(this + 0x204c);
        local_c = *(undefined4 *)(this + 0x2054);
        local_8 = *(undefined4 *)(this + 0x2058);
        local_4 = 5; // Weapon type
        iVar3 = FUN_008ca3b0(local_44);
        if (*piVar1 != iVar3) {
            if (*piVar1 != 0) {
                FUN_004daf90(piVar1); // Release previous weapon
            }
            *piVar1 = iVar3;
            if (iVar3 != 0) {
                *(undefined4 *)(this + 0x800) = *(undefined4 *)(iVar3 + 4);
                *(int **)(iVar3 + 4) = piVar1;
            }
        }
    }
    
    // Handle weapon slot 2 at +0x804
    piVar1 = (int *)(this + 0x804);
    if (*(int *)(this + 0x804) == 0) {
        local_18 = *(undefined4 *)(this + 0x2030);
        local_14 = *(undefined4 *)(this + 0x202c);
        local_c = *(undefined4 *)(this + 0x203c);
        local_8 = *(undefined4 *)(this + 0x2040);
        local_4 = 5; // Weapon type
        iVar3 = FUN_008ca3b0(local_44);
        if (*piVar1 != iVar3) {
            if (*piVar1 != 0) {
                FUN_004daf90(piVar1); // Release previous weapon
            }
            *piVar1 = iVar3;
            if (iVar3 != 0) {
                *(undefined4 *)(this + 0x808) = *(undefined4 *)(iVar3 + 4);
                *(int **)(iVar3 + 4) = piVar1;
            }
        }
    }
    
    // Notify about update
    FUN_007f63b0(1);
    
    // Cleanup local list
    if (local_3c[0] != 0) {
        FUN_004daf90(local_3c);
    }
    while (local_40 != (undefined4 *)0x0) {
        puVar2 = (undefined4 *)local_40[1];
        local_40[1] = 0;
        *local_40 = 0;
        local_40 = puVar2;
    }
    return;
}