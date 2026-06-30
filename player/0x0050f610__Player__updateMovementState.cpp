// FUNC_NAME: Player::updateMovementState
void __thiscall Player::updateMovementState(int thisPtr, float deltaTime)
{
    uint *puVar1;
    short sVar2;
    char cVar3;
    int iVar4;
    int *piVar5;
    undefined4 uVar6;
    int iVar7;
    int unaff_FS_OFFSET;
    
    // Check if player has a weapon equipped (offset +0xA0) and not in a state that blocks movement (offset +0xC & 0x20000)
    if ((*(int *)(thisPtr + 0xa0) != 0) &&
       (iVar4 = *(int *)(thisPtr + 4), (*(uint *)(iVar4 + 0xc) & 0x20000) == 0)) {
        uVar6 = 0;
        iVar7 = 0;
        // Get weapon data from player's weapon slot
        if (*(int *)(iVar4 + 0x20) != 0) {
            iVar4 = *(int *)(iVar4 + 0x20);
            if (iVar4 != 0) {
                *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + 1;
            }
            iVar4 = FUN_00513f70(iVar4); // Get weapon animation state
            if (iVar4 != 0) {
                iVar7 = *(int *)(iVar4 + 0x24);
                uVar6 = *(undefined4 *)(iVar4 + 0x28);
            }
        }
        // Update weapon state if changed
        if (*(int *)(thisPtr + 0xa0) != iVar7) {
            FUN_004f7bc0(); // Play weapon unequip sound
            *(int *)(thisPtr + 0xa0) = iVar7;
            *(undefined4 *)(thisPtr + 0xa4) = uVar6;
            if (iVar7 != 0) {
                FUN_004f7ba0(); // Play weapon equip sound
            }
        }
    }
    piVar5 = *(int **)(unaff_FS_OFFSET + 0x2c);
    // Handle movement timer (offset +0x4C) - countdown for movement state
    if ((0.0 < *(float *)(thisPtr + 0x4c)) &&
       (deltaTime = *(float *)(thisPtr + 0x4c) - deltaTime, *(float *)(thisPtr + 0x4c) = deltaTime,
       deltaTime <= 0.0)) {
        iVar4 = *piVar5;
        *(undefined4 *)(thisPtr + 0x4c) = DAT_00e2eff4; // Reset movement timer
        puVar1 = (uint *)(*(int *)(iVar4 + 8) + *(int *)(thisPtr + 0x10));
        *puVar1 = *puVar1 | 1; // Set movement state flag
    }
    // Check for sprint input
    cVar3 = FUN_0050d950(); // Check sprint button
    if (cVar3 != '\0') {
        iVar4 = *piVar5;
        *(uint *)(thisPtr + 0x2c) = *(uint *)(thisPtr + 0x2c) | 0x8000; // Set sprinting flag
        puVar1 = (uint *)(*(int *)(iVar4 + 8) + *(int *)(thisPtr + 0x10));
        *puVar1 = *puVar1 | 1; // Set movement state flag
    }
    sVar2 = *(short *)(thisPtr + 0x58);
    piVar5 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_FUN_01125130;
    *piVar5 = *piVar5 + 4;
    FUN_00514080(thisPtr, CONCAT44((int)sVar2, thisPtr + 0xb0), 4); // Send movement state to network
    return;
}