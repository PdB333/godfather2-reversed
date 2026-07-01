//FUNC_NAME: Character::modifyDamage
// Function address: 0x0081a0d0
// Role: Modifies incoming damage based on hit location, invulnerability flags, and other conditions.
// param_1: this pointer (Character object)
// param_2: damage source info (e.g., weapon or attacker)
// param_3: pointer to damage value (modified in place)
// Returns: true if damage was modified, false if damage should be zeroed or ignored.

bool Character::modifyDamage(int *thisObj, int damageSource, float *damage)
{
    float fVar1;
    int iVar2;
    char cVar3;
    int *piVar4;
    int iVar5;
    int iVar6;
    bool bVar7;
    float10 fVar8;
    float fVar9;
    int hitZone;          // local_8
    int hitSubZone;       // local_c
    int hitLocationIndex; // local_4

    iVar2 = *(int *)(damageSource + 0xf0); // +0xF0: some internal data pointer
    bVar7 = false;
    if (*damage <= 0.0 && *damage != 0.0) {
        return false;
    }
    // Check invulnerability flag (bit 5 of thisObj[0x6E5])
    if ((~(byte)((uint)thisObj[0x6E5] >> 5) & 1) == 0) {
        *damage = DAT_00d5ccf8; // likely 0.0f
        return false;
    }
    cVar3 = FUN_008184d0(&hitZone, &hitSubZone, &hitLocationIndex); // get hit location info
    if (cVar3 == '\0') {
        // No specific hit zone
        if (*(int *)(damageSource + 8) != 0) {
            FUN_0043b870(DAT_01130fa0); // play sound or effect
        }
        if (((*(uint *)(damageSource + 0x6C) & 0x10) != 0) ||
           ((((*(uint *)(damageSource + 0x6C) & 4) != 0 &&
             ((cVar3 = FUN_009a9b40(thisObj), cVar3 != '\0' ||
              (iVar6 = (**(code **)(*thisObj + 0x22C))(), iVar6 != 0)))) ||
            ((*(byte *)(damageSource + 0x70) & 0x10) != 0)))) {
            *damage = DAT_00d5ccf8;
            return false;
        }
        fVar9 = *(float *)(iVar2 + 0x1CC) + *damage; // accumulate damage?
    }
    else {
        bVar7 = damage != (float *)0x0;
        if ((((*(uint *)(damageSource + 0x6C) & 0x48) != 0) && (damage == (float *)0x0)) &&
           ((*(uint *)(damageSource + 0x6C) & 8) != 0)) {
            fRam00000000 = DAT_00d5ccf8;
        }
        // Access damage multiplier table at iVar2+0xD4
        fVar1 = *(float *)(iVar2 + 0xD4 +
                          hitLocationIndex * 4 + ((int)damage + (hitSubZone + hitZone * 2) * 2) * 0x14);
        fVar9 = DAT_00d5ccf8;
        if (fVar1 != 0.0) {
            if (*damage < 0.0) {
                return bVar7;
            }
            *damage = *damage + fVar1; // apply multiplier
            iVar6 = *(int *)(damageSource + 8);
            if ((hitZone != 0) && ((*(byte *)(damageSource + 0x6C) & 4) != 0)) {
                if (((hitZone == 1) && (damage == (float *)0x0)) &&
                   ((hitLocationIndex == 4 || (cVar3 = FUN_00730210(), cVar3 != '\0')))) {
                    fRam00000000 = *(float *)(iVar2 + 0xD4 + hitLocationIndex * 4) +
                                   (fRam00000000 - *(float *)(iVar2 + 0x124 + (hitLocationIndex + hitSubZone * 10) * 4));
                }
                piVar4 = (int *)FUN_00716b80(iVar6); // get character from handle
                iVar5 = (**(code **)(*piVar4 + 0x34))(); // get some state
                if (*(int *)(iVar5 + 0xC) == 0) {
                    piVar4 = (int *)0x0;
                }
                else {
                    piVar4 = (int *)(*(int *)(iVar5 + 0xC) + -0x48);
                }
                if (((thisObj == piVar4) && (*(int *)(iVar5 + 0x30) == 2)) &&
                   (DAT_01205224 < (uint)(*(int *)(iVar5 + 0x40) + *(int *)(iVar2 + 0xBC)))) {
                    *damage = *damage - *(float *)(iVar2 + 0xB8); // damage reduction
                }
                fVar9 = (float)thisObj[0x92F]; // some stat
                if (thisObj[0x92F] < 0) {
                    fVar9 = fVar9 + DAT_00e44578;
                }
                if ((0.0 < fVar9 * DAT_00d5efb8) &&
                   (DAT_01205228 < *(float *)(iVar2 + 0xC4) + fVar9 * DAT_00d5efb8)) {
                    fVar8 = (float10)FUN_00470300(thisObj); // get distance or health
                    fVar9 = (float)fVar8;
                    if (fVar9 < *(float *)(iVar2 + 0xCC)) {
                        if (fVar9 < *(float *)(iVar2 + 200) || fVar9 == *(float *)(iVar2 + 200)) {
                            *damage = *damage - *(float *)(iVar2 + 0xC0);
                        }
                        else {
                            *damage = *damage - (*(float *)(iVar2 + 0xCC) - fVar9) * *(float *)(iVar2 + 0xD0);
                        }
                    }
                }
            }
            iVar6 = *(int *)(iVar6 + 0x2528); // get attacker from damage source
            if (iVar6 == 0) {
                piVar4 = (int *)0x0;
            }
            else {
                piVar4 = (int *)(iVar6 + -0x48);
            }
            if (thisObj != piVar4) {
                return bVar7;
            }
            if (*damage <= _DAT_00d577a0) {
                return bVar7;
            }
            *damage = *damage - *(float *)(iVar2 + 0x1D4); // final reduction
            return bVar7;
        }
    }
    *damage = fVar9;
    return bVar7;
}