// FUNC_NAME: GodfatherGameManager::updateCrewState
void __fastcall GodfatherGameManager::updateCrewState(int this)
{
    int *piVar1;
    char cVar2;
    int crewData;
    int iVar3;
    undefined4 uVar4;
    undefined4 *puVar5;
    int iVar6;
    uint uVar7;
    int *piVar8;
    int local_c;
    int local_8;
    undefined4 local_4;
    
    local_8 = this;
    FUN_008fad60(1,1);  // Debug/Profiling function
    crewData = FUN_008c74d0(0x637b907);  // Get crew data by hash
    local_c = crewData;
    if (crewData != 0) {
        FUN_00785d60(crewData);  // Increment reference count
    }
    
    // Clear AI combat flags for all crew members
    uVar7 = 0;
    if (*(int *)(this + 0x1a3c) != 0) {  // +0x1a3c: crew member count
        piVar8 = (int *)(this + 0x193c);  // +0x193c: crew member array start
        do {
            // Clear bit 1 (0x2) of combat flags at +0x2c
            *(uint *)(*piVar8 + 0x2c) = *(uint *)(*piVar8 + 0x2c) & 0xfffffffd;
            FUN_00788720();  // Update something per crew member
            uVar7 = uVar7 + 1;
            piVar8 = piVar8 + 1;
            iVar3 = crewData;
        } while (uVar7 < *(uint *)(local_8 + 0x1a3c));
    }
    
    local_4 = DAT_01223414;
    uVar4 = FUN_008c6d20(2);  // Get manager list
    puVar5 = (undefined4 *)FUN_0043c2c0(uVar4);
    iVar6 = local_8;
    
    // Iterate through some managed objects
    for (piVar8 = (int *)*puVar5; local_8 = iVar6, piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
        piVar1 = (int *)*piVar8;
        if ((piVar1 != (int *)0x0) && (iVar6 = FUN_0043b870(DAT_0112af58), iVar6 != 0)) {
            FUN_00783810(crewData);  // Process crew member action
        }
        local_c = 0;
        // Check if entity is of a specific type (hash 0x369ac561)
        cVar2 = (**(code **)(*piVar1 + 0x10))(0x369ac561, &local_c);
        if ((cVar2 != '\0') && (local_c != 0)) {
            FUN_007196a0(0x637b907);  // Handle specific crew event
        }
        iVar6 = local_8;
    }
    
    // Additional processing for crew leader state
    if ((crewData != 0) && (*(int *)(iVar6 + 0x2c88) != 0)) {  // +0x2c88: crew leader pointer
        puVar5 = (undefined4 *)FUN_0043c2c0(*(undefined4 *)(crewData + 0x88));
        for (piVar8 = (int *)*puVar5; piVar8 != (int *)0x0; piVar8 = (int *)piVar8[1]) {
            if ((int *)*piVar8 != (int *)0x0) {
                local_8 = 0;
                cVar2 = (**(code **)(*(int *)*piVar8 + 0x10))(0x369ac561, &local_8);
                if ((cVar2 != '\0') && (local_8 != 0)) {
                    FUN_007196a0(*(undefined4 *)(*(int *)(iVar6 + 0x2c88) + 0x88));
                }
            }
        }
        // Check for player control mode
        if (((**(int **)(DAT_012233a0 + 4) != 0) && (**(int **)(DAT_012233a0 + 4) != 0x1f30)) &&
           (iVar3 = FUN_0043b870(DAT_01130fb0), iVar3 != 0)) {
            FUN_009ab6f0(*(undefined4 *)(*(int *)(iVar6 + 0x2c88) + 0x88));  // Force update crew behavior
        }
    }
    return;
}