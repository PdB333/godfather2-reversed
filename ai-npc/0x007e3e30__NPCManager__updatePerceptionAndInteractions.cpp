// FUNC_NAME: NPCManager::updatePerceptionAndInteractions
void __fastcall NPCManager::updatePerceptionAndInteractions(int thisPtr)
{
    int iVar1;
    uint uVar2;
    uint uVar3;
    char cVar4;
    int iVar5;
    int *piVar6;
    int *piVar7;
    int *piVar8;
    int iVar9;
    code *pcVar10;
    float *pfVar11;
    int *piVar12;
    float10 fVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    undefined4 uVar17;
    undefined4 uVar18;
    undefined4 uVar19;
    undefined4 uVar20;
    undefined4 uVar21;
    undefined4 uStack_130;
    int *local_128;
    int local_124;
    float *local_120;
    int *local_11c;
    float local_118;
    int local_114;
    float local_110;
    uint local_10c;
    int local_108;
    float local_104;
    undefined8 uStack_100;
    float fStack_f8;
    undefined8 uStack_f4;
    float fStack_ec;
    undefined1 auStack_e8 [12];
    undefined1 auStack_dc [12];
    undefined1 auStack_d0 [96];
    int iStack_70;
    undefined1 auStack_60 [92];
    
    // +0x80: some flag, set to 0
    *(undefined1 *)(thisPtr + 0x80) = 0;
    local_124 = thisPtr;
    FUN_007e17b0(); // probably resetPerceptionState or similar
    piVar12 = *(int **)(thisPtr + 0x58); // +0x58: pointer to player/NPC data
    iVar5 = FUN_00471610(); // get player position/transform
    local_104 = *(float *)(iVar5 + 0x34); // +0x34: player Y position
    pfVar11 = (float *)(iVar5 + 0x30); // +0x30: player position vector
    local_120 = pfVar11;
    piVar6 = (int *)FUN_007ab170(); // get some manager (maybe input/state manager)
    local_114 = 0;
    local_110 = DAT_00e445d0; // some distance threshold constant
    local_10c = 0;
    if (*(int *)(thisPtr + 0x90) != 0) { // +0x90: count of something (NPCs?)
        do {
            uVar2 = uStack_130;
            iVar5 = *(int *)(*(int *)(thisPtr + 0x8c) + local_10c * 8); // +0x8c: array of NPC entries
            if (((iVar5 != 0) && (local_11c = (int *)(iVar5 + -0x48), local_11c != (int *)0x0)) &&
               (local_11c != piVar12)) {
                iVar5 = FUN_00471610(); // get player position again
                fVar14 = *pfVar11 - *(float *)(iVar5 + 0x30);
                fVar15 = pfVar11[1] - *(float *)(iVar5 + 0x34);
                fVar16 = pfVar11[2] - *(float *)(iVar5 + 0x38);
                local_118 = fVar16 * fVar16 + fVar15 * fVar15 + fVar14 * fVar14; // squared distance to player
                uStack_130 = uStack_130 & 0xffffff;
                uVar3 = uStack_130;
                uStack_130._0_3_ = (undefined3)uVar2;
                if (((uint)piVar12[0x238] >> 4 & 1) == 0) { // +0x8E0: some flag check
                    local_108 = 0;
                    cVar4 = (**(code **)(*local_11c + 0x10))(0x369ac561, &local_108); // query NPC type/state
                    iVar9 = local_108;
                    iVar5 = local_124;
                    if ((cVar4 == '\0') || (local_108 == 0)) {
                        cVar4 = FUN_00481660(); // check if player is in combat
                        if (((cVar4 != '\0') &&
                            ((piVar12[0x7be] != -1 && (iVar5 = FUN_006c9470(local_11c, 0x383225a1), iVar5 != 0))) // check NPC relationship
                            ) && (cVar4 = FUN_007b9a80(piVar12, iVar5, 0), cVar4 != '\0')) {
                            cVar4 = FUN_00799a90(0); // check some game state
                            if ((cVar4 == '\0') || (cVar4 = FUN_00800c10(), cVar4 != '\0')) {
                                cVar4 = FUN_00800c10();
                                if ((cVar4 == '\0') ||
                                   ((((iVar9 = FUN_007b1060(piVar12, iVar5), iVar9 != 1 ||
                                      (cVar4 = FUN_007ab070(0x4000), cVar4 != '\0')) ||
                                     (cVar4 = FUN_00799a90(1), cVar4 == '\0')) ||
                                    ((cVar4 = FUN_00690150(0x3f), cVar4 != '\0' ||
                                     (cVar4 = FUN_00690150(0x3e), cVar4 != '\0')))))) goto LAB_007e42a9;
                            }
                            else {
                                cVar4 = FUN_007ab070(0x4000);
                                if ((cVar4 != '\0') && (iVar9 = FUN_007d65e0(), iVar9 != 0)) {
                                    FUN_007d65e0();
                                    iVar9 = FUN_00471610();
                                    fVar13 = (float10)FUN_0045c470(pfVar11, iVar9 + 0x30); // distance check
                                    if ((float10)local_118 <= fVar13) goto LAB_007e42a9;
                                }
                            }
                            FUN_007e16a0(iVar5); // start interaction
                            (**(code **)(*piVar6 + 4))(0x4000); // set flag
                        }
                        goto LAB_007e42a9;
                    }
                    uStack_130 = CONCAT13(1, (undefined3)uStack_130);
                    FUN_007e3a90(local_108); // process NPC type
                    if (local_118 <= *(float *)(iVar9 + 8000) * *(float *)(iVar9 + 8000)) { // +0x1F40: some radius
                        FUN_007e3b40(iVar9, local_118); // update distance-based state
                        if ((((*(int *)(iVar5 + 0x84) == 0) || (*(int *)(iVar5 + 0x84) == 0x48)) &&
                            ((iVar5 = FUN_006ad770(iVar9), iVar5 != 0 &&
                             (((cVar4 = FUN_0078a860(), cVar4 != '\0' && (local_118 < local_110)) &&
                              (iVar5 = FUN_00471610(),
                              (float)((uint)(local_104 - *(float *)(iVar5 + 0x34)) & DAT_00e44680) <
                              DAT_00d5eee4)))))) && (cVar4 = FUN_007e1850(iVar9), cVar4 == '\0')) {
                            local_110 = local_118;
                            local_114 = iVar9; // track closest NPC
                        }
                    }
                    cVar4 = FUN_007ab070(0x1000);
                    if ((cVar4 == '\0') && (cVar4 = FUN_007cbcd0(piVar12, iVar9, 1, 0), cVar4 != '\0')) {
                        if ((*(byte *)(iVar9 + 0x1f98) & 1) == 0) {
                            uVar20 = 0x1000;
                        }
                        else {
                            uVar20 = 0x40000000;
                        }
                        (**(code **)(*piVar6 + 4))(uVar20);
                    }
                    cVar4 = FUN_007ab070(0x4000);
                    if (cVar4 == '\0') {
                        iVar5 = FUN_00716c30(); // get current target
                        if (iVar5 == 0) {
                            iVar5 = FUN_006c94a0(); // get some other entity
                        }
                        if ((iVar9 == iVar5) && (cVar4 = FUN_007b9a80(piVar12, iVar9, 0), cVar4 != '\0')) {
                            (**(code **)(*piVar6 + 4))(0x4000);
                        }
                    }
                    cVar4 = FUN_007ab070(0x8000);
                    if (cVar4 == '\0') {
                        iVar5 = FUN_00716c30();
                        if (iVar5 == 0) {
                            iVar5 = FUN_006c94a0();
                        }
                        if ((iVar9 == iVar5) && (cVar4 = FUN_007b9a20(piVar12, iVar9), cVar4 != '\0')) {
                            (**(code **)(*piVar6 + 4))(0x8000);
                        }
                    }
                    cVar4 = FUN_007ab070(0x40);
                    if ((((cVar4 == '\0') && (cVar4 = FUN_007b9a80(piVar12, iVar9, 1), cVar4 != '\0')) &&
                        (iVar5 = FUN_007fd780(), iVar9 == iVar5)) &&
                       (((cVar4 = FUN_00800c10(), cVar4 != '\0' && (cVar4 = FUN_00690150(0x22), cVar4 != '\0')
                        ) && (cVar4 = FUN_00799b10(), cVar4 != '\0')))) {
                        (**(code **)(*piVar6 + 4))(0x40);
                    }
                    cVar4 = FUN_007ab070(0x2000);
                    uVar3 = uStack_130;
                    if (cVar4 == '\0') {
                        switch((char)piVar12[0x7b1]) { // +0x1EC4: some state
                        case '\b':
                        case '\t':
                        case '\n':
                        case '\v':
                        case '\x10':
                        case '\x11':
                        case '\x1a':
                        case '\x1b':
                        case '\x1c':
                        case '\x1d':
                        case '\"':
                        case '#':
                            (**(code **)(*piVar6 + 4))(0x2000);
                        }
                    }
                    goto switchD_007e4161_caseD_c;
                }
LAB_007e42a9:
                if (((uint)piVar12[0x238] >> 4 & 1) == 0) {
                    local_128 = (int *)0x0;
                    cVar4 = (**(code **)(*local_11c + 0x10))(0xa5975eb2, &local_128);
                    piVar8 = local_128;
                    if ((cVar4 == '\0') || (pfVar11 = local_120, local_128 == (int *)0x0)) goto LAB_007e43c4;
                    uStack_130 = CONCAT13(1, (undefined3)uStack_130);
                    piVar7 = (int *)FUN_007ab320();
                    uVar3 = uStack_130;
                    if (piVar8 == piVar7) goto switchD_007e4161_caseD_c;
                    if (piVar7 != (int *)0x0) {
                        iVar5 = FUN_00471610();
                        fVar13 = (float10)FUN_0045c470(local_120, iVar5 + 0x30);
                        if (fVar13 <= (float10)local_118) goto switchD_007e4161_caseD_c;
                    }
                    iVar5 = FUN_007e1dd0(piVar8, local_118);
                    if (iVar5 != 0) {
                        FUN_007ab3a0(piVar8);
                        (**(code **)(*piVar6 + 4))(iVar5);
                    }
                    iVar5 = FUN_00691810();
                    if ((((iVar5 == 0) || (iVar5 = FUN_00691810(), *(char *)(iVar5 + 0x1ad) != '\x1a')) ||
                        (((uint)piVar12[0x238] >> 10 & 1) == 0)) ||
                       (cVar4 = FUN_007e1fb0(piVar8), cVar4 == '\0')) goto switchD_007e4161_caseD_c;
                    FUN_007ab3a0(piVar8);
                    uVar20 = 0x10;
LAB_007e45da:
                    uStack_130 = CONCAT13(1, (undefined3)uStack_130);
                    (**(code **)(*piVar6 + 4))(uVar20);
                    uVar3 = uStack_130;
                }
                else {
LAB_007e43c4:
                    local_128 = (int *)0x0;
                    cVar4 = (**(code **)(*local_11c + 0x10))(0x4ecfbe13, &local_128);
                    piVar7 = local_11c;
                    piVar8 = local_128;
                    if ((cVar4 != '\0') && (local_128 != (int *)0x0)) {
                        uStack_130 = CONCAT13(1, (undefined3)uStack_130);
                        if (((char)local_128[0x6a] == '\x01') || ((char)local_128[0x6a] == '\x02')) {
                            FUN_007e3c20(local_128); // handle specific NPC state
                        }
                        iVar5 = FUN_00471610();
                        fVar14 = *pfVar11 - *(float *)(iVar5 + 0x30);
                        fVar15 = pfVar11[1] - *(float *)(iVar5 + 0x34);
                        fVar16 = pfVar11[2] - *(float *)(iVar5 + 0x38);
                        uVar3 = uStack_130;
                        if ((fVar16 * fVar16 + fVar15 * fVar15 + fVar14 * fVar14 <= (float)piVar12[0x7da]) && // +0x1F68: detection range
                           (cVar4 = FUN_007f80e0(piVar8, piVar12[0x7db]), cVar4 != '\0')) {
                            (**(code **)(*piVar6 + 4))(0x8000000);
                        }
                        goto switchD_007e4161_caseD_c;
                    }
                    if (((uint)piVar12[0x238] >> 6 & 1) == 0) {
                        local_128 = (int *)0x0;
                        cVar4 = (**(code **)(*local_11c + 0x10))(0x63c15f4e, &local_128);
                        piVar8 = local_128;
                        if ((cVar4 == '\0') || (piVar7 = local_11c, local_128 == (int *)0x0)) goto LAB_007e458f;
                        uStack_130 = CONCAT13(1, (undefined3)uStack_130);
                        cVar4 = FUN_007e1a40(local_128);
                        uVar3 = uStack_130;
                        if (cVar4 != '\0') {
                            iVar5 = FUN_007ab330();
                            if (iVar5 != 0) {
                                iVar5 = FUN_00471610();
                                fVar13 = (float10)FUN_0045c470(pfVar11, iVar5 + 0x30);
                                if (fVar13 <= (float10)local_118) goto switchD_007e4161_caseD_c;
                            }
                            iVar5 = local_124;
                            FUN_007ab3b0(piVar8);
                            cVar4 = FUN_00795a90(uStack_130, 1);
                            if (cVar4 == '\0') {
                                (**(code **)(*piVar6 + 4))(8);
                            }
                            else {
                                (**(code **)(*piVar6 + 4))(0x4000000);
                                cVar4 = FUN_00793930();
                                if ((cVar4 != '\0') &&
                                   (piVar8 = (int *)FUN_006ad7f0(*(undefined4 *)(iVar5 + 0x58)),
                                   piVar8 != (int *)0x0)) {
                                    (**(code **)(*piVar8 + 0x24))(0xc47960f6);
                                }
                            }
                        }
                    }
                    else {
LAB_007e458f:
                        local_128 = (int *)0x0;
                        cVar4 = (**(code **)(*piVar7 + 0x10))(0x545c7e0f, &local_128);
                        piVar8 = local_128;
                        if ((cVar4 != '\0') && (local_128 != (int *)0x0)) {
                            uStack_130 = CONCAT13(1, (undefined3)uStack_130);
                            cVar4 = FUN_007e0f60(local_128);
                            uVar3 = uStack_130;
                            if (cVar4 != '\0') {
                                FUN_007ab3c0(piVar8);
                                uVar20 = 0x400000;
                                goto LAB_007e45da;
                            }
                        }
                    }
                }
switchD_007e4161_caseD_c:
                uStack_130 = uVar3;
                piVar8 = local_11c;
                if ((uStack_130._3_1_ == '\0' & ~*(byte *)(*(int *)(local_124 + 0x58) + 0x8e3) & 1) == 0) {
LAB_007e46cf:
                    pfVar11 = local_120;
                    param_1 = local_124;
                    if (uStack_130._3_1_ == '\0') {
                        local_128 = (int *)0x0;
                        cVar4 = (**(code **)(*piVar8 + 0x10))(0x346d561a, &local_128);
                        piVar7 = local_128;
                        if ((cVar4 == '\0') || (local_128 == (int *)0x0)) {
                            if (((uint)piVar12[0x23a] >> 0x1c & 1) == 0) {
                                local_128 = (int *)0x0;
                                cVar4 = (**(code **)(*piVar8 + 0x10))(0xd22e242b, &local_128);
                                piVar7 = local_128;
                                if ((cVar4 != '\0') && (local_128 != (int *)0x0)) {
                                    cVar4 = FUN_007e10d0(local_128);
                                    pfVar11 = local_120;
                                    param_1 = local_124;
                                    if (cVar4 != '\0') {
                                        FUN_007ab3f0(piVar7);
                                        iVar5 = *piVar6;
                                        uVar20 = 0x100000;
                                        goto LAB_007e465b;
                                    }
                                    goto LAB_007e466e;
                                }
                            }
                            local_128 = (int *)0x0;
                            cVar4 = (**(code **)(*piVar8 + 0x10))(0x1ea6b19a, &local_128);
                            piVar7 = local_128;
                            if ((cVar4 == '\0') || (local_128 == (int *)0x0)) {
                                cVar4 = FUN_007ab070(0x2000000);
                                pfVar11 = local_120;
                                param_1 = local_124;
                                if (((cVar4 == '\0') &&
                                    (((iVar5 = FUN_006e5740(), pfVar11 = local_120, param_1 = local_124, iVar5 == 0
                                      && (cVar4 = FUN_00481660(), pfVar11 = local_120, param_1 = local_124,
                                         cVar4 == '\0')) &&
                                     (iVar5 = FUN_0079ae70(piVar8, 0xa7039c8), pfVar11 = local_120,
                                     param_1 = local_124, iVar5 != 0)))) &&
                                   (((iVar9 = FUN_00716c30(), iVar9 == 0 ||
                                     (iVar9 = FUN_00716c30(), pfVar11 = local_120, param_1 = local_124,
                                     iVar9 == iVar5)) &&
                                    (pfVar11 = local_120, param_1 = local_124,
                                    (*(uint *)(iVar5 + 0x18c) >> 10 & 1) != 0)))) {
                                    iVar9 = FUN_00471610();
                                    pfVar11 = local_120;
                                    uStack_f4 = *(undefined8 *)(iVar9 + 0x30);
                                    fStack_ec = *(float *)(iVar9 + 0x38);
                                    fVar14 = local_120[1] - local_120[1];
                                    param_1 = local_124;
                                    if (((local_120[2] - fStack_ec) * (local_120[2] - fStack_ec) +
                                         fVar14 * fVar14 +
                                         (*local_120 - (float)uStack_f4) * (*local_120 - (float)uStack_f4) <=
                                         (float)piVar12[0x7da]) &&
                                       (cVar4 = FUN_007f80e0(iVar5, piVar12[0x7db]), param_1 = local_124, cVar4 != '\0'
                                       )) {
                                        fStack_f8 = pfVar11[2];
                                        uStack_100 = *(undefined8 *)pfVar11;
                                        iVar9 = FUN_008b8820(auStack_dc);
                                        uVar21 = 0;
                                        uVar19 = 0;
                                        uVar18 = 0x100000;
                                        uVar17 = 0x40002;
                                        uStack_100 = CONCAT44(*(undefined4 *)(iVar9 + 4), (undefined4)uStack_100);
                                        uVar20 = FUN_008b8820(auStack_e8);
                                        FUN_00542650(&uStack_100, uVar20, uVar17, uVar18, uVar19, uVar21);
                                        FUN_0046d6a0();
                                        FUN_009e5ed0(auStack_60, auStack_d0);
                                        param_1 = local_124;
                                        if (iStack_70 == 0) {
                                            (**(code **)(*piVar6 + 4))(0x2000000);
                                            FUN_007ab400(iVar5);
                                            param_1 = local_124;
                                        }
                                    }
                                }
                            }
                            else {
                                cVar4 = (**(code **)(*local_128 + 0x150))(*(undefined4 *)(local_124 + 0x58));
                                pfVar11 = local_120;
                                param_1 = local_124;
                                if (cVar4 != '\0') {
                                    FUN_007ab410(piVar7);
                                    (**(code **)(*piVar6 + 4))(0x20000);
                                    pfVar11 = local_120;
                                    param_1 = local_124;
                                }
                            }
                        }
                        else {
                            cVar4 = FUN_007e0ff0(local_128);
                            pfVar11 = local_120;
                            param_1 = local_124;
                            if (cVar4 != '\0') {
                                FUN_007ab3e0(piVar7);
                                pcVar10 = *(code **)(*piVar6 + 4);
                                if (piVar7[0x6a] == 0) {
                                    uVar20 = 0x800000;
                                }
                                else {
                                    uVar20 = 0x1000000;
                                }
                                goto LAB_007e4660;
                            }
                        }
                    }
                }
                else {
                    local_128 = (int *)0x0;
                    cVar4 = (**(code **)(*local_11c + 0x10))(0x8136ec1d, &local_128);
                    piVar7 = local_128;
                    if ((cVar4 == '\0') || (local_128 == (int *)0x0)) goto LAB_007e46cf;
                    cVar4 = FUN_007e1950(local_128);
                    pfVar11 = local_120;
                    param_1 = local_124;
                    if (cVar4 == '\0') goto LAB_007e466e;
                    FUN_007ab3d0(piVar7);
                    iVar5 = *piVar6;
                    uVar20 = 0x80000;
LAB_007e465b:
                    pcVar10 = *(code **)(iVar5 + 4);
LAB_007e4660:
                    (*pcVar10)(uVar20);
                    pfVar11 = local_120;
                    param_1 = local_124;
                }
            }
LAB_007e466e:
            iVar9 = local_114;
            iVar5 = local_124;
            local_10c = local_10c + 1;
        } while (local_10c < *(uint *)(param_1 + 0x90));
        if (local_114 != 0) {
            piVar12 = (int *)(local_124 + 0x84);
            iVar1 = local_114 + 0x48;
            if (*(int *)(local_124 + 0x84) != iVar1) {
                if (*(int *)(local_124 + 0x84) != 0) {
                    FUN_004daf90(piVar12); // remove from linked list
                }
                *piVar12 = iVar1;
                if (iVar1 != 0) {
                    *(undefined4 *)(iVar5 + 0x88) = *(undefined4 *)(iVar9 + 0x4c);
                    *(int **)(iVar9 + 0x4c) = piVar12;
                }
            }
            FUN_0093c780(iVar9); // process closest NPC
        }
    }
    return;
}