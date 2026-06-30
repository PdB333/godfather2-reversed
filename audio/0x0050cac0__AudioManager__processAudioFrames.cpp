// FUNC_NAME: AudioManager::processAudioFrames
int AudioManager::processAudioFrames(int frameCount, float param_2)
{
    byte *pbVar1;
    int *piVar2;
    float fVar3;
    int iVar4;
    undefined4 uVar5;
    uint uVar6;
    char cVar7;
    int in_EAX;
    int iVar8;
    int iVar9;
    int iVar10;
    uint uVar11;
    int iVar12;
    int *piVar13;
    uint uVar14;
    int unaff_FS_OFFSET;
    float fVar15;
    float fVar16;
    float fVar17;
    double dVar18;
    float fVar19;
    float fVar20;
    undefined8 uVar21;
    undefined4 local_110;
    undefined4 local_108;
    uint local_104;
    float local_100;
    int local_f4;
    undefined4 local_f0;
    uint local_e8;
    undefined4 local_e0;
    float local_dc;
    int local_d8;
    float local_d0;
    float fStack_cc;
    float fStack_c8;
    float local_a0 [4];
    undefined1 local_90 [32];
    uint local_70;
    float local_6c;
    float local_68;
    undefined4 local_64;
    uint local_60;
    float local_50;
    float fStack_4c;
    float fStack_48;
    undefined4 uStack_44;
    undefined4 local_40;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined4 uStack_34;
    undefined4 local_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    undefined4 uStack_24;
    undefined4 local_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    undefined4 uStack_14;
    
    fVar17 = DAT_00e2b1a4; // 1.0f
    if (frameCount < 1) {
        return 0;
    }
    iVar4 = *(int *)(in_EAX + 0x24); // audio context pointer
    fVar19 = 0.0;
    if ((*(byte *)(iVar4 + 0x10c) & 4) != 0) {
        param_2 = 0.0;
    }
    local_e8 = 0;
    if (*(char *)(iVar4 + 0x170) == '\x01') {
        local_e8 = 0x80;
    }
    *(uint *)(in_EAX + 0x2c) = *(uint *)(in_EAX + 0x2c) | 0x10;
    local_108 = 0x80;
    local_110 = 0x80;
    local_e0 = 0x80;
    local_104 = (uint)*(ushort *)(in_EAX + 0x76) + (uint)*(ushort *)(in_EAX + 0x74);
    fVar15 = fVar17 / (float)frameCount;
    local_100 = 0.0;
    if ((int)*(short *)(in_EAX + 0x5c) <= (int)local_104) {
        local_104 = local_104 - (int)*(short *)(in_EAX + 0x5c);
    }
    *(uint *)(in_EAX + 0x2c) = *(uint *)(in_EAX + 0x2c) & 0xfffffff7;
    local_dc = 0.0;
    if ((*(uint *)(iVar4 + 0x10c) & 0x2000000) != 0) {
        cVar7 = *(char *)(iVar4 + 0x157);
        FUN_00414aa0(); // getListenerPosition
        local_a0[cVar7] = fVar19;
        fVar16 = local_a0[1] * local_a0[1] + local_a0[2] * local_a0[2] + local_a0[0] * local_a0[0];
        fVar20 = fVar19;
        if (DAT_00e2cbe0 < fVar16) { // epsilon
            fVar20 = SQRT(fVar16);
            fVar19 = fVar17 / fVar20;
        }
        if (DAT_00e2e210 < fVar20) { // threshold
            dVar18 = (double)(fVar19 * local_a0[2]);
            FUN_00b9a9fa(); // sin/cos
            local_dc = DAT_00e44564 - (float)dVar18; // doppler shift
        }
    }
    *(int *)(in_EAX + 0x50) = *(int *)(in_EAX + 0x50) + frameCount;
    local_f4 = 0;
    if (0 < frameCount) {
        iVar4 = **(int **)(unaff_FS_OFFSET + 0x2c);
        local_d8 = frameCount;
        do {
            iVar9 = *(int *)(iVar4 + 8);
            piVar2 = (int *)(in_EAX + 0xb0 + ((int)local_104 >> 3) * 8);
            uVar14 = local_104 & 7;
            iVar8 = uVar14 * 0x50;
            iVar12 = *(int *)(in_EAX + 0xb0 + ((int)local_104 >> 3) * 8) + iVar8;
            *(undefined1 *)(iVar12 + 0x54 + iVar9) = 0;
            iVar12 = iVar12 + iVar9;
            *(undefined1 *)(*piVar2 + iVar8 + 0x55 + *(int *)(iVar4 + 8)) = 0;
            *(float *)(*piVar2 + uVar14 * 4 + *(int *)(iVar4 + 8)) = param_2;
            *(undefined2 *)(iVar12 + 0x56) = (undefined2)local_104;
            fVar17 = param_2;
            if (((*(uint *)(*(int *)(in_EAX + 0x24) + 0x108) & 0x1000) == 0) ||
               (fVar17 = *(float *)(iVar12 + 0x2c), fVar17 == DAT_00e44628)) {
                FUN_0050bfa0(iVar12 + 0x20U,local_100,fVar15); // interpolateAudioFrame
                iVar9 = DAT_01194a94;
                if (DAT_01194a94 == 0) {
LAB_0050ce41:
                    FUN_004e41b0(); // getSampleRate
                    *(float *)(iVar12 + 0x58) = fVar17;
                    fVar17 = DAT_00e2e50c; // default pitch
                    if ((*(uint *)(*(int *)(in_EAX + 0x24) + 0x104) & 0x10000) != 0) {
                        fVar17 = *(float *)(*(int *)(in_EAX + 0x24) + 0x174) * _DAT_00e449a0;
                    }
                    *(float *)(iVar12 + 0x6c) = fVar17;
                    if ((*(char *)(in_EAX + 0x5b) == '\0') &&
                       ((*(uint *)(*(int *)(in_EAX + 0x24) + 0x108) & 0x4000) != 0)) {
                        fVar17 = *(float *)(iVar12 + 0x30);
                        fVar19 = fVar17 * fVar17 + *(float *)(iVar12 + 0x34) * *(float *)(iVar12 + 0x34) +
                                 *(float *)(iVar12 + 0x38) * *(float *)(iVar12 + 0x38);
                        if (fVar19 <= DAT_00e2cbe0) {
                            fVar20 = 0.0;
                            fVar19 = 0.0;
                        }
                        else {
                            fVar19 = SQRT(fVar19);
                            fVar20 = DAT_00e2b1a4 / fVar19;
                        }
                        fVar16 = *(float *)(iVar12 + 0x34);
                        fVar3 = *(float *)(iVar12 + 0x38);
                        if (DAT_00e2e210 < fVar19) {
                            iVar9 = FUN_004e9fa0(); // getReverbData
                            iVar9 = iVar9 + (uint)(*(int *)(iVar4 + 0x34) != 0) * 0x98;
                            if (*(int *)(iVar9 + 4) != 0) {
                                iVar9 = *(int *)(iVar9 + 0xc);
                                local_50 = *(float *)(iVar9 + 0x40);
                                fStack_4c = *(float *)(iVar9 + 0x44);
                                fStack_48 = *(float *)(iVar9 + 0x48);
                                uStack_44 = *(undefined4 *)(iVar9 + 0x4c);
                                local_40 = *(undefined4 *)(iVar9 + 0x50);
                                uStack_3c = *(undefined4 *)(iVar9 + 0x54);
                                uStack_38 = *(undefined4 *)(iVar9 + 0x58);
                                uStack_34 = *(undefined4 *)(iVar9 + 0x5c);
                                local_30 = *(undefined4 *)(iVar9 + 0x60);
                                uStack_2c = *(undefined4 *)(iVar9 + 100);
                                uStack_28 = *(undefined4 *)(iVar9 + 0x68);
                                uStack_24 = *(undefined4 *)(iVar9 + 0x6c);
                                local_20 = *(undefined4 *)(iVar9 + 0x70);
                                uStack_1c = *(undefined4 *)(iVar9 + 0x74);
                                uStack_18 = *(undefined4 *)(iVar9 + 0x78);
                                uStack_14 = *(undefined4 *)(iVar9 + 0x7c);
                                fVar17 = fStack_48 * fVar3 * fVar20 + fStack_4c * fVar16 * fVar20 +
                                         local_50 * fVar20 * fVar17;
                                dVar18 = (double)fVar17;
                                FUN_00b9a9fa(); // sin/cos
                                fVar19 = DAT_00e44564;
                                fVar20 = DAT_00e44564 - (float)dVar18;
                                *(float *)(iVar12 + 0x2c) = fVar20;
                                iVar9 = *(int *)(in_EAX + 0x24);
                                if ((*(byte *)(iVar9 + 0x108) & 2) == 0) {
                                    fVar17 = *(float *)(iVar9 + 0xd0) * fVar17;
                                }
                                else {
                                    fVar17 = *(float *)(iVar9 + 0xd0);
                                }
                                *(float *)(iVar12 + 0x3c) = fVar19 - fVar17;
                                *(float *)(iVar12 + 0x2c) = *(float *)(*(int *)(in_EAX + 0x24) + 0x144) + fVar20;
                            }
                        }
                    }
                    else {
                        if (*(char *)(in_EAX + 0x5b) == '\x05') {
                            *(undefined4 *)(iVar12 + 0x2c) = *(undefined4 *)(*(int *)(in_EAX + 0x24) + 0x144);
LAB_0050d064:
                            FUN_004e41b0(); // getSampleRate
                            fVar17 = (fVar17 * DAT_00e2b04c - DAT_00e2b1a4) *
                                     *(float *)(*(int *)(in_EAX + 0x24) + 0x14c);
LAB_0050d0ee:
                            fVar17 = fVar17 + *(float *)(iVar12 + 0x2c);
LAB_0050d0f3:
                            *(float *)(iVar12 + 0x2c) = fVar17;
                        }
                        else {
                            fVar17 = *(float *)(*(int *)(in_EAX + 0x24) + 0x144) + local_dc;
                            *(float *)(iVar12 + 0x2c) = fVar17;
                            uVar11 = *(uint *)(*(int *)(in_EAX + 0x24) + 0x108);
                            if ((uVar11 & 1) != 0) {
                                if ((uVar11 & 0x4000000) != 0) goto LAB_0050d064;
                                FUN_004e41b0(); // getSampleRate
                                fVar17 = fVar17 * DAT_00e2a848;
                                goto LAB_0050d0f3;
                            }
                            if (*(int *)(*(int *)(in_EAX + 4) + 0x20) != 0) {
                                iVar9 = *(int *)(*(int *)(in_EAX + 4) + 0x20);
                                if (iVar9 != 0) {
                                    *(int *)(iVar9 + 4) = *(int *)(iVar9 + 4) + 1;
                                }
                                iVar9 = FUN_00513f70(iVar9); // getAudioSource
                                if (iVar9 != 0) {
                                    fVar17 = *(float *)(iVar9 + 0x38);
                                    goto LAB_0050d0ee;
                                }
                            }
                        }
                        if ((*(byte *)(*(int *)(in_EAX + 0x24) + 0x108) & 2) == 0) {
                            *(undefined4 *)(iVar12 + 0x3c) = *(undefined4 *)(*(int *)(in_EAX + 0x24) + 0xd0);
                        }
                        else {
                            FUN_004e41b0(); // getSampleRate
                            if ((*(uint *)(*(int *)(in_EAX + 0x24) + 0x108) & 0x400000) == 0) {
                                fVar17 = fVar17 * DAT_00e2b04c - DAT_00e2b1a4;
                            }
                            *(float *)(iVar12 + 0x3c) = *(float *)(*(int *)(in_EAX + 0x24) + 0xd0) * fVar17;
                        }
                    }
                    iVar9 = *(int *)(in_EAX + 0x24);
                    fVar17 = *(float *)(iVar9 + 0x8c);
                    fVar19 = fVar17;
                    FUN_004e41b0(); // getSampleRate
                    fVar20 = fVar19 * *(float *)(iVar9 + 400) + *(float *)(iVar9 + 0x18c);
                    iVar9 = *(int *)(in_EAX + 0x24);
                    fVar19 = fVar20;
                    FUN_004e41b0(); // getSampleRate
                    fVar19 = fVar19 * *(float *)(iVar9 + 0x198) + *(float *)(iVar9 + 0x194);
                    *(float *)(*piVar2 + iVar8 + 0x48 + *(int *)(iVar4 + 8)) = fVar20;
                    *(float *)(*piVar2 + iVar8 + 0x44 + *(int *)(iVar4 + 8)) = fVar19;
                    uVar11 = *(uint *)(*(int *)(in_EAX + 0x24) + 0x108);
                    if ((uVar11 & 0x20000) == 0) {
                        if ((uVar11 & 4) != 0) {
                            FUN_004e41b0(); // getSampleRate
                            fVar17 = fVar19 * *(float *)(*(int *)(in_EAX + 0x24) + 0x9c) + fVar17;
                        }
                    }
                    else {
                        fVar17 = (fVar20 - *(float *)(*(int *)(in_EAX + 0x24) + 0x8c)) * local_100 + fVar17;
                    }
                    *(float *)(*piVar2 + iVar8 + 0x40 + *(int *)(iVar4 + 8)) = fVar17;
                }
                else {
                    if ((*(byte *)(DAT_01194a94 + 0x20) & 2) != 0) {
                        FUN_00414aa0(); // getListenerPosition
                    }
                    if ((*(uint *)(iVar9 + 0x20) & 4) != 0) {
                        if ((*(uint *)(iVar9 + 0x20) & 1) == 0) {
                            FUN_00414aa0(); // getListenerPosition
                        }
                        else {
                            fVar16 = *(float *)(*(int *)(in_EAX + 0x24) + 0xd8) +
                                     *(float *)(*(int *)(in_EAX + 0x24) + 0xd4);
                            fVar17 = *(float *)(iVar9 + 0x14);
                            fVar19 = *(float *)(iVar9 + 0x18);
                            fVar20 = *(float *)(iVar9 + 0x1c);
                            uVar5 = *(undefined4 *)(iVar12 + 0x3c);
                            *(float *)(iVar12 + 0x30) =
                                 fVar16 * *(float *)(iVar9 + 0x10) + *(float *)(iVar12 + 0x30);
                            *(float *)(iVar12 + 0x34) = fVar16 * fVar17 + *(float *)(iVar12 + 0x34);
                            *(float *)(iVar12 + 0x38) = fVar16 * fVar19 + *(float *)(iVar12 + 0x38);
                            *(float *)(iVar12 + 0x3c) = fVar16 * fVar20 + *(float *)(iVar12 + 0x3c);
                            *(undefined4 *)(iVar12 + 0x3c) = uVar5;
                        }
                    }
                    fVar19 = *(float *)(iVar9 + 0x24);
                    fVar17 = fVar19;
                    if (fVar19 != DAT_00e2b1a4) {
                        uVar5 = *(undefined4 *)(iVar12 + 0x3c);
                        fVar17 = fVar19 * *(float *)(iVar12 + 0x30);
                        *(float *)(iVar12 + 0x30) = fVar17;
                        *(float *)(iVar12 + 0x34) = fVar19 * *(float *)(iVar12 + 0x34);
                        *(float *)(iVar12 + 0x38) = fVar19 * *(float *)(iVar12 + 0x38);
                        *(float *)(iVar12 + 0x3c) = fVar19 * *(float *)(iVar12 + 0x3c);
                        *(undefined4 *)(iVar12 + 0x3c) = uVar5;
                    }
                    if (*(int *)(iVar9 + 0x30) == 0) goto LAB_0050ce41;
                    *(float *)(iVar12 + 0x2c) =
                         *(float *)(*(int *)(iVar9 + 0x30) + 0xc) +
                         *(float *)(*(int *)(in_EAX + 0x24) + 0x144);
                    *(undefined4 *)(iVar12 + 0x3c) = *(undefined4 *)(*(int *)(iVar9 + 0x30) + 0x1c);
                    *(float *)(iVar12 + 0x40) =
                         *(float *)(*(int *)(iVar9 + 0x30) + 0x20) +
                         *(float *)(*(int *)(in_EAX + 0x24) + 0x8c);
                    *(float *)(iVar12 + 0x44) =
                         *(float *)(*(int *)(iVar9 + 0x30) + 0x24) +
                         *(float *)(*(int *)(in_EAX + 0x24) + 0x194);
                    fVar17 = *(float *)(*(int *)(iVar9 + 0x30) + 0x28) +
                             *(float *)(*(int *)(in_EAX + 0x24) + 0x18c);
                    *(float *)(iVar12 + 0x48) = fVar17;
                    pbVar1 = (byte *)(*piVar2 + iVar8 + 0x54 + *(int *)(iVar4 + 8));
                    *pbVar1 = *pbVar1 | 2;
                    if (*(int *)(iVar9 + 0x30) == 0) goto LAB_0050ce41;
                }
                fVar17 = *(float *)(*(int *)(in_EAX + 0x28) + 0x1c);
                if ((*(uint *)(*(int *)(in_EAX + 0x24) + 0x108) & 0x200000) != 0) {
                    fVar19 = *(float *)(*(int *)(in_EAX + 0x24) + 0x130);
                    if (fVar19 <= DAT_00e2b05c) {
                        FUN_004e41b0(); // getSampleRate
                        fVar19 = fVar19 * *(float *)(*(int *)(in_EAX + 0x24) + 0x130);
                    }
                    else {
                        FUN_004e41b0(); // getSampleRate
                        fVar19 = (fVar19 * DAT_00e2b04c - DAT_00e2b1a4) *
                                 *(float *)(*(int *)(in_EAX + 0x24) + 0x130);
                    }
                    fVar17 = fVar19 + fVar17;
                }
                *(float *)(*piVar2 + iVar8 + 0x4c + *(int *)(iVar4 + 8)) = fVar17;
                if (*(char *)(*(int *)(in_EAX + 0x24) + 0x170) == '\x02') {
                    iVar10 = DAT_0119478c + -1;
                    iVar9 = DAT_0119478c + 2;
                    if (iVar10 < 0) {
                        iVar10 = 0x13;
                    }
                    else if (0x13 < iVar9) {
                        iVar9 = DAT_0119478c + -0x12;
                    }
                    (&DAT_01194790)[iVar10] = (&DAT_01194790)[iVar10] + (&DAT_01194790)[iVar9];
                    local_e8 = (&DAT_01194790)[iVar10] & 0x80;
                    DAT_0119478c = iVar10;
                }
                iVar9 = *(int *)(in_EAX + 0x24);
                uVar11 = *(uint *)(iVar9 + 0x108);
                piVar13 = piVar2;
                if ((uVar11 & 0x9820000) != 0) {
                    if ((uVar11 & 0x20000) == 0) {
                        if ((uVar11 & 0x9000000) != 0) {
                            uVar21 = FUN_004e9200(); // getRandomFloat
                            uVar11 = (uint)uVar21;
                            iVar9 = *(int *)(in_EAX + 0x24);
                            fVar19 = (float)(uVar11 & 0x7fffff | 0x3f800000) - DAT_00e2b1a4;
                            fVar17 = fVar19;
                            fStack_cc = fVar19;
                            if ((*(uint *)(iVar9 + 0x108) & 0x8000000) == 0) {
                                uVar6 = uVar11 << 8;
                                fVar17 = (float)((uVar6 & 0x7fff | uVar11 >> 0x18) << 8 | uVar6 >> 0x18 | 0x3f800000
                                                ) - DAT_00e2b1a4;
                                fStack_cc = (float)(uVar6 & 0x7fffff | uVar11 >> 0x18 | 0x3f800000) - DAT_00e2b1a4;
                            }
                            local_d0 = *(float *)(iVar9 + 0xb0) * fVar19 + *(float *)(iVar9 + 0xa0);
                            fStack_cc = *(float *)(iVar9 + 0xb4) * fStack_cc + *(float *)(iVar9 + 0xa4);
                            fStack_c8 = *(float *)(iVar9 + 0xb8) * fVar17 + *(float *)(iVar9 + 0xa8);
                            piVar13 = (int *)((ulonglong)uVar21 >> 0x20);
                        }
                    }
                    else {
                        local_d0 = (*(float *)(iVar9 + 0xb0) - *(float *)(iVar9 + 0xa0)) * local_100 +
                                   *(float *)(iVar9 + 0xa0);
                        fStack_cc = (*(float *)(iVar9 + 0xb4) - *(float *)(iVar9 + 0xa4)) * local_100 +
                                    *(float *)(iVar9 + 0xa4);
                        fStack_c8 = (*(float *)(iVar9 + 0xb8) - *(float *)(iVar9 + 0xa8)) * local_100 +
                                    *(float *)(iVar9 + 0xa8);
                    }
                    local_d0 = DAT_00e44764 * local_d0;
                    fStack_cc = DAT_00e44764 * fStack_cc;
                    fStack_c8 = DAT_00e44764 * fStack_c8;
                    local_f0 = (undefined4)(longlong)ROUND(local_d0);
                    local_e0 = local_f0;
                    local_f0 = (undefined4)(longlong)ROUND(fStack_cc);
                    local_110 = local_f0;
                    local_f0 = (undefined4)(longlong)ROUND(fStack_c8);
                    local_108 = local_f0;
                }
                *(uint *)(*piVar13 + iVar8 + 0x5c + *(int *)(iVar4 + 8)) =
                     CONCAT31(CONCAT21(CONCAT11((undefined1)local_e0,(undefined1)local_110),
                                       (undefined1)local_108),(undefined1)local_e8);
            }
            if (((*(byte *)(*(int *)(iVar4 + 8) + *(int *)(in_EAX + 0x10)) & 8) != 0) &&
               ((*(uint *)(*(int *)(in_EAX + 0x24) + 0x10c) & 0x100) == 0)) {
                local_68 = param_2;
                local_70 = 0;
                local_64 = 1;
                local_6c = DAT_00e2b1a4;
                if ((*(uint *)(*(int *)(in_EAX + 0x24) + 0x10c) & 0x400) == 0) {
                    FUN_00414aa0(); // getListenerPosition
                    local_70 = local_70 | 2;
                }
                if ((*(uint *)(*(int *)(in_EAX + 0x24) + 0x10c) & 0x800) == 0) {
                    FUN_00414aa0(); // getListenerPosition
                    local_70 = local_70 | 4;
                }
                local_60 = -(uint)((*(uint *)(*(int *)(in_EAX + 0x24) + 0x108) & 0x80000000) != 0) &
                           iVar12 + 0x20U;
                FUN_0051ab70(*(undefined4 *)(in_EAX + 4),local_90); // submitAudioBuffer
            }
            cVar7 = *(char *)(in_EAX + 0x5b);
            if ((((cVar7 == '\0') || (cVar7 == '\x03')) || (cVar7 == '\x05')) ||
               (cVar7 = FUN_0050f900(in_EAX,piVar2,uVar14), cVar7 != '\0')) {
                local_f4 = local_f4 + 1;
                local_104 = local_104 + 1;
                if ((int)*(short *)(in_EAX + 0x5c) <= (int)local_104) {
                    local_104 = local_104 - (int)*(short *)(in_EAX + 0x5c);
                }
            }
            local_d8 = local_d8 + -1;
            local_100 = fVar15 + local_100;
        } while (local_d8 != 0);
    }
    *(short *)(in_EAX + 0x74) = *(short *)(in_EAX + 0x74) + (short)local_f4;
    return local_f4;
}