// FUN_00510110: CharacterMotion::update
void CharacterMotion::update(int param_1, int* param_2, int param_3)
{
    byte bVar1;
    int iVar2;
    int* piVar3;
    bool bVar4;
    char cVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    uint uVar9;
    int unaff_FS_OFFSET;
    float in_XMM0_Da;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    char local_8a;
    float local_7c;
    float local_70;
    float fStack_6c;
    float fStack_68;
    float fStack_64;
    undefined1 local_60 [16];
    undefined1 local_50 [48];
    float local_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;

    iVar2 = **(int**)(unaff_FS_OFFSET + 0x2c);
    iVar6 = param_3 * 0x50;
    iVar7 = *(int*)(*(int*)(param_1 + 4) + 0x20);
    iVar8 = *(int*)(iVar2 + 8) + iVar6 + 0x20 + *param_2;
    if (iVar7 != 0) {
        *(int*)(iVar7 + 4) = *(int*)(iVar7 + 4) + 1;
    }
    iVar7 = FUN_00513f70(iVar7);
    switch(*(undefined1*)(param_1 + 0x5b)) {
    case 1:
        iVar8 = *(int*)(*(int*)(param_1 + 0xac) + (uint)*(ushort*)(iVar8 + 0x36) * 4);
        if (iVar8 == 0) {
            return;
        }
        if (*(int*)(iVar8 + 0x10) == 0) {
            *(undefined4*)(param_1 + 0x60) = 0;
            FUN_004f98d0();
            return;
        }
        iVar7 = *(int*)(iVar8 + 0x20);
        local_7c = DAT_00e2b1a4;
        if (iVar7 != 0) {
            fVar10 = DAT_00e2b1a4;
            FUN_0050be90(param_1);
            *(float*)(iVar7 + 0x2c) = in_XMM0_Da;
            if ((*(byte*)(*(int*)(param_1 + 0x24) + 0x10c) & 0x20) == 0) {
                fStack_64 = *(float*)(param_1 + 0x48);
                local_70 = fVar10;
                fStack_6c = fVar10;
                fStack_68 = fVar10;
            }
            else {
                FUN_0050a810(param_1 + 0x24, param_2, *(undefined4*)(param_1 + 0x48));
            }
            *(float*)(iVar7 + 0x10) = local_70;
            *(float*)(iVar7 + 0x14) = fStack_6c;
            *(float*)(iVar7 + 0x18) = fStack_68;
            *(float*)(iVar7 + 0x1c) = fStack_64;
            local_7c = in_XMM0_Da;
        }
        FUN_0050a9d0(param_1, param_2, local_60);
        local_8a = FUN_0050ae70(param_1, param_2, param_3, &local_70, local_60, local_7c);
        FUN_00414aa0();
        FUN_00414aa0();
        *(float*)(*(int*)(iVar2 + 8) + iVar6 + 0x40 + *param_2) = local_7c;
        iVar7 = *(int*)(iVar2 + 8) + *(int*)(param_1 + 0x10);
        uVar9 = *(uint*)(*(int*)(iVar2 + 8) + *(int*)(param_1 + 0x10)) & 4;
        if (uVar9 != 0) {
            fVar10 = fStack_6c * *(float*)(iVar7 + 0x68);
            fVar11 = fStack_6c * *(float*)(iVar7 + 0x6c);
            fVar12 = local_70 * *(float*)(iVar7 + 0x54);
            fVar13 = local_70 * *(float*)(iVar7 + 0x58);
            fVar14 = local_70 * *(float*)(iVar7 + 0x5c);
            fVar15 = fStack_68 * *(float*)(iVar7 + 0x7c);
            local_7c = *(float*)(iVar7 + 0x80);
            local_70 = fStack_6c * *(float*)(iVar7 + 0x60) + local_70 * *(float*)(iVar7 + 0x50) +
                       fStack_68 * *(float*)(iVar7 + 0x70) + fStack_64 * local_7c;
            fStack_6c = fStack_6c * *(float*)(iVar7 + 100) + fVar12 +
                        fStack_68 * *(float*)(iVar7 + 0x74) + fStack_64 * *(float*)(iVar7 + 0x84);
            fStack_68 = fVar10 + fVar13 + fStack_68 * *(float*)(iVar7 + 0x78) +
                        fStack_64 * *(float*)(iVar7 + 0x88);
            fStack_64 = fVar11 + fVar14 + fVar15 + fStack_64 * *(float*)(iVar7 + 0x8c);
        }
        if ((*(uint*)(*(int*)(param_1 + 0x24) + 0x108) & 0x4000) == 0) {
            if (uVar9 == 0) {
                *(float*)(iVar8 + 0x60) = local_70;
                *(float*)(iVar8 + 100) = fStack_6c;
                *(float*)(iVar8 + 0x68) = fStack_68;
                *(float*)(iVar8 + 0x6c) = fStack_64;
            }
            else {
                FUN_0048efa0(iVar7 + 0x50, local_50);
                local_20 = local_70;
                fStack_1c = fStack_6c;
                fStack_18 = fStack_68;
                fStack_14 = fStack_64;
                FUN_004deb30();
            }
        }
        else {
            FUN_0050a940(param_2);
            FUN_0050fe90(param_1 + 0x24, local_7c);
            local_20 = local_70;
            fStack_1c = fStack_6c;
            fStack_18 = fStack_68;
            fStack_14 = fStack_64;
            FUN_004deb30();
        }
        bVar1 = *(byte*)(*(int*)(param_1 + 0x24) + 0x111);
        if ((bVar1 == 0) || (iVar8 = FUN_00509570(param_2), iVar8 < (int)(uint)bVar1))
        goto LAB_0051061c;
        LAB_005105d6:
            FUN_00414aa0();
            bVar4 = true;
            goto LAB_005105e5;
    case 2:
        if (*(int*)(*(int*)(param_1 + 0xac) + (uint)*(ushort*)(iVar8 + 0x36) * 4) != 0) {
            FUN_0050a9d0(param_1, param_2, &local_70);
            cVar5 = FUN_0050ae70(param_1, param_2, param_3, local_60, &local_70, 0);
            FUN_00414aa0();
            FUN_00414aa0();
            FUN_00510f60(param_1, param_2, param_3);
            piVar3 = *(int**)(*(int*)(param_1 + 0xac) + (uint)*(ushort*)(iVar8 + 0x36) * 4);
            if (((piVar3 != (int*)0x0) && (iVar8 = *piVar3, iVar8 != 0)) &&
               (piVar3 = (int*)(iVar8 + -0x48), piVar3 != (int*)0x0)) {
                (**(code**)(*piVar3 + 0x28))(local_50);
            }
            bVar1 = *(byte*)(*(int*)(param_1 + 0x24) + 0x111);
            if ((bVar1 == 0) || (*(byte*)(*param_2 + *(int*)(iVar2 + 8) + iVar6 + 0x55) < bVar1)) {
                bVar4 = false;
            }
            else {
                FUN_00414aa0();
                bVar4 = true;
            }
            if (((cVar5 != '\0') && ((*(byte*)(*(int*)(param_1 + 0x24) + 0x10c) & 0x40) != 0)) &&
               (bVar4)) {
                FUN_0050ca80(param_2);
                return;
            }
        }
        break;
    case 4:
        FUN_0050a9d0(param_1, param_2, &local_70);
        FUN_0050be90(param_1);
        fVar10 = DAT_00e2b1a4;
        if (iVar7 != 0) {
            fVar10 = *(float*)(iVar7 + 0x2c);
        }
        cVar5 = FUN_0050ae70(param_1, param_2, param_3, local_60, &local_70, fVar10 * in_XMM0_Da);
        FUN_00414aa0();
        FUN_00414aa0();
        *(float*)(*(int*)(iVar2 + 8) + iVar6 + 0x40 + *param_2) = in_XMM0_Da;
        bVar1 = *(byte*)(*(int*)(param_1 + 0x24) + 0x111);
        if ((bVar1 == 0) || (*(byte*)(*(int*)(iVar2 + 8) + iVar6 + *param_2 + 0x55) < bVar1)) {
            bVar4 = false;
        }
        else {
            FUN_00414aa0();
            bVar4 = true;
        }
        if (((cVar5 != '\0') && ((*(byte*)(*(int*)(param_1 + 0x24) + 0x10c) & 0x40) != 0)) && (bVar4))
        {
            FUN_0050ca80(param_2);
        }
        break;
    case 6:
        iVar8 = *(int*)(*(int*)(param_1 + 0xac) + (uint)*(ushort*)(iVar8 + 0x36) * 4);
        if (iVar8 == 0) {
            return;
        }
        FUN_0050a9d0(param_1, param_2, local_60);
        FUN_0050be90(param_1);
        fVar10 = DAT_00e2b1a4;
        if (iVar7 != 0) {
            fVar10 = *(float*)(iVar7 + 0x2c);
        }
        if (*(int*)(iVar8 + 0x48) == 0) {
            local_8a = FUN_0050ae70(param_1, param_2, param_3, &local_70, local_60, fVar10 * in_XMM0_Da);
        }
        else {
            local_8a = FUN_0050ab80(param_2, param_3, &local_70, local_60, fVar10 * in_XMM0_Da);
        }
        FUN_00414aa0();
        FUN_00414aa0();
        *(float*)(*(int*)(iVar2 + 8) + iVar6 + 0x40 + *param_2) = in_XMM0_Da;
        bVar1 = *(byte*)(*(int*)(param_1 + 0x24) + 0x111);
        if ((bVar1 != 0) && (bVar1 <= *(byte*)(*(int*)(iVar2 + 8) + iVar6 + *param_2 + 0x55)))
        goto LAB_005105d6;
        LAB_0051061c:
            bVar4 = false;
        LAB_005105e5:
            if (((local_8a != '\0') && ((*(byte*)(*(int*)(param_1 + 0x24) + 0x10c) & 0x40) != 0)) &&
               (bVar4)) {
                FUN_0050ca80(param_2);
                return;
            }
    }
    return;
}