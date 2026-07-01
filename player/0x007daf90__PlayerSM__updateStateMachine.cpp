// FUNC_NAME: PlayerSM::updateStateMachine
void __fastcall PlayerSM::updateStateMachine(int this)
{
    bool bVar1;
    bool bVar2;
    char cVar3;
    float *pfVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    code *pcVar8;
    int *piVar9;
    undefined4 *puVar10;
    float fVar11;
    uint uVar12;
    int *piVar13;
    float10 fVar14;
    undefined4 uVar15;
    undefined4 uVar16;
    undefined4 uVar17;
    float local_80;
    int *local_7c;
    float local_78;
    int local_74;
    uint local_70;
    int *local_6c;
    float local_68;
    undefined4 local_64;
    undefined4 local_60;
    undefined1 local_5c [12];
    undefined1 local_50 [12];
    undefined4 local_44;
    undefined4 local_34;
    float local_30;
    float local_2c;
    float local_28;
    undefined4 local_24;
    float local_14;

    // Static state initialization (first call)
    if ((_DAT_0112bad8 & 1) == 0) {
        _DAT_0112bad8 = _DAT_0112bad8 | 1;
        _DAT_0112bad4 = 0;
    }

    // Get current state from state machine
    local_78 = *(float *)(*(int *)(this + 0x74) + 4); // +0x74: stateMachine, +4: currentState
    piVar13 = *(int **)(this + 0x58); // +0x58: playerData
    local_70 = DAT_0122339c;
    local_7c = piVar13;
    local_74 = this;
    fVar14 = (float10)FUN_00425190(piVar13[0x925]); // Get some time value
    local_6c = (int *)(float)fVar14;

    // Check if we should force state transition
    if ((fVar14 <= (float10)DAT_00e44750) ||
       ((-1 < piVar13[0x239] && (((uint)piVar13[0x239] >> 0x1e & 1) == 0)))) {
        bVar1 = false;
        if (((float)local_6c <= DAT_00e44750) &&
           (((piVar13[0x239] < 0 || (((uint)piVar13[0x239] >> 0x1e & 1) != 0)) &&
            (pfVar4 = (float *)FUN_00425060(&local_68,piVar13[0x925]),
            *pfVar4 <= DAT_00d6f400 && DAT_00d6f400 != *pfVar4)))) {
            FUN_00425060(&local_68,piVar13[0x925]);
            FUN_00424fb0(local_5c,piVar13[0x925]);
            local_44 = 0;
            local_34 = 0;
            local_24 = 0;
            local_14 = _DAT_00d5780c;
            FUN_0056b8a0(local_64,local_68,local_60,local_50);
            iVar5 = FUN_00471610();
            iVar6 = FUN_00471610();
            iVar7 = FUN_00471610();
            piVar13 = local_7c;
            if (_DAT_00d577a0 <
                *(float *)(iVar6 + 0x24) * local_2c + *(float *)(iVar5 + 0x20) * local_30 +
                *(float *)(iVar7 + 0x28) * local_28) goto LAB_007db13d;
        }
    }
    else {
LAB_007db13d:
        bVar1 = true;
    }

    // Check for special conditions (combat, etc.)
    bVar2 = false;
    if ((piVar13[0x93f] != 0) && (piVar9 = (int *)(piVar13[0x93f] + -0x48), piVar9 != (int *)0x0)) {
        local_80 = 0.0;
        cVar3 = (**(code **)(*piVar9 + 0x10))(0x55859efa,&local_80);
        if ((cVar3 != '\0') && (local_80 != 0.0)) {
            cVar3 = FUN_007f47a0();
            if ((cVar3 != '\0') ||
               ((iVar5 = FUN_0043b870(DAT_01130950), iVar5 != 0 &&
                ((*(uint *)(iVar5 + 0x4c) >> 1 & 1) != 0)))) {
                bVar2 = true;
            }
            cVar3 = FUN_007fd720();
            if (cVar3 != '\0') {
                bVar2 = false;
            }
        }
    }

    local_80 = _DAT_00d5780c;
    if ((*(byte *)((int)piVar13 + 0x8e3) & 1) == 0) {
        if ((*(uint *)(*(int *)(this + 0x58) + 0x8e8) >> 0x1c & 1) == 0) {
            if ((*(byte *)((int)piVar13 + 0x249f) & 1) == 0) {
                cVar3 = FUN_007f7c50();
                if (((cVar3 != '\0') || (cVar3 = FUN_007fd720(), cVar3 != '\0')) ||
                   (cVar3 = FUN_00690210(0x43), cVar3 != '\0')) {
                    if ((*(int *)(this + 0xa0) != 0) && (*(int *)(this + 0xa0) != 0x48)) {
                        if (*(int *)(this + 0xa0) == 0) {
                            iVar5 = 0;
                        }
                        else {
                            iVar5 = *(int *)(this + 0xa0) + -0x48;
                        }
                        if ((*(int *)(iVar5 + 0x70) == 0) || (*(int *)(iVar5 + 0x70) == 0x48))
                        goto LAB_007db27c;
                    }
                    if (!bVar2) {
                        *(undefined4 *)(*(int *)(this + 0x74) + 8) = 2; // Set state to 2
                        goto LAB_007db412;
                    }
                }
LAB_007db27c:
                if (((((((_DAT_0112bad4 & 1) != 0) || (bVar1)) &&
                      ((*(uint *)(*(int *)(this + 0x58) + 0x8e4) >> 5 & 1) == 0)) &&
                     ((cVar3 = FUN_007ab500(0x11), cVar3 == '\0' &&
                      (cVar3 = FUN_007aefe0(0x27), cVar3 == '\0')))) &&
                    ((cVar3 = FUN_007aefe0(0x42), cVar3 == '\0' && (cVar3 = FUN_007aefe0(9), cVar3 == '\0'))
                    )) || (((*(byte *)(*(int *)(this + 0x58) + 0x8e3) & 1) != 0 || (bVar1)))) {
                    local_80 = DAT_00d5f18c;
                    *(undefined4 *)(*(int *)(this + 0x74) + 8) = 1; // Set state to 1
                    FUN_00425060(&local_68,piVar13[0x925]);
                    if (local_68 <= DAT_00d6f3fc) {
                        local_80 = DAT_00d6f3c8;
                    }
                }
                else {
                    iVar5 = FUN_007a5f40();
                    if ((iVar5 == 2) || (iVar5 = FUN_007a5f40(), iVar5 == 1)) {
                        if ((local_78 == 5.60519e-45) || (bVar1 = false, local_78 == 2.24208e-44)) {
                            bVar1 = true;
                        }
                        cVar3 = FUN_006dfdb0();
                        if ((cVar3 == '\0') || (!bVar1)) {
                            if (((_DAT_0112bad4 & 1) == 0) && (iVar5 = FUN_007a5f40(), iVar5 != 2)) {
                                *(undefined4 *)(*(int *)(this + 0x74) + 8) = 0x20; // Set state to 0x20
                            }
                            else {
                                *(undefined4 *)(*(int *)(this + 0x74) + 8) = 4; // Set state to 4
                            }
                        }
                        else {
                            *(undefined4 *)(*(int *)(this + 0x74) + 8) = 0x10; // Set state to 0x10
                        }
                    }
                    else {
                        cVar3 = FUN_007aefe0(0x25);
                        if ((((cVar3 == '\0') && (cVar3 = FUN_007ab500(0x11), cVar3 == '\0')) &&
                            (cVar3 = FUN_007aefe0(0x27), cVar3 == '\0')) &&
                           ((cVar3 = FUN_007aefe0(0x42), cVar3 == '\0' &&
                            (cVar3 = FUN_007aefe0(9), cVar3 == '\0')))) {
                            *(undefined4 *)(*(int *)(this + 0x74) + 8) = 0x20; // Set state to 0x20
                        }
                        else {
                            *(undefined4 *)(*(int *)(this + 0x74) + 8) = 8; // Set state to 8
                        }
                    }
                }
            }
            else {
                *(undefined4 *)(*(int *)(this + 0x74) + 8) = 0x100; // Set state to 0x100
            }
        }
        else {
            *(undefined4 *)(*(int *)(this + 0x74) + 8) = 0x80; // Set state to 0x80
        }
    }
    else {
        *(float *)(*(int *)(this + 0x74) + 8) = local_78; // Keep current state
    }

LAB_007db412:
    // Handle state transition callbacks
    if (((*(int *)(this + 0x58) == 0) || (iVar5 = FUN_0043b870(DAT_01130950), iVar5 == 0)) ||
       ((*(uint *)(iVar5 + 0x4c) >> 1 & 1) == 0)) {
        uVar12 = *(uint *)(this + 0xc4) >> 1;
        if (local_80 <= (float)local_6c) {
            if ((uVar12 & 1) != 0) {
                *(uint *)(this + 0xc4) = *(uint *)(this + 0xc4) & 0xfffffffd;
                pcVar8 = *(code **)(*piVar13 + 0x304);
                goto LAB_007db470;
            }
        }
        else if ((uVar12 & 1) == 0) {
            *(uint *)(this + 0xc4) = *(uint *)(this + 0xc4) | 2;
            pcVar8 = *(code **)(*piVar13 + 0x308);
LAB_007db470:
            (*pcVar8)();
        }
    }

    uVar12 = local_70;
    local_80 = *(float *)(*(int *)(this + 0x74) + 8);
    if (piVar13[0x71e] == 0) {
        local_6c = (int *)0x0;
    }
    else {
        local_6c = (int *)(piVar13[0x71e] + -0x48);
    }
    local_70 = local_70 & 0xffffff00;

    // Handle state-specific logic
    if (local_78 != local_80) {
        DAT_0112bacc = local_78;
        if (local_78 == 8.96831e-44) {
            if (*(int *)(this + 0x90) == 0) {
                iVar5 = 0;
            }
            else {
                iVar5 = *(int *)(this + 0x90) + -0x48;
            }
            FUN_00424df0(0,iVar5,0x3f800000,1,0,0);
        }
        else if (local_78 == 1.79366e-43) {
            piVar9 = (int *)(this + 0x98);
            if (*(int *)(this + 0x98) == 0) {
                iVar5 = 0;
            }
            else {
                iVar5 = *(int *)(this + 0x98) + -0x48;
            }
            FUN_00424df0(piVar13[0x925],iVar5,0x3f800000,1,0,0);
            if ((*piVar9 != 0) &&
               (puVar10 = (undefined4 *)(*piVar9 + -0x48), puVar10 != (undefined4 *)0x0)) {
                (**(code **)*puVar10)(1);
            }
LAB_007db536:
            if (*piVar9 != 0) {
                FUN_004daf90(piVar9);
                *piVar9 = 0;
            }
        }
        else if (local_78 == 3.58732e-43) {
            local_70 = CONCAT31(SUB43(uVar12,1),1);
            FUN_007d9de0();
            iVar5 = *(int *)(this + 0xb8);
            piVar9 = (int *)(this + 0xb8);
            if (local_80 == 1.4013e-45) {
                if (iVar5 == 0) {
                    iVar5 = 0;
                }
                else {
                    iVar5 = iVar5 + -0x48;
                }
                uVar16 = 0;
                uVar15 = 0;
                iVar6 = piVar13[0x925];
            }
            else {
                if (iVar5 == 0) {
                    iVar5 = 0;
                }
                else {
                    iVar5 = iVar5 + -0x48;
                }
                uVar16 = 1;
                iVar6 = piVar13[0x925];
                uVar15 = 0x3f800000;
            }
            FUN_00424df0(iVar6,iVar5,uVar15,uVar16,0,0);
            if ((*piVar9 != 0) &&
               (puVar10 = (undefined4 *)(*piVar9 + -0x48), puVar10 != (undefined4 *)0x0)) {
                (**(code **)*puVar10)(1);
            }
            if (*piVar9 != 0) {
                FUN_004daf90(piVar9);
                *piVar9 = 0;
            }
            iVar5 = DAT_01129944;
            piVar9 = (int *)(this + 0xb0);
            if ((*(int *)(this + 0xb0) != 0) && (*(int *)(this + 0xb0) != 0x48)) {
                if ((*(int *)(this + 0xa8) != 0) && (*(int *)(this + 0xa8) != 0x48)) {
                    if (*(int *)(this + 0xa8) == 0) {
                        iVar6 = 0;
                    }
                    else {
                        iVar6 = *(int *)(this + 0xa8) + -0x48;
                    }
                    *(undefined8 *)(DAT_01129944 + 0x108) = *(undefined8 *)(iVar6 + 0xe4);
                    *(undefined4 *)(iVar5 + 0x110) = *(undefined4 *)(iVar6 + 0xec);
                }
                FUN_007d99b0();
                goto LAB_007db536;
            }
        }
    }

    iVar6 = local_74;
    piVar13 = local_7c;
    iVar5 = DAT_01129944;
    fVar11 = local_78;
    if ((float)(**(uint **)(this + 0x74) & (uint)local_80) == local_80) {
        if (local_78 == 2.8026e-45) {
            piVar13 = (int *)(this + 0xa0);
            if ((*(int *)(this + 0xa0) == 0) || (*(int *)(this + 0xa0) == 0x48)) goto LAB_007dba8c;
            if (local_80 != 2.8026e-45) {
LAB_007db6c8:
                if (*piVar13 == 0) {
                    iVar5 = 0;
                }
                else {
                    iVar5 = *piVar13 + -0x48;
                }
                FUN_00424df0(local_7c[0x925],iVar5,0x3f800000,(DAT_0112a900 == '\0') * '\x04' + '\x04',0,0);
                if ((*piVar13 != 0) &&
                   (puVar10 = (undefined4 *)(*piVar13 + -0x48), puVar10 != (undefined4 *)0x0)) {
                    (**(code **)*puVar10)(1);
                }
                if (*piVar13 != 0) {
                    FUN_004daf90(piVar13);
                    *piVar13 = 0;
                }
                goto LAB_007dba8c;
            }
            if (local_6c != (int *)0x0) {
                if (*piVar13 == 0) {
                    iVar5 = 0;
                }
                else {
                    iVar5 = *piVar13 + -0x48;
                }
                if (*(int *)(iVar5 + 0x70) == 0) {
                    piVar9 = (int *)0x0;
                }
                else {
                    piVar9 = (int *)(*(int *)(iVar5 + 0x70) + -0x48);
                }
                if (local_6c != piVar9) goto LAB_007db6c8;
            }
        }
        else {
            if (local_78 == 5.60519e-45) {
                if ((*(int *)(this + 0xa8) != 0) && (*(int *)(this + 0xa8) != 0x48)) {
                    if (local_80 == 5.60519e-45) goto LAB_007dbaaa;
                    if (local_80 != 2.24208e-44) {
                        if (local_80 == 1.4013e-45) {
                            DAT_0112a862 = 1;
                        }
                        if (*(int *)(this + 0x88) == 0) {
                            iVar6 = 0;
                        }
                        else {
                            iVar6 = *(int *)(this + 0x88) + -0x48;
                        }
                        *(undefined8 *)(DAT_01129944 + 0x108) = *(undefined8 *)(iVar6 + 0x1a0);
                        *(undefined4 *)(iVar5 + 0x110) = *(undefined4 *)(iVar6 + 0x1a8);
                        if (*(int *)(this + 0xa8) == 0) {
                            local_6c = (int *)0x0;
                        }
                        else {
                            local_6c = (int *)(*(int *)(this + 0xa8) + -0x48);
                        }
                        iVar5 = local_7c[0x925];
                        uVar16 = 0;
                        uVar15 = 0;
                        cVar3 = FUN_00690150(0x4f);
                        iVar6 = (-(uint)(cVar3 != '\0') & 5) + 2;
                        fVar14 = (float10)FUN_006d03a0(iVar6,uVar15,uVar16);
                        fVar11 = (float)fVar14;
                        goto LAB_007dba5d;
                    }
                }
            }
            else if (local_78 == 2.24208e-44) {
                piVar9 = (int *)(this + 0xa8);
                local_6c = piVar9;
                if ((*(int *)(this + 0xa8) != 0) && (*(int *)(this + 0xa8) != 0x48)) {
                    if (local_80 == 2.24208e-44) goto LAB_007dbaaa;
                    if ((local_80 == 5.60519e-45) || (local_80 == 4.48416e-44)) {
                        if (*piVar9 == 0) {
                            iVar7 = 0;
                        }
                        else {
                            iVar7 = *piVar9 + -0x48;
                        }
                        *(undefined8 *)(DAT_01129944 + 0x108) = *(undefined8 *)(iVar7 + 0xe4);
                        *(undefined4 *)(iVar5 + 0x110) = *(undefined4 *)(iVar7 + 0xec);
                        FUN_007d99b0();
                        piVar13 = (int *)(iVar6 + 0xb0);
                    }
                    else {
                        if ((local_80 != 1.4013e-45) && (local_80 != 3.58732e-43)) goto LAB_007dba8c;
                        FUN_006901e0(0x17);
                        iVar6 = local_74;
                        iVar5 = DAT_01129944;
                        if (*(int *)(local_74 + 0x88) == 0) {
                            iVar7 = 0;
                        }
                        else {
                            iVar7 = *(int *)(local_74 + 0x88) + -0x48;
                        }
                        *(undefined8 *)(DAT_01129944 + 0x108) = *(undefined8 *)(iVar7 + 0x1a0);
                        *(undefined4 *)(iVar5 + 0x110) = *(undefined4 *)(iVar7 + 0x1a8);
                        FUN_007d99b0();
                        puVar10 = (undefined4 *)(iVar6 + 0xb0);
                        if (*(int *)(iVar6 + 0xb0) != 0) {
                            FUN_004daf90(puVar10);
                            *puVar10 = 0;
                        }
                        if (*piVar9 == 0) {
                            iVar5 = 0;
                        }
                        else {
                            iVar5 = *piVar9 + -0x48;
                        }
                        iVar6 = piVar13[0x925];
                        uVar17 = 0;
                        uVar16 = 0;
                        uVar15 = 1;
                        fVar14 = (float10)FUN_006d03a0(1,0,0);
                        FUN_00424df0(iVar6,iVar5,(float)fVar14,uVar15,uVar16,uVar17);
                        piVar13 = local_6c;
                        if ((*local_6c != 0) &&
                           (puVar10 = (undefined4 *)(*local_6c + -0x48), puVar10 != (undefined4 *)0x0)) {
                            (**(code **)*puVar10)(1);
                            piVar13 = local_6c;
                        }
                    }
LAB_007dba7a:
                    if (*piVar13 != 0) {
                        FUN_004daf90(piVar13);
                        *piVar13 = 0;
                    }
                }
            }
            else if (local_78 == 1.12104e-44) {
                if ((*(int *)(this + 0xa8) != 0) && (*(int *)(this + 0xa8) != 0x48)) {
                    if (local_80 != 1.12104e-44) {
                        if (*(int *)(this + 0xa8) == 0) {
                            local_6c = (int *)0x0;
                        }
                        else {
                            local_6c = (int *)(*(int *)(this + 0xa8) + -0x48);
                        }
                        iVar5 = local_7c[0x925];
                        uVar16 = 0;
                        uVar15 = 0;
                        cVar3 = FUN_00690150(0x4f);
                        iVar6 = (-(uint)(cVar3 != '\0') & 2) + 2;
                        fVar14 = (float10)FUN_006d03a0(iVar6,uVar15,uVar16);
                        fVar11 = (float)fVar14;
LAB_007dba5d:
                        piVar13 = (int *)(this + 0xa8);
                        FUN_00424df0(iVar5,local_6c,fVar11,iVar6,uVar15,uVar16);
                        if ((*piVar13 != 0) &&
                           (puVar10 = (undefined4 *)(*piVar13 + -0x48), puVar10 != (undefined4 *)0x0)) {
                            (**(code **)*puVar10)(1);
                        }
                        goto LAB_007dba7a;
                    }
                    goto LAB_007dbaaa;
                }
            }
            else if (local_78 == 4.48416e-44) {
                if ((*(int *)(this + 0xa8) != 0) && (*(int *)(this + 0xa8) != 0x48)) {
                    if (local_80 != 4.48416e-44) {
                        if (*(int *)(this + 0xa8) == 0) {
                            local_6c = (int *)0x0;
                        }
                        else {
                            local_6c = (int *)(*(int *)(this + 0xa8) + -0x48);
                        }
                        iVar5 = local_7c[0x925];
                        uVar16 = 0;
                        uVar15 = 0;
                        cVar3 = FUN_00690150(0x4f);
                        iVar6 = (-(uint)(cVar3 != '\0') & 2) + 2;
                        fVar14 = (float10)FUN_006d03a0(iVar6,uVar15,uVar16);
                        fVar11 = (float)fVar14;
                        goto LAB_007dba5d;
                    }
                    goto LAB_007dbaaa;
                }
            }
LAB_007dba8c:
            if (local_78 != local_80) {
                *(undefined4 *)(local_74 + 0xc0) = DAT_01205228;
            }
        }
LAB_007dbaaa:
        *(float *)(*(int *)(local_74 + 0x74) + 4) = local_80;
        fVar11 = local_80;
        this = local_74;
    }

    // State-specific update functions
    if ((uint)fVar11 < 0x11) {
        if (fVar11 == 2.24208e-44) {
            if ((**(byte **)(this + 0x74) & 0x10) == 0) {
                return;
            }
            FUN_007da6d0();
            return;
        }
        switch(fVar11) {
        case 1.4013e-45:
            if ((**(byte **)(this + 0x74) & 1) != 0) {
                FUN_007da1e0();
                return;
            }
            break;
        case 2.8026e-45:
            if ((**(byte **)(this + 0x74) & 2) != 0) {
                FUN_007da480();
                return;
            }
            break;
        case 5.60519e-45:
            if ((**(byte **)(this + 0x74) & 4) != 0) {
                FUN_007da8b0(local_70);
                return;
            }
            break;
        case 1.12104e-44:
            if ((**(byte **)(this + 0x74) & 8) == 0) {
                return;
            }
switchD_007dbb5d_caseD_20:
            FUN_007da8b0(local_70);
        }
    }
    else {
        switch(fVar11) {
        case 4.48416e-44:
            goto switchD_007dbb5d_caseD_20;
        case 8.96831e-44:
            if ((**(byte **)(this + 0x74) & 0x40) != 0) {
                if (*(int *)(this + 0x90) == 0) {
                    iVar5 = 0;
                }
                else {
                    iVar5 = *(int *)(this + 0x90) + -0x48;
                }
                FUN_00424dc0(0,iVar5,0x3f800000,2,0);
                FUN_007da1e0();
                return;
            }
            break;
        case 1.79366e-43:
            if ((**(byte **)(this + 0x74) & 0x80) != 0) {
                FUN_007da030();
                return;
            }
            break;
        case 3.58732e-43:
            if ((**(uint **)(this + 0x74) & 0x100) != 0) {
                FUN_007d9e80();
                return;
            }
        }
    }
    return;
}