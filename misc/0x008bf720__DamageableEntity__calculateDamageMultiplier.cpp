// FUNC_NAME: DamageableEntity::calculateDamageMultiplier
float __fastcall DamageableEntity::calculateDamageMultiplier(int this)
{
    uint count;
    int *pData;
    int iVar6;
    int *piVar4;
    uint uVar5;
    int iVar3;
    int iVar2;
    float multiplier;
    float local_4;

    count = *(uint *)(this + 0x1a8);  // +0x1a8: number of damage modifiers
    uVar5 = 0;
    multiplier = _DAT_00d5780c;  // Base damage multiplier (likely global)
    
    if (3 < (int)count) {
        piVar4 = (int *)(*(int *)(this + 0x1a4) + 8);  // +0x1a4: damage modifier array
        iVar6 = (count - 4 >> 2) + 1;
        uVar5 = iVar6 * 4;
        do {
            iVar2 = piVar4[-2];
            // Check if modifier is active and not an invalid type (5,6,7 are likely invulnerability/immune)
            if ((((iVar2 != 0) && (iVar3 = *(int *)(iVar2 + 4), iVar3 != 5)) &&
                (iVar3 != 6)) && (iVar3 != 7)) {
                multiplier = *(float *)(iVar2 + 0x28) * multiplier;  // +0x28: damage multiplier value
            }
            iVar2 = piVar4[-1];
            if (((iVar2 != 0) && (iVar3 = *(int *)(iVar2 + 4), iVar3 != 5)) &&
               ((iVar3 != 6 && (iVar3 != 7)))) {
                multiplier = *(float *)(iVar2 + 0x28) * multiplier;
            }
            iVar2 = *piVar4;
            if (((iVar2 != 0) && (iVar3 = *(int *)(iVar2 + 4), iVar3 != 5)) &&
               ((iVar3 != 6 && (iVar3 != 7)))) {
                multiplier = *(float *)(iVar2 + 0x28) * multiplier;
            }
            iVar2 = piVar4[1];
            if ((((iVar2 != 0) && (iVar3 = *(int *)(iVar2 + 4), iVar3 != 5)) && (iVar3 != 6)) &&
               (iVar3 != 7)) {
                multiplier = *(float *)(iVar2 + 0x28) * multiplier;
            }
            piVar4 = piVar4 + 4;
            iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
    }
    if (uVar5 < count) {
        iVar6 = count - uVar5;
        piVar4 = (int *)(*(int *)(this + 0x1a4) + uVar5 * 4);
        float fVar7 = multiplier;
        do {
            iVar2 = *piVar4;
            if (((iVar2 != 0) && (iVar3 = *(int *)(iVar2 + 4), iVar3 != 5)) &&
               ((iVar3 != 6 && (iVar3 != 7)))) {
                fVar7 = *(float *)(iVar2 + 0x28) * fVar7;
                multiplier = fVar7;
            }
            piVar4 = piVar4 + 1;
            iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
    }
    return (float10)multiplier;
}