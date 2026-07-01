// FUNC_NAME: Player::isWithinInteractionRange
bool __thiscall Player::isWithinInteractionRange(int thisPtr, char param_2, float *outDistanceSq)
{
    int iVar2;
    int iVar4;
    bool bVar3;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float local_c;
    float fStack_8;
    float local_4;

    iVar2 = DAT_0112af68; // Global game manager pointer
    iVar4 = *(int *)(thisPtr + 0x50); // +0x50: player's current entity/object pointer
    bVar3 = false;
    if ((*(int *)(iVar4 + 0x70) != 0) && (*(int *)(iVar4 + 0x70) != 0x48)) {
        if ((*(int *)(iVar4 + 0x70) == 0) ||
           ((*(int *)(iVar4 + 0x70) == 0x48 || ((*(byte *)(iVar4 + 0xc9) & 1) != 0)))) {
            // Player is in a state that allows interaction (state 0 or 0x48, or bit 0 of +0xC9 set)
            iVar4 = FUN_00471610(); // Get player position
            iVar5 = FUN_00471610(); // Get target position
            fVar11 = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30); // dx
            fVar10 = *(float *)(iVar5 + 0x34) - *(float *)(iVar4 + 0x34); // dy
            fVar12 = *(float *)(iVar5 + 0x38) - *(float *)(iVar4 + 0x38); // dz
            fVar10 = fVar12 * fVar12 + fVar10 * fVar10 + fVar11 * fVar11; // distance squared
            fVar11 = *(float *)(iVar2 + 0x370); // +0x370: default interaction range
            if (param_2 != '\0') {
                // If param_2 is true, check if the player is facing the target
                iVar4 = FUN_00471610(); // Get player forward vector
                iVar5 = FUN_00471610(); // Get target direction vector
                iVar6 = FUN_00471610(); // Get player right vector
                iVar7 = FUN_00471610(); // Get target direction (x component)
                iVar8 = FUN_00471610(); // Get target direction (y component)
                iVar9 = FUN_00471610(); // Get target direction (z component)
                // Dot product of forward and target direction
                if (*(float *)(iVar7 + 0x24) * *(float *)(iVar6 + 0x24) +
                    *(float *)(iVar4 + 0x20) * *(float *)(iVar5 + 0x20) +
                    *(float *)(iVar9 + 0x28) * *(float *)(iVar8 + 0x28) < DAT_00d75fb0) {
                    fVar11 = *(float *)(iVar2 + 0x374); // +0x374: tighter interaction range when not facing
                }
            }
        }
        else {
            // Player is in a different state (e.g., driving)
            if (*(float *)(DAT_0112af68 + 0x164) < _DAT_00d577a0) {
                iVar4 = FUN_00471610(); // Get player position
                uVar1 = *(undefined8 *)(iVar4 + 0x30); // player position (x,y)
                local_4 = *(float *)(iVar4 + 0x38); // player z
            }
            else {
                local_4 = *(float *)(DAT_0112af68 + 0x1e8); // +0x1E8: vehicle z position
                uVar1 = *(undefined8 *)(DAT_0112af68 + 0x1e0); // +0x1E0: vehicle x,y position
            }
            iVar4 = FUN_00471610(); // Get target position
            local_c = (float)uVar1;
            local_c = local_c - *(float *)(iVar4 + 0x30); // dx
            fStack_8 = (float)((ulonglong)uVar1 >> 0x20);
            fStack_8 = fStack_8 - *(float *)(iVar4 + 0x34); // dy
            local_4 = local_4 - *(float *)(iVar4 + 0x38); // dz
            fVar10 = local_4 * local_4 + fStack_8 * fStack_8 + local_c * local_c; // distance squared
            fVar11 = DAT_00d75f54; // Vehicle interaction range
        }
        bVar3 = fVar10 <= fVar11;
        if (outDistanceSq != (float *)0x0) {
            *outDistanceSq = fVar10;
        }
    }
    return bVar3;
}