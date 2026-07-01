//FUNC_NAME: TargetingManager::selectBestTarget
void __thiscall TargetingManager::selectBestTarget(int thisPtr, undefined4 *outTarget, undefined4 param3, char param4)
{
    int *piVar1;
    int iVar2;
    float fVar3;
    char cVar4;
    int iVar5;
    int iVar6;
    undefined4 *puVar7;
    int iVar8;
    uint uVar9;
    int *piVar10;
    int iVar11;
    float10 fVar12;
    float local_5c;
    float local_58;
    float local_54;
    int local_50;
    int local_4c;
    int local_48;
    undefined4 *local_44;
    uint local_40;
    undefined4 local_3c;
    float local_38[2];
    int local_30;
    undefined1 local_2c;
    undefined4 local_28;
    undefined4 local_24;
    undefined4 local_20;
    float local_1c[2];
    int local_14;
    undefined1 local_10;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;
    
    iVar11 = DAT_01129904; // Global manager pointer
    iVar5 = 0;
    iVar8 = 0;
    piVar10 = (int *)(DAT_01129904 + 0x30); // +0x30: pointer to entity list?
    uVar9 = 0;
    local_50 = 0; // dynamic array pointer
    local_4c = 0; // count
    local_48 = 0; // capacity
    if (*(int *)(DAT_01129904 + 0x34) != 0) { // +0x34: number of entities
        do {
            iVar6 = *(int *)(*piVar10 + uVar9 * 4); // entity pointer
            iVar2 = *(int *)(iVar6 + 0x54); // entity type ID
            if (iVar2 == 0x637b907) { // specific type (e.g., "Gangster" or "NPC")
                if (*(uint *)(iVar6 + 0x10c) < 2) { // +0x10c: some state counter
                    if (iVar5 == iVar8) {
                        iVar5 = iVar8 * 2;
                        if (iVar8 == 0) {
                            iVar5 = 1;
                        }
                        FUN_00486800(iVar5); // realloc array
                        iVar5 = local_4c;
                        iVar8 = local_48;
                    }
                    puVar7 = (undefined4 *)(local_50 + iVar5 * 4);
                }
                else {
                    if (1 < *(uint *)(iVar6 + 0x118)) goto LAB_008c5ae6; // +0x118: another state
                    if (iVar5 == iVar8) {
                        iVar5 = iVar8 * 2;
                        if (iVar8 == 0) {
                            iVar5 = 1;
                        }
                        FUN_00486800(iVar5);
                        iVar5 = local_4c;
                        iVar8 = local_48;
                    }
                    puVar7 = (undefined4 *)(local_50 + iVar5 * 4);
                }
                iVar5 = iVar5 + 1;
                local_4c = iVar5;
                if (puVar7 != (undefined4 *)0x0) {
                    *puVar7 = 0x637b907; // store type ID
                }
            }
            else if ((uint)(*(int *)(iVar6 + 0x118) + *(int *)(iVar6 + 0x10c)) < 4) { // combined state < 4
                if (iVar5 == iVar8) {
                    iVar5 = iVar8 * 2;
                    if (iVar8 == 0) {
                        iVar5 = 1;
                    }
                    FUN_00486800(iVar5);
                    iVar5 = local_4c;
                    iVar8 = local_48;
                }
                piVar1 = (int *)(local_50 + iVar5 * 4);
                iVar5 = iVar5 + 1;
                local_4c = iVar5;
                if (piVar1 != (int *)0x0) {
                    *piVar1 = iVar2; // store entity type ID
                }
            }
LAB_008c5ae6:
            uVar9 = uVar9 + 1;
        } while (uVar9 < *(uint *)(iVar11 + 0x34));
    }
    uVar9 = 0;
    local_1c[0] = DAT_00e44758; // some float constant (maybe -infinity or 0)
    local_1c[1] = 0.0;
    local_14 = 0;
    local_10 = 0;
    local_8 = 0;
    FUN_009c8f10(0); // clear or init
    local_c = 0;
    local_4 = 0;
    local_38[0] = DAT_00e44758;
    local_38[1] = 0.0;
    local_30 = 0;
    local_2c = 0;
    local_24 = 0;
    FUN_009c8f10(0);
    iVar11 = 0;
    local_28 = 0;
    local_20 = 0;
    local_5c = DAT_00e44758; // best score for param3==0?
    local_58 = DAT_00e44758; // best score for param3!=0?
    if (*(int *)(thisPtr + 0x1a8) == 0) { // +0x1a8: count of something (e.g., allies?)
LAB_008c5b9a:
        if ((char)param3 != '\0') goto LAB_008c5ba5;
    }
    else {
        do {
            cVar4 = FUN_008c8110(); // check something (maybe alive?)
            if (cVar4 != '\0') {
                iVar11 = iVar11 + 1;
            }
            uVar9 = uVar9 + 1;
        } while (uVar9 < *(uint *)(thisPtr + 0x1a8));
        if (iVar11 == 0) goto LAB_008c5b9a;
LAB_008c5ba5:
        iVar11 = DAT_0112a558; // another global manager (e.g., EntityManager)
        uVar9 = 0;
        if (*(int *)(DAT_0112a558 + 0x38) != 0) { // +0x38: number of entities
            do {
                iVar8 = FUN_006b0770(uVar9); // get entity by index
                iVar5 = *(int *)(iVar8 + 0xc4); // +0xc4: some state (e.g., team or faction)
                local_54 = *(float *)(iVar8 + 0x40); // +0x40: position X?
                if ((((((iVar5 == 1) || (iVar5 == 0)) && (local_54 != *(float *)(thisPtr + 0x54))) && // not same ID
                     ((iVar6 = FUN_006b4860(), iVar6 == 0 && (*(int *)(iVar8 + 0xfc) == 0)))) && // not dead? and no special flag
                    ((*(int *)(iVar8 + 0x174) == 0 && // +0x174: some flag
                     (((*(uint *)(iVar8 + 0x34) >> 0x1c & 1) == 0 && (0.0 < *(float *)(iVar8 + 0x54)))))) // health > 0
                   && ((*(int *)(iVar8 + 0x44) != *(int *)(thisPtr + 0x54) && // different team?
                       (((*(float *)(iVar8 + 0x100) <= 0.0 && (iVar6 = FUN_00486770(&local_54), iVar6 == -1)
                         ) && (iVar6 = FUN_00849cf0(*(undefined4 *)(iVar8 + 0x48)),
                              (~*(byte *)(iVar6 + 0x58) & 1) != 0)))))) {
                    if ((((param4 != '\0') && ((~(byte)(*(uint *)(iVar8 + 0x34) >> 7) & 1) != 0)) && // param4 flag and some bit
                        (*(int *)(iVar8 + 0xd4) == 0)) && // +0xd4: some state
                       ((iVar5 == 0 || ((iVar5 == 1 && (iVar5 = FUN_0084a410(), iVar5 != 0)))))) {
                        fVar12 = (float10)FUN_008c4bb0(iVar8, param3); // evaluate score for param3==0
                        local_54 = (float)fVar12;
                        if ((float10)local_5c < fVar12) {
                            local_5c = local_54;
                            local_30 = iVar8; // best entity for param3==0
                        }
                    }
                    if ((~(byte)(*(uint *)(iVar8 + 0x34) >> 6) & 1) != 0) { // another bit check
                        fVar12 = (float10)FUN_008c4a90(iVar8, param3); // evaluate score for param3!=0
                        local_54 = (float)fVar12;
                        if ((float10)local_58 < fVar12) {
                            local_58 = local_54;
                            local_14 = iVar8; // best entity for param3!=0
                        }
                    }
                }
                uVar9 = uVar9 + 1;
            } while (uVar9 < *(uint *)(iVar11 + 0x38));
        }
    }
    local_44 = (undefined4 *)0x0; // candidate list
    local_40 = 0; // count
    local_3c = 0; // capacity
    if ((local_30 != 0) && ((char)param3 == '\0')) {
        local_38[1] = 2.8026e-45; // some flag
        local_38[0] = local_5c;
        FUN_008c4190(local_38); // add to candidate list
    }
    if (local_14 != 0) {
        local_1c[1] = 1.4013e-45;
        local_1c[0] = local_58;
        FUN_008c4190(local_1c);
    }
    puVar7 = local_44;
    if (local_40 != 0) {
        if (1 < local_40) {
            _qsort(local_44, local_40, 0x1c, (_PtFuncCompare *)&LAB_008bd540); // sort candidates
        }
        if (((*(byte *)(puVar7 + 1) & 3) == 0) && ((char)param3 != '\0')) {
            *outTarget = *puVar7;
            outTarget[1] = puVar7[1];
            outTarget[2] = puVar7[2];
        }
        else {
            fVar3 = (float)*(int *)(puVar7[2] + 0x68); // +0x68: some value (e.g., distance)
            if (*(int *)(puVar7[2] + 0x68) < 0) {
                fVar3 = fVar3 + DAT_00e44578; // adjust
            }
            uVar9 = 0;
            iVar11 = 0;
            if (*(int *)(thisPtr + 0x1a8) != 0) {
                do {
                    cVar4 = FUN_008c8110();
                    if (cVar4 != '\0') {
                        iVar11 = iVar11 + 1;
                    }
                    uVar9 = uVar9 + 1;
                } while (uVar9 < *(uint *)(thisPtr + 0x1a8));
            }
            uVar9 = iVar11 + 1U >> 1; // half of count
            if (uVar9 != 0) {
                FUN_006b1e10(uVar9); // allocate something
                cVar4 = FUN_008c0bb0(fVar3, uVar9, puVar7 + 4); // check condition
                if (cVar4 == '\0') {
                    if (puVar7[5] != 0) {
                        puVar7[5] = 0;
                    }
                    FUN_008c2b50(fVar3, uVar9, puVar7 + 4); // adjust
                }
            }
            if ((puVar7[5] == 0) && ((char)param3 == '\0')) goto LAB_008c5ec7;
            *outTarget = *puVar7;
            outTarget[1] = puVar7[1];
            outTarget[2] = puVar7[2];
        }
        FUN_00792320(puVar7 + 4); // cleanup
        *(undefined1 *)(outTarget + 3) = *(undefined1 *)(puVar7 + 3);
    }
LAB_008c5ec7:
    FUN_008c2020(); // final cleanup
    if (local_50 != 0) {
        FUN_009c8f10(local_50); // free array
    }
    return;
}