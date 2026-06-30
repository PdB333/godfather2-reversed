// FUNC_NAME: BoneChain::updateAndRender
void __thiscall BoneChain::updateAndRender(int this, int unkParam)
{
    float *pfVar1;
    short sVar2;
    int iVar3;
    int iVar4;
    float fVar5;
    int iVar6;
    int iVar7;
    float *pfVar8;
    int iVar9;
    byte *pbVar10;
    float *pfVar11;
    float *extraout_EDX;
    int iVar12;
    undefined1 *puVar13;
    int iVar14;
    uint uVar15;
    int unaff_FS_OFFSET;
    byte bVar16;
    bool bVar17;
    float fVar18;
    float fVar19;
    float fVar20;
    float fVar21;
    double dVar22;
    float fVar23;
    float fVar24;
    float fVar25;
    float fVar26;
    float fVar27;
    float fVar28;
    int local_4d0;          // bone count
    float local_4cc;        // step for texture coordinates
    float local_4c8;        // cumulative texture coordinate
    float local_4c0;        // current texture coord
    float local_4bc;        // unused? set to 0
    float local_4b8;        // interpolated scale
    float local_4b4;        // interpolated width
    float local_4b0;        // direction vector component (normalized)
    float fStack_4ac;       // direction vector component
    float fStack_4a8;       // direction vector component
    int local_494;          // loop over items
    float local_478;        // thickness (scale * constant)
    undefined4 local_474;   // render flags
    float local_464;        // thickness (scale * constant)
    float local_460;        // start position x
    float fStack_45c;       // start position y
    float fStack_458;       // start position z
    float local_450;        // color r
    float fStack_44c;       // color g
    float fStack_448;       // color b
    float fStack_444;       // color a (1.0)
    float local_440;        // some float used for comparison
    undefined1 local_43c;   // flag
    uint local_434;         // flags: bit1 = interpolate scale
    float local_430;        // blend factor for direction
    float local_42c;        // max angle/limit for blend
    uint local_428;         // flags: bit0 = interpolate width
    float local_424;        // distance threshold
    float local_420;        // cross product component
    float fStack_41c;       // cross product component
    float fStack_418;       // cross product component
    float local_410;        // delta vector component
    float fStack_40c;       // delta vector component
    float fStack_408;       // delta vector component
    float local_400;        // target position x
    float fStack_3fc;       // target position y
    float fStack_3f8;       // target position z
    float fStack_3f4;       // target position w
    float local_3f0;        // vector difference component
    float fStack_3ec;       // vector difference component
    float fStack_3e8;       // vector difference component
    int local_3d8;          // current node id
    undefined1 local_3d0[16]; // matrix/transform
    float local_3c0;        // world position x
    float fStack_3bc;       // world position y
    float fStack_3b8;       // world position z
    undefined1 local_3b0[16]; // another matrix
    undefined4 local_3a0[4]; // 4x4 matrix (16 floats)
    undefined4 uStack_39c;
    undefined4 uStack_398;
    undefined4 uStack_394;
    undefined4 local_390;
    undefined4 uStack_38c;
    undefined4 uStack_388;
    undefined4 uStack_384;
    undefined4 local_380;
    undefined4 uStack_37c;
    undefined4 uStack_378;
    undefined4 uStack_374;
    undefined4 local_370;
    undefined4 uStack_36c;
    undefined4 uStack_368;
    undefined4 uStack_364;
    float afStack_35c[29];  // output scale/thickness
    float afStack_2e8[32];  // twist angles or colors
    float local_268[30];    // output thickness per bone
    float local_1f0[4];     // quaternion?
    undefined1 local_1e0[476]; // output vertex data

    // Get global scene/context pointer from thread local storage
    iVar3 = **(int **)(unaff_FS_OFFSET + 0x2c);
    // Start position from the object's offset 0x10 into the scene's vertex array (+0x80)
    pfVar8 = (float *)(*(int *)(iVar3 + 8) + 0x80 + *(int *)(this + 0x10));
    local_460 = *pfVar8;
    fStack_45c = pfVar8[1];
    fStack_458 = pfVar8[2];
    fVar5 = pfVar8[3];

    // Get item list from this+0x40 offset into scene
    iVar6 = *(int *)(iVar3 + 8) + *(int *)(this + 0x40);
    if ((*(int *)(iVar6 + 0xac) != 0) && (local_494 = 0, 0 < *(int *)(iVar6 + 0x58))) {
        do {
            iVar14 = *(int *)(iVar6 + 8 + local_494 * 8);
            if (iVar14 != 0) {
                iVar4 = *(int *)(iVar3 + 8);
                iVar9 = *(int *)(iVar4 + 0x24 + iVar14);
                if (iVar9 != 0) {
                    // Get parameter struct from this+0x3c
                    fVar21 = *(float *)(*(int *)(this + 0x3c) + 0x70);
                    // Transform start position by bone matrix (iVar9+0x80 4x4)
                    local_400 = fStack_45c * *(float *)(iVar9 + 0x90) +
                                local_460 * *(float *)(iVar9 + 0x80) +
                                fStack_458 * *(float *)(iVar9 + 0xa0) +
                                fVar5 * *(float *)(iVar9 + 0xb0);
                    fStack_3fc = fStack_45c * *(float *)(iVar9 + 0x94) +
                                 local_460 * *(float *)(iVar9 + 0x84) +
                                 fStack_458 * *(float *)(iVar9 + 0xa4) +
                                 fVar5 * *(float *)(iVar9 + 0xb4);
                    fStack_3f8 = fStack_45c * *(float *)(iVar9 + 0x98) +
                                 local_460 * *(float *)(iVar9 + 0x88) +
                                 fStack_458 * *(float *)(iVar9 + 0xa8) +
                                 fVar5 * *(float *)(iVar9 + 0xb8);
                    fStack_3f4 = fStack_45c * *(float *)(iVar9 + 0x9c) +
                                 local_460 * *(float *)(iVar9 + 0x8c) +
                                 fStack_458 * *(float *)(iVar9 + 0xac) +
                                 fVar5 * *(float *)(iVar9 + 0xbc);
                    local_3d8 = iVar14;

                    // If there is a world transform matrix (unkParam+0x40..0x7c)
                    if (DAT_00e2b05c < fVar21) {
                        local_3a0[0] = *(undefined4 *)(unkParam + 0x40);
                        uStack_39c = *(undefined4 *)(unkParam + 0x44);
                        uStack_398 = *(undefined4 *)(unkParam + 0x48);
                        uStack_394 = *(undefined4 *)(unkParam + 0x4c);
                        local_390 = *(undefined4 *)(unkParam + 0x50);
                        uStack_38c = *(undefined4 *)(unkParam + 0x54);
                        uStack_388 = *(undefined4 *)(unkParam + 0x58);
                        uStack_384 = *(undefined4 *)(unkParam + 0x5c);
                        local_380 = *(undefined4 *)(unkParam + 0x60);
                        uStack_37c = *(undefined4 *)(unkParam + 100);
                        uStack_378 = *(undefined4 *)(unkParam + 0x68);
                        uStack_374 = *(undefined4 *)(unkParam + 0x6c);
                        local_370 = *(undefined4 *)(unkParam + 0x70);
                        uStack_36c = *(undefined4 *)(unkParam + 0x74);
                        uStack_368 = *(undefined4 *)(unkParam + 0x78);
                        uStack_364 = *(undefined4 *)(unkParam + 0x7c);
                        // Transform bone matrix by world matrix (multiply?)
                        FUN_0056b420(iVar9 + 0x80, &local_370, &local_3c0);
                    }

                    // Get the bone chain data from scene arrays at +0x1c and +0x10 and +0x14
                    iVar9 = *(int *)(iVar4 + 0x1c + iVar14);
                    local_4d0 = *(int *)(iVar4 + 0x10 + iVar14);
                    if (iVar9 == 0) {
                        iVar14 = *(int *)(iVar4 + 0x14 + iVar14);
                        iVar9 = 0;
                        if (iVar14 != 0) {
                            iVar9 = iVar14 + iVar4;
                        }
                    }
                    if (iVar9 == 0) {
                        return;
                    }
                    // Cap bone count at 30
                    if (0x1e < local_4d0) {
                        local_4d0 = 0x1e;
                    }

                    // Get initial radius/scale from this+0x40's keyframe arrays (interpolation?)
                    local_4b4 = *(float *)(*(int *)(this + 0x40) + 0x5c + iVar4); // width keyframes
                    local_4b8 = *(float *)(*(int *)(this + 0x40) + 0x84 + iVar4); // scale keyframes
                    local_478 = local_4b8 * DAT_00e35654; // convert to thickness
                    iVar14 = 0;
                    local_464 = local_4b8 * DAT_00e2b198; // another thickness constant

                    if (0 < local_4d0) {
                        iVar12 = *(int *)(this + 0x3c);
                        local_430 = *(float *)(iVar12 + 0x74); // blend factor
                        local_428 = *(uint *)(iVar12 + 0x50) & 1; // interpolate width flag
                        local_42c = *(float *)(this + 0x48); // angle/limit
                        local_434 = *(uint *)(iVar12 + 0x50) & 2; // interpolate scale flag
                        local_424 = *(float *)(iVar12 + 0x5c); // distance threshold for thickness

                        pfVar8 = local_1f0 + 3; // points to local_1f0[3] (quaternion w?)
                        pfVar11 = (float *)(iVar9 + 0x10); // bone positions array

                        do {
                            fVar23 = (float)iVar14 / (float)(local_4d0 + -1);
                            // Interpolate width if flag set
                            if (local_428 != 0) {
                                iVar12 = iVar4 + 0x5c + *(int *)(this + 0x40);
                                if (fVar23 == DAT_00e2b1a4) {
                                    local_4b4 = *(float *)(iVar12 + 0x24);
                                }
                                else {
                                    iVar7 = (int)(fVar23 * _DAT_01128680);
                                    local_4b4 = *(float *)(iVar12 + iVar7 * 4);
                                    local_4b4 = (*(float *)(iVar12 + 4 + iVar7 * 4) - local_4b4) *
                                                (fVar23 * _DAT_01128680 - (float)iVar7) + local_4b4;
                                }
                            }
                            // Interpolate scale if flag set
                            if (local_434 != 0) {
                                iVar12 = iVar4 + 0x84 + *(int *)(this + 0x40);
                                if (fVar23 == DAT_00e2b1a4) {
                                    local_4b8 = *(float *)(iVar12 + 0x24);
                                }
                                else {
                                    iVar7 = (int)(fVar23 * _DAT_01128680);
                                    local_4b8 = *(float *)(iVar12 + iVar7 * 4);
                                    local_4b8 = (*(float *)(iVar12 + 4 + iVar7 * 4) - local_4b8) *
                                                (fVar23 * _DAT_01128680 - (float)iVar7) + local_4b8;
                                }
                                local_478 = local_4b8 * DAT_00e35654;
                                local_464 = local_4b8 * DAT_00e2b198;
                            }

                            // Get bone position (source point)
                            fVar23 = pfVar11[-4]; // x
                            fVar27 = pfVar11[-3]; // y
                            fVar28 = pfVar11[-2]; // z
                            fVar26 = pfVar11[-1]; // w?
                            // Compute delta from target position
                            local_410 = fVar23 - local_400;
                            fStack_40c = fVar27 - fStack_3fc;
                            fStack_408 = fVar28 - fStack_3f8;
                            // Squared distance
                            fVar18 = fStack_408 * fStack_408 + fStack_40c * fStack_40c + local_410 * local_410;
                            // Normalize if not zero
                            if (fVar18 <= DAT_00e2cbe0) {
                                fStack_4a8 = 0.0;
                                fVar18 = 0.0;
                            }
                            else {
                                fVar18 = SQRT(fVar18);
                                fStack_4a8 = DAT_00e2b1a4 / fVar18;
                            }
                            // Direction components
                            fStack_4ac = fStack_40c * fStack_4a8;
                            local_4b0 = local_410 * fStack_4a8;
                            fStack_4a8 = fStack_408 * fStack_4a8;

                            // Compute angle between current direction and target direction
                            fVar24 = DAT_00e44564 -
                                     (pfVar11[2] * fStack_4a8 + fStack_4ac * pfVar11[1] + *pfVar11 * local_4b0);

                            fVar25 = DAT_00e2b1a4; // 1.0
                            fVar20 = local_4b8;
                            // Blend direction based on local_430 (blend factor)
                            if (local_430 != DAT_00e2b05c) {
                                if (local_430 == DAT_00e2b1a4) {
                                    // If blend factor is 1.0, call something (maybe function call to normalize?)
                                    FUN_00414aa0();
                                    pfVar11 = extraout_EDX; // likely updated pointer
                                }
                                else {
                                    // Linear blend between current bone direction and target direction
                                    fVar19 = DAT_00e2b1a4 - local_430;
                                    local_4b0 = local_430 * *pfVar11 + fVar19 * local_4b0;
                                    fStack_4ac = local_430 * pfVar11[1] + fVar19 * fStack_4ac;
                                    fStack_4a8 = local_430 * pfVar11[2] + fVar19 * fStack_4a8;
                                    // Renormalize
                                    fVar19 = fStack_4a8 * fStack_4a8 + fStack_4ac * fStack_4ac + local_4b0 * local_4b0;
                                    if (fVar19 <= DAT_00e2cbe0) {
                                        fVar19 = 0.0;
                                    }
                                    else {
                                        fVar19 = DAT_00e2b1a4 / SQRT(fVar19);
                                    }
                                    local_4b0 = fVar19 * local_4b0;
                                    fStack_4ac = fStack_4ac * fVar19;
                                    fStack_4a8 = fStack_4a8 * fVar19;
                                }
                            }
                            // Compute angle fade factor based on local_42c (max angle)
                            fVar19 = fVar25;
                            if (local_42c != fVar25) {
                                if (fVar24 <= local_42c) {
                                    fVar19 = 0.0;
                                }
                                else {
                                    fVar19 = (fVar24 - *(float *)(this + 0x48)) /
                                             (fVar25 - *(float *)(this + 0x48));
                                }
                            }

                            pfVar1 = local_268 + iVar14;
                            // Compute thickness based on distance
                            if (fVar18 <= local_424) {
                                iVar12 = *(int *)(this + 0x3c);
                                if (*(float *)(iVar12 + 0x58) <= fVar18) {
                                    // Within range, interpolate thickness
                                    fVar20 = fVar25 - (fVar18 - *(float *)(iVar12 + 0x58)) /
                                                      (*(float *)(iVar12 + 0x5c) - *(float *)(iVar12 + 0x58));
                                    *pfVar1 = fVar20 * local_464 + local_478;
                                    fVar18 = *(float *)(iVar12 + 0x60);
                                    if (*(float *)(iVar12 + 0x60) <= fVar20) {
                                        afStack_35c[iVar14 + 1] =
                                            (fVar25 - (fVar20 - fVar18) / (fVar25 - fVar18)) * fVar19 * local_4b4;
                                    }
                                    else {
                                        afStack_35c[iVar14 + 1] =
                                            (fVar25 - (fVar18 - fVar20) / fVar18) * fVar19 * local_4b4;
                                    }
                                }
                                else {
                                    // Too close, zero thickness
                                    *pfVar1 = fVar20;
                                    afStack_35c[iVar14 + 1] = 0.0;
                                }
                            }
                            else {
                                // Outside range, use constant thickness and zero twist
                                *pfVar1 = local_478;
                                afStack_35c[iVar14 + 1] = 0.0;
                            }

                            // Store computed position (output)
                            fVar18 = *pfVar1;
                            fVar25 = *pfVar8;
                            pfVar8[-3] = fVar18 * local_4b0 + fVar23;
                            pfVar8[-2] = fVar18 * fStack_4ac + fVar27;
                            pfVar8[-1] = fVar18 * fStack_4a8 + fVar28;
                            *pfVar8 = fVar18 * fStack_4a4 + fVar26; // note: fStack_4a4 undefined? likely meaning pfVar11[3]?
                            *pfVar8 = fVar25; // restore original? might be a mistake

                            // Compute twist/tilt if there is a world transform and not last bone
                            if ((0.0 < fVar21) && (iVar14 < local_4d0 + -1)) {
                                if (*(char *)((int)pfVar11 + 0x1f) == '\x02') {
                                    // Vector from start to end of bone
                                    local_460 = fVar23 - local_3c0;
                                    fStack_45c = fVar27 - fStack_3bc;
                                    fStack_458 = fVar28 - fStack_3b8;
                                    fVar26 = fStack_458 * fStack_458 + fStack_45c * fStack_45c + local_460 * local_460;
                                    if (fVar26 <= DAT_00e2cbe0) {
                                        fVar26 = 0.0;
                                    }
                                    else {
                                        fVar26 = DAT_00e2b1a4 / SQRT(fVar26);
                                    }
                                    local_460 = local_460 * fVar26;
                                    fStack_45c = fStack_45c * fVar26;
                                    fStack_458 = fStack_458 * fVar26;
                                    // Cross product of bone direction and global up
                                    local_3f0 = fVar23 - pfVar11[4];
                                    fStack_3ec = fVar27 - pfVar11[5];
                                    fStack_3e8 = fVar28 - pfVar11[6];
                                    local_420 = fStack_3ec * fStack_4a8 - fStack_3e8 * fStack_4ac;
                                    fStack_41c = fStack_3e8 * local_4b0 - local_3f0 * fStack_4a8;
                                    fStack_418 = local_3f0 * fStack_4ac - fStack_3ec * local_4b0;
                                    fVar23 = fStack_418 * fStack_418 + fStack_41c * fStack_41c + local_420 * local_420;
                                    if (fVar23 <= DAT_00e2cbe0) {
                                        fVar23 = 0.0;
                                    }
                                    else {
                                        fVar23 = DAT_00e2b1a4 / SQRT(fVar23);
                                    }
                                    // Store twisted angle (as float)
                                    afStack_2e8[iVar14 + 2] =
                                        (float)((uint)(fStack_418 * fVar23 * fStack_458 +
                                                       fStack_41c * fVar23 * fStack_45c +
                                                       local_420 * fVar23 * local_460) & DAT_00e44680);
                                }
                                else {
                                    // Copy previous twist
                                    afStack_2e8[iVar14 + 2] = afStack_2e8[iVar14 + 1];
                                }
                            }

                            iVar14 = iVar14 + 1;
                            pfVar8 = pfVar8 + 4; // advance output pointer
                            pfVar11 = pfVar11 + 8; // advance bone data pointer (stride 8 floats)
                        } while (iVar14 < local_4d0);
                    }

                    // Post-process twist based on some global timing
                    if (DAT_00e2b05c < fVar21) {
                        dVar22 = (double)(DAT_00e2a850 - fVar21 * DAT_00e445c8);
                        FUN_00b99e20(); // likely some math function
                        iVar14 = 0;
                        afStack_2e8[local_4d0 + 1] = afStack_2e8[local_4d0];
                        fVar21 = afStack_2e8[3];
                        if (0 < local_4d0) {
                            do {
                                fVar23 = afStack_2e8[iVar14 + 2];
                                bVar16 = 0;
                                if (iVar14 == 0) {
                                    if (*(char *)(iVar9 + 0x2f) != '\x02') goto LAB_004fb840;
                                    bVar16 = 1;
                                    fVar27 = fVar21;
LAB_004fb839:
                                    fVar23 = fVar27 + fVar23;
                                }
                                else if (iVar14 == local_4d0 + -1) {
                                    if (*(char *)(iVar14 * 0x20 + 0xf + iVar9) == '\x02') {
                                        bVar16 = 1;
LAB_004fb830:
                                        fVar27 = afStack_2e8[iVar14 + 1];
                                        goto LAB_004fb839;
                                    }
                                }
                                else {
                                    iVar12 = iVar14 * 0x20 + iVar9;
                                    bVar16 = *(char *)(iVar12 + 0x2f) == '\x02';
                                    if ((bool)bVar16) {
                                        fVar23 = afStack_2e8[iVar14 + 3] + fVar23;
                                    }
                                    if (*(char *)(iVar12 + 0xf) == '\x02') {
                                        bVar16 = bVar16 + 1;
                                        goto LAB_004fb830;
                                    }
                                }
LAB_004fb840:
                                if (fVar23 / (float)bVar16 < (float)dVar22) {
                                    // Scale down twist if below threshold
                                    afStack_35c[iVar14 + 1] =
                                        (fVar23 / (float)bVar16) * (DAT_00e2b1a4 / (float)dVar22) *
                                        afStack_35c[iVar14 + 1];
                                }
                                iVar14 = iVar14 + 1;
                            } while (iVar14 < local_4d0);
                        }
                    }

                    // Set render flags and call rendering subroutines
                    bVar17 = *(int *)(iVar4 + 0xb0 + *(int *)(this + 0x40)) != 0; // has texture?
                    FUN_005334b0(&local_440,
                                 (*(uint *)(*(int *)(this + 0x3c) + 0x50) & 0x80) * 2 |
                                 (-(uint)(*(int *)(iVar4 + *(int *)(this + 0x40) + 0xac) != 0) & 0xffffffc0) + 0x40 |
                                 -(uint)bVar17 & 2);
                    FUN_00534ff0(*(undefined4 *)(*(int *)(iVar3 + 8) + *(int *)(this + 0x40) + 0xb0));

                    if ((*(byte *)(*(int *)(this + 0x3c) + 0x50) & 0x80) != 0) {
                        _DAT_01219b30 = FUN_00535640(local_3d0, local_3b0);
                        if ((*(int *)(&DAT_01219d44 + (uint)DAT_01219b21 * 0x3c) != 0) &&
                            (*(int *)(&DAT_01219d50 + (uint)DAT_01219b21 * 0x3c) != 0)) {
                            FUN_006063b0();
                        }
                        FUN_00534e20(local_3b0);
                    }

                    if (*(undefined **)(*(int *)(iVar3 + 8) + 0x24 + local_3d8) != &UNK_00e2cb60) {
                        FUN_00417560(); // some render call
                    }

                    FUN_00535220(); // draw call

                    // Determine if we should use "local_474" (1 or 0)
                    if (((*(uint *)(*(int *)(iVar3 + 8) + *(int *)(this + 0x10)) & 0x200) == 0) ||
                        (local_474 = 1, *(int *)(DAT_012234c4 + 0x24) == 0)) {
                        local_474 = 0;
                    }

                    FUN_00535450(local_474, local_440);

                    // Set up color from parameter struct
                    iVar14 = *(int *)(this + 0x3c);
                    local_450 = *(float *)(iVar14 + 100); // red
                    fStack_44c = *(float *)(iVar14 + 0x68); // green
                    fStack_448 = *(float *)(iVar14 + 0x6c); // blue
                    local_43c = 1; // alpha flag?
                    if ((*(uint *)(*(int *)(iVar3 + 8) + *(int *)(this + 0x10)) & 0x80000) != 0) {
                        iVar14 = *(int *)(this + 4);
                        local_450 = *(float *)(iVar14 + 0xa0) * local_450;
                        fStack_44c = *(float *)(iVar14 + 0xa4) * fStack_44c;
                        fStack_448 = *(float *)(iVar14 + 0xa8) * fStack_448;
                    }
                    fStack_444 = DAT_00e2b1a4; // alpha = 1.0

                    // Set global shader constants
                    _DAT_01219b40 = local_450;
                    _DAT_01219b44 = fStack_44c;
                    _DAT_01219b48 = fStack_448;
                    _DAT_01219b4c = DAT_00e2b1a4;

                    if ((DAT_012058e8 == &DAT_01219a70) &&
                        (*(int *)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30) != 0)) {
                        FUN_0060add0(DAT_01219a80, *(int *)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30), &local_450);
                    }

                    // Set global state for rendering
                    if (DAT_012058d0 < 0xe) {
                        DAT_012058d0 = 0xe;
                    }
                    if (0xe < DAT_00f15988) {
                        DAT_00f15988 = 0xe;
                    }
                    _DAT_011f3a10 = 0;
                    if (DAT_012058d0 < 7) {
                        DAT_012058d0 = 7;
                    }
                    if (7 < DAT_00f15988) {
                        DAT_00f15988 = 7;
                    }
                    _DAT_011f39f4 = (uint)(~(byte)(*(uint *)(*(int *)(this + 0x3c) + 0x50) >> 3) & 1);
                    uVar15 = *(uint *)(*(int *)(this + 0x3c) + 0x50) >> 4 & 1;
                    if (DAT_012058d0 < 0x1b) {
                        DAT_012058d0 = 0x1b;
                    }
                    if (0x1a < DAT_00f15988) {
                        DAT_00f15988 = 0x1b;
                    }
                    _DAT_011f3a44 = (uint)(uVar15 != 3);
                    FUN_004ec7a0(); // some state setup
                    local_440 = DAT_00e2b1a4;
                    if (uVar15 == 1) {
                        local_440 = 0.0;
                    }
                    FUN_004eccc0(8); // texture coordinate generation?

                    // Now handle per-bone texture coordinate offsets
                    local_4c0 = *(float *)(this + 0x164); // initial texture coord
                    sVar2 = *(short *)(*(int *)(this + 0x3c) + 0x40);
                    local_4bc = 0.0;
                    if (sVar2 < 1) {
                        local_4cc = DAT_00e2b1a4;
                        local_4c8 = DAT_00e2b1a4;
                    }
                    else {
                        local_4cc = DAT_00e2b1a4 / (float)(int)(*(byte *)(iVar9 + 0xe) - 1);
                        local_4c8 = (float)(int)sVar2 * local_4cc;
                    }

                    iVar14 = 1;
                    if (1 < local_4d0) {
                        pbVar10 = (byte *)(iVar9 + 0x2e);
                        puVar13 = local_1e0;
                        fVar21 = DAT_00e2b1a4;
                        do {
                            pfVar8 = (float *)(pbVar10 + -0x2e);
                            if (pbVar10[1] == 2) {
                                if ((*(byte *)(*(int *)(this + 0x3c) + 0x50) & 4) == 0) {
                                    // Use computed bone positions
                                    pfVar11 = (float *)(pbVar10 + -0xe);
                                    fVar21 = afStack_35c[iVar14 + 1];
                                    fVar23 = afStack_35c[iVar14];
                                }
                                else {
                                    // Use target positions
                                    pfVar8 = &local_400;
                                    fVar21 = afStack_35c[iVar14 + 1];
                                    fVar23 = afStack_35c[iVar14];
                                    pfVar11 = pfVar8;
                                }
                                // Call rendering for this bone (maybe generate geometry)
                                FUN_004fab60(pfVar8, puVar13 + -0x10, pfVar11, fVar23, fVar21,
                                             local_4c0, local_4c8, local_4bc, local_4cc, bVar17);
                                // Advance texture coordinates
                                local_4c0 = local_4c8 + local_4c0;
                                local_4bc = local_4cc + local_4bc;
                                // Update some state (this+0x50)
                                FUN_004faa80(this + 0x50);
                                fVar21 = DAT_00e2b1a4;
                            }
                            else {
                                // Reset texture coordinates for non-rendered bones
                                local_4c0 = *(float *)(this + 0x164);
                                local_4bc = 0.0;
                                local_4cc = fVar21;
                                local_4c8 = fVar21;
                                if ((1 < *pbVar10) &&
                                    (sVar2 = *(short *)(*(int *)(this + 0x3c) + 0x40), 0 < sVar2)) {
                                    local_4cc = fVar21 / (float)(int)(*pbVar10 - 1);
                                    local_4c8 = (float)(int)sVar2 * local_4cc;
                                }
                            }
                            iVar14 = iVar14 + 1;
                            pbVar10 = pbVar10 + 0x20;
                            puVar13 = puVar13 + 0x10;
                        } while (iVar14 < local_4d0);
                    }

                    FUN_00533720(&local_440); // finish rendering
                }
            }
            local_494 = local_494 + 1;
        } while (local_494 < *(int *)(iVar6 + 0x58));
    }
    return;
}