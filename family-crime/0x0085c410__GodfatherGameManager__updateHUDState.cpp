// FUNC_NAME: GodfatherGameManager::updateHUDState
void __fastcall GodfatherGameManager::updateHUDState(int this)
{
    char cVar1;
    int *piVar2;
    int iVar3;
    undefined4 uVar4;
    uint extraout_ECX;
    uint extraout_ECX_00;
    uint uVar5;
    int iVar6;
    uint uVar7;
    uint uVar8;
    int iStack_4;

    // Check if there's an active mission/objective
    piVar2 = (int *)(**(code **)(**(int **)(this + 4) + 0x1e4))();
    if (piVar2 != (int *)0x0) {
        iStack_4 = 0;
        cVar1 = (**(code **)(*piVar2 + 0x10))(0x383225a1, &iStack_4);
        if ((cVar1 != '\0') && (iStack_4 != 0)) {
            FUN_006d68e0(iStack_4);
            FUN_00544ae0(1);
            if (*(int *)(this + 8) == 0) {
                iVar3 = 0;
            } else {
                iVar3 = *(int *)(this + 8) + -0x48;
            }
            uVar4 = (**(code **)(*(int *)(iVar3 + 0x1f30) + 8))();
            iVar3 = FUN_00464930(&DAT_0112df70);
            if (iVar3 != 0) {
                FUN_00464960(uVar4, iVar3, 0);
            }
            goto LAB_0085c4c9;
        }
    }
    if (*(int *)(this + 8) != 0) {
        FUN_004daf90((undefined4 *)(this + 8));
        *(undefined4 *)(this + 8) = 0;
    }
LAB_0085c4c9:
    FUN_00549a50(0);
    FUN_00549a70(0);
    FUN_00549ab0(extraout_ECX & 0xffffff00);
    FUN_00549ac0(extraout_ECX_00 & 0xffffff00);
    FUN_00549a90(0);

    // Update HUD elements from the game state
    iVar3 = *(int *)(*(int *)(this + 4) + 0x368);
    uVar7 = (uint)*(char *)(iVar3 + 0x20);
    uVar5 = uVar7 - (int)**(char **)(iVar3 + 0x98);
    uVar8 = 0;
    if (3 < (int)uVar5) {
        iVar3 = 0;
        iVar6 = (uVar5 - 4 >> 2) + 1;
        uVar8 = iVar6 * 4;
        do {
            DAT_0112df40 = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x88 + iVar3);
            DAT_0112df50 = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3);
            DAT_0112df34._0_4_ = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3);
            iVar3 = iVar3 + 0xa0;
            iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
    }
    if (uVar8 < uVar5) {
        iVar3 = uVar8 * 0x28;
        iVar6 = uVar5 - uVar8;
        do {
            DAT_0112df40 = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3);
            DAT_0112df50 = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3);
            DAT_0112df34._0_4_ = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3);
            iVar3 = iVar3 + 0x28;
            iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
    }
    if (3 < (int)(uVar7 - uVar5)) {
        iVar3 = uVar5 * 0x28;
        iVar6 = ((uVar7 - uVar5) - 4 >> 2) + 1;
        uVar5 = uVar5 + iVar6 * 4;
        do {
            DAT_0112df44 = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x88 + iVar3);
            DAT_0112df54 = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3);
            DAT_0112df34._4_4_ = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3);
            iVar3 = iVar3 + 0xa0;
            iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
    }
    if (uVar5 < uVar7) {
        iVar3 = uVar5 * 0x28;
        iVar6 = uVar7 - uVar5;
        do {
            DAT_0112df44 = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3);
            DAT_0112df54 = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3);
            DAT_0112df34._4_4_ = *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3);
            iVar3 = iVar3 + 0x28;
            iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
    }

    // Update additional HUD data
    DAT_0112df48 = *(undefined4 *)(*(int *)(*(int *)(this + 4) + 0x38c) + 0xc);
    if ((((*(int *)(this + 8) == 0) || (*(int *)(this + 8) == 0x48)) ||
        (iVar3 = FUN_007ff880(), iVar3 == 0)) || (*(int *)(iVar3 + 0x360) == 0)) {
        DAT_0112df58 = 0;
    } else {
        DAT_0112df58 = *(undefined4 *)(*(int *)(*(int *)(iVar3 + 0x360) + 0x1c) + 0x188);
    }
    DAT_0112df3c = _DAT_00d5780c;
    DAT_0112df5c = 0;
    DAT_0112df5d = 0;
    DAT_0112df60 = 0;
    return;
}