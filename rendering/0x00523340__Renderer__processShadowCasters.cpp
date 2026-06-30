// FUNC_NAME: Renderer::processShadowCasters
bool Renderer::processShadowCasters(int param_1) // param_1 likely Renderer* (this)
{
    short sVar1;
    undefined4 *puVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    float fVar17;
    int iVar18;
    float *pfVar19;
    void *_Dst;
    uint uVar20;
    undefined4 uVar21;
    int iVar22;
    uint uVar23;
    float *pfVar24;
    float *pfVar25;
    float fVar26;
    float fVar27;
    float fVar28;
    double dVar29;
    float fVar30;
    float fVar31;
    float fVar32;
    undefined1 *puVar33;
    float *pfVar34;
    float *pfVar35;
    float *pfVar36;
    float *pfVar37;
    float *pfVar38;
    uint uVar39;
    undefined1 *puVar40;
    int *piVar41;
    uint local_22ac;
    int local_22a8;
    float fStack_22a4;
    float fStack_2288;
    int local_2284;
    float fStack_2280;
    int local_2278;
    uint local_2274;
    float local_2270;
    float fStack_226c;
    float fStack_2268;
    float fStack_2264;
    float local_2260;
    float fStack_225c;
    float fStack_2258;
    float fStack_2254;
    float local_2250;
    float fStack_224c;
    float fStack_2248;
    float fStack_2244;
    float local_2240;
    float fStack_223c;
    float fStack_2238;
    float fStack_2234;
    float local_2230 [8];
    float local_2210;
    float local_220c;
    float local_2208;
    float local_2204;
    float local_2200;
    float local_21fc;
    float local_21f8;
    float local_21f4;
    undefined4 local_21e4;
    float local_21e0;
    float local_21dc;
    float local_21d8;
    float fStack_21d4;
    float local_21d0 [7];
    float fStack_21b4;
    float local_21b0;
    float fStack_21ac;
    float fStack_21a8;
    float fStack_21a4;
    float local_21a0;
    float fStack_219c;
    float fStack_2198;
    float fStack_2194;
    float local_2184;
    float local_2180;
    float local_217c;
    undefined4 local_2178;
    float local_2174;
    float local_2170;
    float local_216c;
    undefined4 local_2168;
    float local_2164;
    float local_2160;
    float local_215c;
    undefined4 local_2158;
    float local_2154;
    float local_2150;
    float local_214c;
    undefined4 local_2148;
    float local_2144;
    undefined4 local_2140;
    undefined4 local_213c;
    float local_2138;
    undefined4 local_2134;
    float fStack_2130;
    float fStack_212c;
    float fStack_2128;
    float fStack_2120;
    float fStack_211c;
    float fStack_2118;
    float local_2110;
    float fStack_210c;
    float fStack_2108;
    float fStack_2104;
    float local_2100;
    float fStack_20fc;
    float fStack_20f8;
    float fStack_20f4;
    float local_20f0;
    float fStack_20ec;
    float fStack_20e8;
    float fStack_20e4;
    float local_20e0;
    float fStack_20dc;
    float fStack_20d8;
    float fStack_20d4;
    float fStack_20d0;
    float fStack_20cc;
    float fStack_20c8;
    float fStack_20c4;
    float local_20c0;
    float fStack_20bc;
    float fStack_20b8;
    float fStack_20b4;
    float local_20b0;
    float fStack_20ac;
    float fStack_20a8;
    float fStack_20a4;
    undefined4 local_20a0;
    undefined4 uStack_209c;
    undefined4 uStack_2098;
    undefined4 uStack_2094;
    undefined4 uStack_2090;
    undefined4 uStack_208c;
    undefined4 uStack_2088;
    undefined4 uStack_2084;
    undefined4 uStack_2080;
    undefined4 uStack_207c;
    undefined4 uStack_2078;
    undefined4 uStack_2074;
    undefined4 local_2070;
    undefined4 local_206c;
    undefined4 local_2068;
    float local_2064;
    float local_2060;
    float fStack_205c;
    float fStack_2058;
    float fStack_2054;
    float local_2050;
    float fStack_204c;
    float fStack_2048;
    float fStack_2044;
    float fStack_2040;
    float fStack_203c;
    float fStack_2038;
    float fStack_2034;
    float fStack_2030;
    float fStack_202c;
    float fStack_2028;
    float fStack_2024;
    float fStack_2020;
    float fStack_201c;
    float fStack_2018;
    float fStack_2014;
    float fStack_2010;
    float fStack_200c;
    float fStack_2008;
    float fStack_2004;
    undefined1 local_2000 [64];
    undefined1 local_1fc0 [72];
    float local_1f78 [150];
    undefined **ppuStack_1d20;
    float *local_1d1c;
    int local_1d18;
    undefined1 local_1d14;
    undefined1 *puStack_1d10;
    int local_1d0c;
    undefined1 local_1d08 [600];
    float local_1ab0 [4];
    float afStack_1aa0 [2];
    int aiStack_1a98 [2];
    float afStack_1a90 [4];
    float afStack_1a80 [5];
    float fStack_1a6c;
    float fStack_1a68;
    float fStack_1a64;
    float fStack_1a60;
    float fStack_1a5c;
    undefined4 uStack_1a58;
    undefined4 uStack_1a54;
    float fStack_1a50;
    float fStack_1a4c;
    float fStack_1a48;
    float fStack_1a44;
    float fStack_1a40;
    float fStack_1a3c;
    undefined4 uStack_1a38;
    undefined4 uStack_1a34;
    float fStack_1a30;
    float fStack_1a2c;
    float fStack_1a28;
    float fStack_1a24;
    float fStack_1a20;
    float fStack_1a1c;
    int iStack_1a18;
    undefined4 uStack_1a14;
    float fStack_1a10;
    float fStack_1a0c;
    float fStack_1a08;
    float fStack_1a04;
    float fStack_1a00;
    float fStack_19fc;
    undefined4 uStack_19f8;
    undefined4 uStack_19f4;
    float local_7f0;
    float fStack_7ec;
    float fStack_7e8;
    undefined4 uStack_7e4;
    undefined **local_4d0 [154];
    undefined1 local_268 [596];
    undefined4 uStack_14;
    
    uStack_14 = 0x523350;
    local_22a8 = 0;
    local_2284 = 0;
    if ('\0' < *(char *)(param_1 + 0x450)) {
        pfVar25 = (float *)(param_1 + 0xf0);
        fVar26 = DAT_00e2b1a4;
        do {
            local_21e4 = *(undefined4 *)(param_1 + 0x464);
            *(undefined2 *)(pfVar25 + -0x14) = 0;
            *(undefined2 *)((int)pfVar25 + -0x4e) = 0;
            local_2278 = 0;
            if ((((*(int *)(param_1 + 0x454) != 0) && (pfVar25[-0x18] != 0.0)) &&
                (pfVar25[-0x18] != 5.60519e-45)) &&
               (((*(byte *)(param_1 + 0x460) >> 2 & 1) == 0 || (pfVar25[-0x13] != 0.0)))) {
                local_2230[0] = *(float *)(param_1 + 0x1c) * DAT_00e2cd54;
                local_2230[1] = (*(float *)(param_1 + 0x38) - *(float *)(param_1 + 0x3c)) * local_2230[0];
                local_2230[0] = (*(float *)(param_1 + 0x38) + *(float *)(param_1 + 0x3c)) * local_2230[0];
                local_2230[4] = DAT_00e44564 - local_2230[1];
                local_220c = DAT_00e44564 - local_2230[0];
                local_2060 = pfVar25[0xc];
                fStack_205c = pfVar25[0xd];
                fStack_2058 = pfVar25[0xe];
                fStack_2054 = pfVar25[0xf];
                local_2230[2] = 0.0;
                local_2230[6] = 0.0;
                local_2208 = 0.0;
                local_21f8 = 0.0;
                local_2230[3] = fVar26;
                local_2230[5] = local_2230[0];
                local_2230[7] = fVar26;
                local_2210 = local_2230[1];
                local_2204 = fVar26;
                local_2200 = local_220c;
                local_21fc = local_2230[4];
                local_21f4 = fVar26;
                local_21d8 = local_2230[1];
                local_2184 = local_2230[0];
                FUN_0044c1a0(local_1fc0);
                local_20c0 = pfVar25[8];
                fStack_20bc = pfVar25[9];
                fStack_20b8 = pfVar25[10];
                fStack_20b4 = pfVar25[0xb];
                local_217c = *(float *)(param_1 + 0x24);
                iVar18 = *(int *)(param_1 + 0x10);
                local_2180 = *(float *)(param_1 + 0x20);
                local_2178 = 0;
                local_216c = local_217c + *(float *)(iVar18 + 0xb4);
                local_2168 = 0;
                local_2160 = local_2180 + *(float *)(iVar18 + 0xb0);
                local_2158 = 0;
                local_214c = local_217c + *(float *)(iVar18 + 0xb4);
                local_2150 = local_2180 + *(float *)(iVar18 + 0xb0);
                local_2148 = 0;
                local_2174 = fVar26;
                local_2170 = local_2180;
                local_2164 = fVar26;
                local_215c = local_217c;
                local_2154 = fVar26;
                local_2144 = fVar26;
                FUN_0056c640(pfVar25,local_2000);
                fStack_20ac = 0.0;
                fStack_20a8 = 0.0;
                fStack_20a4 = 0.0;
                fStack_210c = 0.0;
                fStack_2108 = 0.0;
                fStack_2104 = 0.0;
                local_2100 = 0.0;
                fStack_20f8 = 0.0;
                fStack_20f4 = 0.0;
                local_20f0 = 0.0;
                fStack_20ec = 0.0;
                fStack_20e4 = 0.0;
                local_20e0 = 0.0;
                fStack_20dc = 0.0;
                fStack_20d8 = 0.0;
                local_2110 = fVar26;
                fStack_20fc = fVar26;
                fStack_20e8 = fVar26;
                fStack_20d4 = fVar26;
                local_20b0 = fVar26;
                if ((*(byte *)(*(int *)(param_1 + 0x10) + 0x44) & 1) != 0) {
                    local_2140 = 0;
                    local_213c = 0;
                    local_2134 = 0;
                    local_2138 = fVar26;
                    FUN_0056c040(local_21e4,&local_2140,&local_20a0);
                    local_2070 = 0;
                    local_206c = 0;
                    local_2068 = 0;
                    local_2064 = DAT_00e2b1a4;
                    fVar26 = DAT_00e2b1a4;
                    FUN_00417560();
                    local_2110 = local_2270;
                    fStack_210c = fStack_226c;
                    fStack_2108 = fStack_2268;
                    fStack_2104 = fStack_2264;
                    local_2100 = local_2260;
                    fStack_20fc = fStack_225c;
                    fStack_20f8 = fStack_2258;
                    fStack_20f4 = fStack_2254;
                    local_20f0 = local_2250;
                    fStack_20ec = fStack_224c;
                    fStack_20e8 = fStack_2248;
                    fStack_20e4 = fStack_2244;
                }
                local_21d0[5] = DAT_00e2eff4 / *(float *)(param_1 + 0x1c);
                local_21d0[0] = *(float *)(*(int *)(param_1 + 0x10) + 0xb0) * local_21d0[5];
                local_21d0[5] = *(float *)(*(int *)(param_1 + 0x10) + 0xb4) * local_21d0[5];
                local_21d0[1] = fStack_20ac;
                local_21d0[2] = fStack_20a8;
                local_21d0[3] = fStack_20a4;
                local_21d0[4] = fStack_20a4;
                local_21d0[6] = fStack_20a4;
                fStack_21b4 = fStack_20a4;
                local_21b0 = fStack_20a4;
                fStack_21ac = fStack_20a4;
                fStack_21a8 = fVar26;
                fStack_21a4 = fStack_20a4;
                local_21a0 = fStack_20a4;
                fStack_219c = fStack_20a4;
                fStack_2198 = fStack_20a4;
                fStack_2194 = fVar26;
                FUN_00417560();
                local_2110 = local_2270;
                fStack_210c = fStack_226c;
                fStack_2108 = fStack_2268;
                fStack_2108 = fStack_2268;
                fStack_2104 = fStack_2264;
                local_2100 = local_2260;
                fStack_20fc = fStack_225c;
                fStack_20f8 = fStack_2258;
                fStack_20f4 = fStack_2254;
                local_20f0 = local_2250;
                fStack_20ec = fStack_224c;
                fStack_20e8 = fStack_2248;
                fStack_20e4 = fStack_2244;
                fStack_20d8 = fStack_2238;
                fStack_20d4 = fStack_2234;
                local_20e0 = *(float *)(*(int *)(param_1 + 0x10) + 0xb0) * DAT_00e2cd54 +
                             *(float *)(param_1 + 0x20);
                iVar18 = *(int *)(param_1 + 0x454);
                fStack_20dc = *(float *)(*(int *)(param_1 + 0x10) + 0xb4) * DAT_00e2cd54 +
                              *(float *)(param_1 + 0x24);
                fVar26 = *(float *)(iVar18 + 0xa4) * DAT_00e44718;
                local_2050 = fVar26 * local_20c0 + local_2060;
                fStack_204c = fVar26 * fStack_20bc + fStack_205c;
                fStack_2048 = fVar26 * fStack_20b8 + fStack_2058;
                fStack_2044 = fVar26 * fStack_20b4 + fStack_2054;
                fVar26 = *(float *)(iVar18 + 0xa4);
                uVar20 = (uint)(int)*(short *)(iVar18 + 0x44) >> 2;
                fVar27 = SQRT(fVar26 * DAT_00e44718 * fVar26 * DAT_00e44718 + local_21d8 * local_21d8 +
                              local_2184 * local_2184);
                if (((uVar20 & 1) != 0) || (local_22ac = uVar20 & 1, (*(byte *)(param_1 + 0x460) & 1) == 0))
                {
                    local_22ac = 1;
                }
                local_2274 = CONCAT31(local_2274._1_3_,*(byte *)(param_1 + 0x460) >> 2) & 0xffffff01;
                piVar41 = &local_2278;
                puVar40 = local_268;
                uVar23 = (uint)(int)*(short *)(iVar18 + 0x44) >> 0xc & 0xffffff01;
                iVar22 = (int)pfVar25 + -0x4e;
                pfVar24 = &local_7f0;
                pfVar38 = local_1f78;
                uVar21 = CONCAT31((int3)((uVar20 & 0xffffff01) >> 8),(char)(uVar20 & 0xffffff01) == '\0');
                pfVar19 = pfVar25 + -0x14;
                pfVar37 = local_1ab0;
                dVar29 = (double)*(float *)(iVar18 + 0xa0);
                pfVar36 = &local_2180;
                pfVar35 = &local_2050;
                pfVar34 = &local_20c0;
                puVar33 = local_1fc0;
                uVar20 = local_22ac;
                uVar39 = local_2274;
                local_21e0 = fVar26;
                local_21dc = fVar27;
                FUN_00b99e20(fVar26,puVar33,pfVar34,pfVar35,fVar27,pfVar36,local_22ac,uVar21,pfVar37,pfVar19
                             ,pfVar38,pfVar24,iVar22,local_2274,uVar23,puVar40,piVar41);
                FUN_005208e0(&local_2110,(float)dVar29,fVar26,puVar33,pfVar34,pfVar35,fVar27,pfVar36,uVar20,
                             uVar21,pfVar37,pfVar19,pfVar38,pfVar24,iVar22,uVar39,uVar23,puVar40,piVar41);
                if ((char)local_2274 == '\0') {
                    FUN_0049f960(FUN_0049eb20,local_4d0);
                }
                else {
                    for (puVar2 = (undefined4 *)pfVar25[-0x13]; puVar2 != (undefined4 *)0x0;
                        puVar2 = (undefined4 *)puVar2[2]) {
                        (*(code *)local_4d0[0][1])(*puVar2,puVar2[1]);
                    }
                }
                fVar26 = DAT_00e2b1a4;
                if (*(short *)(pfVar25 + -0x14) != 0) {
                    local_1d18 = (int)*(short *)(pfVar25 + -0x14);
                    local_1d14 = (undefined1)local_22ac;
                    local_1d1c = local_1ab0;
                    local_1d0c = local_2278;
                    puStack_1d10 = local_268;
                    ppuStack_1d20 = &PTR_LAB_00e38378;
                    _memset(local_1d08,0,local_2278 * 4);
                    FUN_0049f960(FUN_0049ead0,&ppuStack_1d20);
                    FUN_005207a0();
                    sVar1 = *(short *)(pfVar25 + -0x14);
                    if (0 < sVar1) {
                        fStack_2288 = afStack_1aa0[1];
                        fStack_2280 = afStack_1aa0[1];
                        fVar26 = afStack_1aa0[0];
                        fVar27 = afStack_1aa0[0];
                        if (1 < sVar1) {
                            pfVar19 = afStack_1a90 + 5;
                            iVar18 = *(short *)(pfVar25 + -0x14) + -1;
                            do {
                                fVar28 = pfVar19[-1];
                                if (fVar28 <= fVar26) {
                                    fVar26 = fVar28;
                                }
                                fVar30 = *pfVar19;
                                if (fVar30 <= fStack_2280) {
                                    fStack_2280 = fVar30;
                                }
                                if (fVar27 < fVar28) {
                                    fVar27 = fVar28;
                                }
                                if (fStack_2288 < fVar30) {
                                    fStack_2288 = fVar30;
                                }
                                pfVar19 = pfVar19 + 8;
                                iVar18 = iVar18 + -1;
                            } while (iVar18 != 0);
                        }
                        if (local_2180 <= local_2160) {
                            fStack_22a4 = local_2180;
                            fVar28 = local_2160;
                        }
                        else {
                            fStack_22a4 = local_2160;
                            fVar28 = local_2180;
                        }
                        fVar31 = local_216c;
                        fVar30 = local_217c;
                        if (local_216c < local_217c) {
                            fVar31 = local_217c;
                            fVar30 = local_216c;
                        }
                        fVar32 = DAT_00e2b1a4;
                        if (DAT_00e44598 < fVar27 - fVar26) {
                            fVar32 = (fVar28 - fStack_22a4) / (fVar27 - fVar26);
                        }
                        fVar27 = DAT_00e2b1a4;
                        if (DAT_00e44598 < fStack_2288 - fStack_2280) {
                            fVar27 = (fVar31 - fVar30) / (fStack_2288 - fStack_2280);
                        }
                        if (0 < sVar1) {
                            iVar18 = (int)*(short *)(pfVar25 + -0x14);
                            pfVar19 = local_1ab0 + 5;
                            do {
                                pfVar19[-1] = (pfVar19[-1] - fVar26) * fVar32 + fStack_22a4;
                                *pfVar19 = (*pfVar19 - fStack_2280) * fVar27 + fVar30;
                                pfVar19 = pfVar19 + 8;
                                iVar18 = iVar18 + -1;
                            } while (iVar18 != 0);
                        }
                    }
                    fVar26 = DAT_00e2b1a4;
                    if ((*(byte *)(*(int *)(param_1 + 0x454) + 0x44) & 4) != 0) {
                        fStack_20d0 = pfVar25[4] * 0.0 + *pfVar25 * 0.0 + DAT_00e2b1a4 * pfVar25[8] +
                                      pfVar25[0xc] * 0.0;
                        fStack_20cc = pfVar25[5] * 0.0 + pfVar25[1] * 0.0 + DAT_00e2b1a4 * pfVar25[9] +
                                      pfVar25[0xd] * 0.0;
                        fStack_20c8 = pfVar25[6] * 0.0 + pfVar25[2] * 0.0 + DAT_00e2b1a4 * pfVar25[10] +
                                      pfVar25[0xe] * 0.0;
                        fStack_20c4 = pfVar25[7] * 0.0 + pfVar25[3] * 0.0 + DAT_00e2b1a4 * pfVar25[0xb] +
                                      pfVar25[0xf] * 0.0;
                        fVar28 = DAT_00e2b1a4 /
                                 SQRT(fStack_20d0 * fStack_20d0 + fStack_20cc * fStack_20cc +
                                      fStack_20c8 * fStack_20c8);
                        iVar22 = 3;
                        iVar18 = 0;
                        fVar27 = (local_1f78[2] + local_1f78[1] + local_1f78[0]) * DAT_00e44728;
                        if (3 < sVar1) {
                            do {
                                fVar30 = (local_1f78[iVar22] + local_1f78[iVar22 + 2] + local_1f78[iVar22 + 1]) *
                                         DAT_00e44728;
                                if (fVar30 < fVar27) {
                                    iVar18 = iVar22;
                                    fVar27 = fVar30;
                                }
                                iVar22 = iVar22 + 3;
                            } while (iVar22 < *(short *)(pfVar25 + -0x14));
                        }
                        local_1f78[iVar18] = fVar28 * local_1f78[iVar18];
                        local_1f78[iVar18 + 1] = fVar28 * local_1f78[iVar18 + 1];
                        local_1f78[iVar18 + 2] = fVar28 * local_1f78[iVar18 + 2];
                        FUN_00417560();
                        local_21d0[0] = local_1ab0[iVar18 * 8];
                        local_21d0[1] = local_1ab0[iVar18 * 8 + 1];
                        local_21d0[2] = local_1ab0[iVar18 * 8 + 2];
                        local_21d0[4] = afStack_1a90[iVar18 * 8];
                        local_21d0[5] = afStack_1a90[iVar18 * 8 + 1];
                        local_21b0 = afStack_1a90[iVar18 * 8 + 8];
                        local_21d0[6] = afStack_1a90[iVar18 * 8 + 2];
                        fStack_21ac = afStack_1a90[iVar18 * 8 + 9];
                        fStack_21a8 = afStack_1a90[iVar18 * 8 + 10];
                        FUN_0056b1a0();
                        fVar28 = (fStack_2258 - fStack_2248) * fStack_226c +
                                 (fStack_2248 - fStack_2268) * fStack_225c +
                                 (fStack_2268 - fStack_2258) * fStack_224c;
                        fVar30 = (local_2270 - local_2260) * fStack_2248 +
                                 (local_2260 - local_2250) * fStack_2268 +
                                 (local_2250 - local_2270) * fStack_2258;
                        fVar27 = (fStack_226c - fStack_225c) * local_2250 +
                                 (fStack_225c - fStack_224c) * local_2270 +
                                 (fStack_224c - fStack_226c) * local_2260;
                        fStack_21d4 = DAT_00e44564 -
                                      (fStack_2248 * fStack_225c - fStack_2258 * fStack_224c) * local_2270;
                        fVar32 = (fStack_21d4 -
                                 (fStack_2268 * fStack_224c - fStack_2248 * fStack_226c) * local_2260) -
                                 (fStack_2258 * fStack_226c - fStack_2268 * fStack_225c) * local_2250;
                        fVar31 = fVar26 / ((fVar30 + fVar28) * DAT_00e2b05c - fVar27 * fVar26);
                        local_2230[2] =
                             (DAT_00e44564 -
                             (local_2230[2] * fVar27 + local_2230[1] * fVar30 + local_2230[0] * fVar28 + fVar32)
                             * fVar31) * DAT_00e2eff4;
                        local_2230[6] =
                             (DAT_00e44564 -
                             (fVar27 * local_2230[6] + local_2230[5] * fVar30 + local_2230[4] * fVar28 + fVar32)
                             * fVar31) * DAT_00e2eff4;
                        local_2208 = (DAT_00e44564 -
                                     (fVar27 * local_2208 + fVar30 * local_220c + fVar28 * local_2210 + fVar32)
                                     * fVar31) * DAT_00e2eff4;
                        local_21f8 = (DAT_00e44564 -
                                     (fVar27 * local_21f8 + fVar30 * local_21fc + fVar28 * local_2200 + fVar32)
                                     * fVar31) * DAT_00e2eff4;
                        fVar28 = local_2230[6] - local_2230[2];
                        fVar27 = *(float *)(*(int *)(param_1 + 0x454) + 0xa8);
                        if ((fVar27 * fVar27 <
                             fVar28 * fVar28 + (local_2230[4] - local_2230[0]) * (local_2230[4] - local_2230[0])
                             + (local_2230[5] - local_2230[1]) * (local_2230[5] - local_2230[1])) ||
                           (fVar28 = local_2208 - local_2230[2],
                           fVar27 = *(float *)(*(int *)(param_1 + 0x454) + 0xa8),
                           fVar27 * fVar27 <
                           fVar28 * fVar28 + (local_2210 - local_2230[0]) * (local_2210 - local_2230[0]) +
                           (local_220c - local_2230[1]) * (local_220c - local_2230[1]))) {
                            *(undefined2 *)(pfVar25 + -0x14) = 0;
                            ppuStack_1d20 = &PTR_LAB_00e36530;
                            goto LAB_0052451e;
                        }
                        puVar2 = (undefined4 *)aiStack_1a98[iVar18 * 8];
                        local_20a0 = *puVar2;
                        uStack_209c = puVar2[1];
                        uStack_2098 = puVar2[2];
                        uStack_2094 = puVar2[3];
                        uStack_2090 = puVar2[4];
                        uStack_208c = puVar2[5];
                        uStack_2088 = puVar2[6];
                        uStack_2084 = puVar2[7];
                        uStack_2080 = puVar2[8];
                        uStack_207c = puVar2[9];
                        uStack_2078 = puVar2[10];
                        uStack_2074 = puVar2[0xb];
                        local_2070 = puVar2[0xc];
                        local_206c = puVar2[0xd];
                        local_2068 = puVar2[0xe];
                        local_2064 = (float)puVar2[0xf];
                        local_2270 = local_20b0;
                        fStack_226c = fStack_20ac;
                        fStack_2268 = fStack_20a8;
                        fStack_2264 = fStack_20a4;
                        local_2260 = fStack_20a4;
                        fStack_225c = local_20b0;
                        fStack_2258 = fStack_20a4;
                        fStack_2254 = fStack_20a4;
                        local_2250 = fStack_20a4;
                        fStack_224c = fStack_20a4;
                        fStack_2248 = local_20b0;
                        fStack_2244 = fStack_20a4;
                        local_2240 = fStack_20a4;
                        fStack_223c = fStack_20a4;
                        fStack_2238 = fStack_20a4;
                        fStack_2234 = local_20b0;
                        FUN_0056c3f0(&local_2270);
                        FUN_00417560();
                        fVar17 = fStack_2004;
                        fVar16 = fStack_2008;
                        fVar15 = fStack_200c;
                        fVar14 = fStack_2010;
                        fVar13 = fStack_2014;
                        fVar12 = fStack_2018;
                        fVar11 = fStack_201c;
                        fVar10 = fStack_2020;
                        fVar9 = fStack_2024;
                        fVar8 = fStack_2028;
                        fVar7 = fStack_202c;
                        fVar32 = fStack_2030;
                        fVar31 = fStack_2034;
                        fVar30 = fStack_2038;
                        fVar28 = fStack_203c;
                        fVar27 = fStack_2040;
                        iVar22 = 4;
                        pfVar19 = local_2230;
                        pfVar24 = local_21d0;
                        do {
                            fVar3 = *pfVar19;
                            fVar4 = pfVar19[1];
                            fVar5 = pfVar19[2];
                            fVar6 = pfVar19[3];
                            iVar22 = iVar22 + -1;
                            *pfVar24 = fVar4 * fVar32 + fVar3 * fVar27 + fVar5 * fVar10 + fVar6 * fVar14;
                            pfVar24[1] = fVar4 * fVar7 + fVar3 * fVar28 + fVar5 * fVar11 + fVar6 * fVar15;
                            pfVar24[2] = fVar4 * fVar8 + fVar3 * fVar30 + fVar5 * fVar12 + fVar6 * fVar16;
                            pfVar24[3] = fVar4 * fVar9 + fVar3 * fVar31 + fVar5 * fVar13 + fVar6 * fVar17;
                            pfVar19 = pfVar19 + 4;
                            pfVar24 = pfVar24 + 4;
                        } while (0 < iVar22);
                        local_1ab0[0] = local_21d0[0];
                        afStack_1aa0[0] = local_2180;
                        local_1ab0[1] = local_21d0[1];
                        local_1ab0[2] = local_21d0[2];
                        afStack_1aa0[1] = local_217c;
                        local_1ab0[3] = local_1ab0[iVar18 * 8 + 3];
                        afStack_1a90[0] = local_21d0[4];
                        afStack_1a90[1] = local_21d0[5];
                        afStack_1a90[2] = local_21d0[6];
                        afStack_1a80[0] = local_2170;
                        afStack_1a80[1] = local_216c;
                        afStack_1a80[4] = local_21b0;
                        fStack_1a6c = fStack_21ac;
                        fStack_1a68 = fStack_21a8;
                        fStack_1a60 = local_2160;
                        fStack_1a5c = local_215c;
                        fStack_1a30 = local_21a0;
                        uStack_1a54 = 0;
                        fStack_1a00 = local_2160;
                        fStack_19fc = local_215c;
                        uStack_19f8 = uStack_1a58;
                        uStack_19f4 = 0;
                        fStack_1a50 = local_21d0[4];
                        fStack_1a4c = local_21d0[5];
                        fStack_1a48 = local_21d0[6];
                        fStack_2120 = local_21d0[4] - local_21d0[0];
                        fStack_211c = local_21d0[5] - local_21d0[1];
                        fStack_2118 = local_21d0[6] - local_21d0[2];
                        fStack_1a2c = fStack_219c;
                        afStack_1a80[3] = 0.0;
                        fStack_1a40 = local_2170;
                        fStack_1a3c = local_216c;
                        uStack_1a38 = afStack_1a80[2];
                        fStack_1a28 = fStack_2198;
                        fStack_1a10 = local_21b0;
                        fStack_1a0c = fStack_21ac;
                        fStack_1a08 = fStack_21a8;
                        fStack_2130 = local_21b0 - local_21d0[0];
                        fStack_212c = fStack_21ac - local_21d0[1];
                        fStack_2128 = fStack_21a8 - local_21d0[2];
                        fStack_1a20 = local_2150;
                        fStack_1a1c = local_214c;
                        aiStack_1a98[1] = 0;
                        uStack_1a34 = 0;
                        iStack_1a18 = aiStack_1a98[0];
                        uStack_1a14 = 0;
                        local_7f0 = fStack_2128 * fStack_211c - fStack_212c * fStack_2118;
                        fStack_7ec = fStack_2130 * fStack_2118 - fStack_2128 * fStack_2120;
                        fStack_7e8 = fStack_212c * fStack_2120 - fStack_2130 * fStack_211c;
                        fVar27 = fStack_7e8 * fStack_7e8 + fStack_7ec * fStack_7ec + local_7f0 * local_7f0;
                        if (fVar27 <= DAT_00e2cbe0) {
                            fVar27 = 0.0;
                        }
                        else {
                            fVar27 = fVar26 / SQRT(fVar27);
                        }
                        local_7f0 = local_7f0 * fVar27;
                        fStack_7ec = fStack_7ec * fVar27;
                        fStack_7e8 = fStack_7e8 * fVar27;
                        uStack_7e4 = DAT_00e44634;
                        *(undefined2 *)(pfVar25 + -0x14) = 6;
                        afStack_1a90[3] = local_1ab0[3];
                        fStack_1a64 = local_1ab0[3];
                        fStack_1a44 = local_1ab0[3];
                        fStack_1a24 = local_1ab0[3];
                        fStack_1a04 = local_1ab0[3];
                    }
                    ppuStack_1d20 = &PTR_LAB_00e36530;
                }
LAB_0052451e:
                local_4d0[0] = &PTR_LAB_00e32a94;
            }
            pfVar25[-0x16] = 0.0;
            if (*(short *)(pfVar25 + -0x14) != 0) {
                _Dst = (void *)FUN_0051ec30(param_1);
                pfVar25[-0x16] = (float)_Dst;
                if (_Dst == (void *)0x0) {
                    *(undefined2 *)(pfVar25 + -0x14) = 0;
                    *(undefined2 *)((int)pfVar25 + -0x4e) = 0;
                    fVar26 = DAT_00e2b1a4;
                }
                else {
                    pfVar25[-0x15] = (float)((int)_Dst + *(short *)(pfVar25 + -0x14) * 0x20);
                    _memcpy(_Dst,local_1ab0,*(short *)(pfVar25 + -0x14) * 0x20);
                    _memcpy((void *)pfVar25[-0x15],&local_7f0,(int)*(short *)((int)pfVar25 + -0x4e) << 4);
                    fVar26 = DAT_00e2b1a4;
                }
            }
            local_22a8 = local_22a8 + *(short *)(pfVar25 + -0x14);
            local_2284 = local_2284 + 1;
            pfVar25 = pfVar25 + 0x28;
        } while (local_2284 < *(char *)(param_1 + 0x450));
    }
    return local_22a8 != 0;
}