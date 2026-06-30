// FUNC_NAME: RibbonEffect::Update
void __thiscall RibbonEffect::Update(int thisPtr, int param2)
{
    byte bVar1;
    float* pfVar2;
    float* pfVar3;
    float* pfVar4;
    ushort flags;
    int iVar6;
    int iVar7;
    ushort uVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    uint uVar16;
    float* pfVar17;
    uint uVar18;
    int unaff_FS_OFFSET;
    float fVar19;
    float fVar20;
    float fVar21;
    float fVar22;
    float fVar23;
    float fVar24;
    float fVar25;
    float fVar26;
    float fVar27;
    float local_ec;
    float local_e8;
    float local_e4;
    float local_e0;
    float fStack_dc;
    float fStack_d8;
    float fStack_d4;
    float local_d0;
    float fStack_cc;
    float fStack_c8;
    float fStack_c4;
    float local_c0;
    float fStack_bc;
    float fStack_b8;
    float fStack_b4;
    float local_b0;
    uint local_ac;
    float local_a8;
    float local_a4;
    float local_a0;
    float local_9c;
    float local_98;
    float local_94;
    float local_90;
    float local_8c;
    float local_88;
    float local_84;
    float local_80;
    float local_7c;
    float local_78;
    float local_74;
    float local_70;
    float fStack_6c;
    float fStack_68;
    float fStack_64;
    float local_54;
    float local_50;
    float fStack_4c;
    float fStack_48;
    float fStack_44;
    float local_40;
    float fStack_3c;
    float fStack_38;
    float fStack_34;
    float local_30;
    float fStack_2c;
    float fStack_28;
    float fStack_24;
    float local_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;

    local_ac = **(uint**)(unaff_FS_OFFSET + 0x2c);
    iVar6 = *(int*)(local_ac + 8);
    pfVar17 = (float*)(*(int*)(thisPtr + 0x24) + iVar6); // vertex array base + thread offset

    // early exit if scale factor is zero
    if (pfVar17[4] == 0.0f) {
        return;
    }

    iVar7 = *(int*)(thisPtr + 0x2c); // pointer to config
    // read six values (maybe quaternion or matrix row)
    fVar19 = *(float*)(iVar7 + 0x48);
    fVar20 = *(float*)(iVar7 + 0x4c);
    fVar21 = *(float*)(iVar7 + 0x50);
    fVar22 = *(float*)(iVar7 + 0x54);
    fVar23 = *(float*)(iVar7 + 0x58);
    fVar24 = *(float*)(iVar7 + 0x5c);
    local_94 = *(float*)(iVar7 + 0x30); // maybe tileU
    local_9c = *(float*)(iVar7 + 0x34); // maybe tileV

    iVar7 = *(int*)(thisPtr + 0x10); // vertex offset
    pfVar2 = (float*)(iVar6 + 0x60 + iVar7); // source positions?
    pfVar3 = (float*)(iVar6 + 0x50 + iVar7);
    pfVar4 = (float*)(iVar6 + 0x50 + iVar7);
    iVar7 = iVar6 + 0x50 + iVar7;

    // transform quaternion/matrix multiplication
    local_40 = fVar20 * *pfVar2 + fVar19 * *pfVar3 + fVar21 * *(float*)(iVar7 + 0x20) + DAT_00e2b1a4 * *(float*)(iVar7 + 0x30);
    fStack_3c = fVar20 * pfVar2[1] + fVar19 * pfVar3[1] + fVar21 * *(float*)(iVar7 + 0x24) + DAT_00e2b1a4 * *(float*)(iVar7 + 0x34);
    fStack_38 = fVar20 * pfVar2[2] + fVar19 * pfVar3[2] + fVar21 * *(float*)(iVar7 + 0x28) + DAT_00e2b1a4 * *(float*)(iVar7 + 0x38);
    fStack_34 = fVar20 * pfVar2[3] + fVar19 * pfVar3[3] + fVar21 * *(float*)(iVar7 + 0x2c) + DAT_00e2b1a4 * *(float*)(iVar7 + 0x3c);

    local_50 = fVar23 * *(float*)(iVar7 + 0x10) + fVar22 * *pfVar4 + fVar24 * *(float*)(iVar7 + 0x20) + DAT_00e2b1a4 * *(float*)(iVar7 + 0x30);
    fStack_4c = fVar23 * *(float*)(iVar7 + 0x14) + fVar22 * pfVar4[1] + fVar24 * *(float*)(iVar7 + 0x24) + DAT_00e2b1a4 * *(float*)(iVar7 + 0x34);
    fStack_48 = fVar23 * *(float*)(iVar7 + 0x18) + fVar22 * pfVar4[2] + fVar24 * *(float*)(iVar7 + 0x28) + DAT_00e2b1a4 * *(float*)(iVar7 + 0x38);
    fStack_44 = fVar23 * *(float*)(iVar7 + 0x1c) + fVar22 * pfVar4[3] + fVar24 * *(float*)(iVar7 + 0x2c) + DAT_00e2b1a4 * *(float*)(iVar7 + 0x3c);

    // compute differences from param2 (target position?)
    fVar23 = local_40 - *(float*)(param2 + 0x70);
    fVar24 = fStack_3c - *(float*)(param2 + 0x74);
    fVar25 = fStack_38 - *(float*)(param2 + 0x78);
    fVar26 = fStack_34 - *(float*)(param2 + 0x7c);
    fVar19 = local_50 - *(float*)(param2 + 0x70);
    fVar20 = fStack_4c - *(float*)(param2 + 0x74);
    fVar21 = fStack_48 - *(float*)(param2 + 0x78);
    fVar22 = fStack_44 - *(float*)(param2 + 0x7c);

    // cross product
    fVar27 = fVar21 * fVar24 - fVar20 * fVar25;
    fVar21 = fVar19 * fVar25 - fVar21 * fVar23;
    fVar19 = fVar20 * fVar23 - fVar19 * fVar24;
    fStack_24 = fVar22 * fVar26 - fVar22 * fVar26; // this should be zero? maybe a bug

    local_e8 = fVar19 * fVar19 + fVar21 * fVar21 + fVar27 * fVar27;
    if (local_e8 <= DAT_00e2cbe0) {
        fVar20 = 0.0f;
        local_e8 = 0.0f;
    } else {
        local_e8 = SQRT(local_e8);
        fVar20 = DAT_00e2b1a4 / local_e8; // normalize
    }

    if (local_e8 <= (float)PTR_FUN_00e4462c) {
        return;
    }

    iVar6 = *(int*)(thisPtr + 0x2c);
    flags = *(ushort*)(iVar6 + 0x20);

    // scale cross product by tile factors
    local_20 = local_94 * fVar27 * fVar20;
    fStack_1c = local_94 * fVar21 * fVar20;
    fStack_18 = local_94 * fVar19 * fVar20;
    fStack_14 = local_94 * fStack_24; // should be 0
    local_30 = local_9c * fVar27 * fVar20;
    fStack_2c = local_9c * fVar21 * fVar20;
    fStack_28 = local_9c * fVar19 * fVar20;
    fStack_24 = local_9c * fStack_24;

    // compute direction vector between two transformed positions
    local_e0 = local_50 - local_40;
    fStack_dc = fStack_4c - fStack_3c;
    fStack_d8 = fStack_48 - fStack_38;
    fStack_d4 = fStack_44 - fStack_34;

    local_54 = pfVar17[1]; // some parameter, maybe "alpha" or "width"
    if ((flags & 0x40) != 0) {
        fVar19 = fVar25 * fStack_d8 + fVar24 * fStack_dc + fVar23 * local_e0;
        fVar19 = (fVar19 * fVar19) /
                 ((fVar24 * fVar24 + fVar25 * fVar25 + fVar23 * fVar23) *
                  (fStack_d8 * fStack_d8 + fStack_dc * fStack_dc + local_e0 * local_e0) +
                  (float)PTR_FUN_00e4462c);
        local_54 = ((DAT_00e2b1a4 - fVar19 * fVar19 * fVar19 * fVar19) * *(float*)(iVar6 + 0x6c) +
                   (DAT_00e2b1a4 - fVar19) * (DAT_00e2b1a4 - *(float*)(iVar6 + 0x6c))) * local_54;
        local_70 = fVar23;
        fStack_6c = fVar24;
        fStack_68 = fVar25;
        fStack_64 = fVar26;
    }

    if (local_54 <= DAT_00e2af44) {
        return;
    }

    fStack_c4 = fStack_d4;
    local_d0 = local_e0;
    fStack_cc = fStack_dc;
    fStack_c8 = fStack_d8;

    if ((flags & 1) == 0) {
        // non-separate UV calculation
        (&local_e0)[*(char*)(iVar6 + 0x23)] = DAT_00e2e210; // set one component?
        FUN_0044d680(&local_e0, &local_e0); // some math function
        bVar1 = *(char*)(iVar6 + 0x23) * '\x04';
        uVar16 = (0x102 >> (bVar1 & 0x1f)) & 0xf;
        fVar19 = (&local_e0)[uVar16];
        uVar18 = (0x21 >> (bVar1 & 0x1f)) & 0xf;
        fVar20 = (&local_e0)[uVar18];
        local_80 = fVar19;
        local_74 = fVar20;
        if ((*(byte*)(iVar6 + 0x20) & 4) == 0) {
            local_80 = DAT_00e44564 - fVar20;
            local_74 = fVar19;
        }
        local_7c = *(float*)(*(int*)(thisPtr + 0x24) + *(int*)(local_ac + 8)) * *(float*)(iVar6 + 100);
        local_78 = local_7c * local_80;
        local_7c = local_7c * local_74;
        local_78 = local_78 - (float)(int)local_78; // fractional part
        local_7c = local_7c - (float)(int)local_7c;
        if ((*(byte*)(iVar6 + 0x20) & 8) == 0) {
            local_e0 = local_d0;
            fStack_dc = fStack_cc;
            fStack_d8 = fStack_c8;
            fStack_d4 = fStack_c4;
        }
        local_a4 = (&local_e0)[uVar16] + local_80;
        local_9c = *(float*)(iVar6 + 0x68) * (&local_e0)[uVar16] + local_78;
        local_b0 = (&local_e0)[uVar18] + local_74;
        local_94 = *(float*)(iVar6 + 0x68) * (&local_e0)[uVar18] + local_7c;
        if ((*(byte*)(iVar6 + 0x20) & 2) == 0) {
            local_a0 = 0.0f;
            local_8c = 0.0f;
            local_e4 = 0.0f;
            local_a8 = 0.0f;
            goto LAB_004f6733;
        }
        fVar19 = fVar19 * DAT_00e2b04c;
        fVar20 = fVar20 * DAT_00e2b04c;
        fVar21 = *(float*)(iVar6 + 0x30);
        local_a8 = DAT_00e44564 - fVar21 * fVar20;
        local_90 = fVar21 * fVar19;
        local_84 = *(float*)(iVar6 + 0x34);
        local_e4 = DAT_00e44564 - local_84 * fVar20;
        local_98 = local_84 * fVar19;
        fVar19 = *(float*)(iVar6 + 0x68) * fVar19;
        fVar20 = *(float*)(iVar6 + 0x68) * fVar20;
        local_88 = fVar21 * fVar19;
        local_8c = DAT_00e44564 - fVar21 * fVar20;
        local_a0 = DAT_00e44564 - local_84 * fVar20;
        local_84 = local_84 * fVar19;
    } else {
        // separate UV calculation
        if ((flags & 4) == 0) {
            local_9c = *(float*)(iVar6 + 100) * *pfVar17 + DAT_00e2cd54;
            local_7c = 0.0f;
        } else {
            local_7c = *(float*)(iVar6 + 100) * *pfVar17;
            local_9c = DAT_00e2cd54;
        }
        local_9c = local_9c - (float)(int)local_9c;
        local_7c = local_7c - (float)(int)local_7c;
        if ((flags & 0x100) == 0) {
            if (*(float*)(iVar6 + 0x30) < *(float*)(iVar6 + 0x34) ||
                *(float*)(iVar6 + 0x30) == *(float*)(iVar6 + 0x34)) {
                fVar19 = *(float*)(iVar6 + 0x34);
            } else {
                fVar19 = *(float*)(iVar6 + 0x30);
            }
            local_e4 = *(float*)(iVar6 + 0x34) * (DAT_00e2cd54 / fVar19);
            local_a8 = *(float*)(iVar6 + 0x30) * (DAT_00e2cd54 / fVar19);
        } else {
            local_e4 = DAT_00e2cd54;
            local_a8 = DAT_00e2cd54;
        }
        local_94 = *(float*)(iVar6 + 0x68);
        local_8c = local_94 * local_a8;
        local_a0 = local_94 * local_e4;
        local_94 = local_94 + local_7c;
        local_80 = DAT_00e2cd54;
        local_a4 = DAT_00e2cd54;
        local_74 = 0.0f;
        local_b0 = DAT_00e2b1a4;
        local_78 = local_9c;
LAB_004f6733:
        local_90 = 0.0f;
        local_98 = 0.0f;
        local_88 = 0.0f;
        local_84 = 0.0f;
    }

    // compute alpha/fade factor
    local_ec = (DAT_00e2b1a4 - SQRT(fStack_d8 * fStack_d8 + fStack_dc * fStack_dc + local_e0 * local_e0) * *(float*)(iVar6 + 0x60)) * local_54;
    local_e8 = local_54;
    if (0.0f < local_ec) {
        if (DAT_00e2b1a4 <= local_ec) {
            local_ec = DAT_00e2b1a4;
        }
    } else {
        local_ec = 0.0f;
    }

    // render setup
    FUN_005334b0(&local_e0, (flags & 0x80) * 2 | -(ushort)(pfVar17[5] != 0.0f) & 2);
    FUN_00534ff0(*(undefined4*)(*(int*)(thisPtr + 0x24) + 0x14 + *(int*)(local_ac + 8)));
    if ((*(byte*)(*(int*)(thisPtr + 0x2c) + 0x20) & 0x80) != 0) {
        FUN_00533480();
    }

    iVar6 = *(int*)(thisPtr + 0x2c);
    local_70 = *(float*)(iVar6 + 0x38);
    fStack_6c = *(float*)(iVar6 + 0x3c);
    fStack_68 = *(float*)(iVar6 + 0x40);
    if ((*(uint*)(*(int*)(local_ac + 8) + *(int*)(thisPtr + 0x10)) & 0x80000) != 0) {
        iVar6 = *(int*)(thisPtr + 4);
        local_70 = *(float*)(iVar6 + 0xa0) * local_70;
        fStack_6c = *(float*)(iVar6 + 0xa4) * fStack_6c;
        fStack_68 = *(float*)(iVar6 + 0xa8) * fStack_68;
    }
    fStack_64 = DAT_00e2b1a4;

    FUN_004ecc00(); // maybe set blending mode
    FUN_004ecc90(); // set color?
    FUN_004ecc40(); // set texture?
    FUN_004eccc0(1); // set some state
    FUN_00535220(); // commit/draw

    if ((*(uint*)(*(int*)(local_ac + 8) + *(int*)(thisPtr + 0x10)) & 0x200) != 0) {
        local_ac = CONCAT31(local_ac._1_3_, 1);
        if (*(int*)(DAT_012234c4 + 0x24) != 0) goto LAB_004f68d7;
    }
    local_ac = local_ac & 0xffffff00;
LAB_004f68d7:
    FUN_00535450(local_ac, local_e0);

    // store intermediate results for vertex buffer filling
    fVar15 = fStack_14;
    fVar14 = fStack_18;
    fVar13 = fStack_1c;
    fVar12 = local_20;
    fVar11 = fStack_34;
    fVar10 = fStack_38;
    fVar9 = fStack_3c;
    fVar27 = local_40;
    fVar26 = local_74;
    fVar25 = local_78;
    fVar24 = local_7c;
    fVar23 = local_80;
    fVar22 = local_88;
    fVar21 = local_8c;
    fVar20 = local_90;
    fVar19 = local_a8;
    flags = *(ushort*)(*(int*)(thisPtr + 0x2c) + 0x20);
    uVar8 = flags >> 5;
    fStack_dc = (float)CONCAT31(fStack_dc._1_3_, 1);
    if ((flags & 0x10) != 0) {
        // swap A/B sets
        local_40 = local_50;
        fStack_3c = fStack_4c;
        fStack_38 = fStack_48;
        fStack_34 = fStack_44;
        local_50 = fVar27;
        fStack_4c = fVar9;
        fStack_48 = fVar10;
        fStack_44 = fVar11;
        local_20 = local_30;
        fStack_1c = fStack_2c;
        fStack_18 = fStack_28;
        fStack_14 = fStack_24;
        local_e8 = local_ec;
        local_30 = fVar12;
        fStack_2c = fVar13;
        fStack_28 = fVar14;
        fStack_24 = fVar15;
        local_ec = local_54;
        local_78 = local_9c;
        local_9c = fVar25;
        local_8c = local_a0;
        local_a0 = fVar21;
        local_7c = local_94;
        local_94 = fVar24;
        local_88 = local_84;
        local_84 = fVar22;
        local_80 = local_a4;
        local_a4 = fVar23;
        local_a8 = local_e4;
        local_e4 = fVar19;
        local_74 = local_b0;
        local_b0 = fVar26;
        local_90 = local_98;
        local_98 = fVar20;
    }

    // allocate vertex buffer: 5 segments, 7 floats per vertex? (5*7 = 35 floats)
    pfVar17 = (float*)FUN_00533880(5, 7);
    if (pfVar17 != (float*)0x0) {
        fVar19 = 0.0f;
        // compute first set of vertices (A set)
        local_70 = local_30 + local_50; // position
        fStack_6c = fStack_2c + fStack_4c;
        fStack_68 = fStack_28 + fStack_48;
        fStack_64 = fStack_24 + fStack_44;
        fStack_c4 = 0.0f;
        fStack_c8 = 0.0f;
        fStack_cc = 0.0f;
        local_d0 = 0.0f;
        fStack_b4 = 0.0f;
        fStack_b8 = 0.0f;
        fStack_bc = 0.0f;
        local_c0 = 0.0f;
        FUN_00414aa0(); // maybe compute tangent/normal
        fStack_c4 = fVar19;
        if ((uVar8 & 1) != 0) {
            fStack_c4 = local_ec;
        }
        local_c0 = local_9c + local_a0;
        fStack_bc = local_94 + local_84;
        fStack_b8 = local_a4 + local_e4;
        fStack_b4 = local_b0 + local_98;
        *pfVar17 = local_d0;
        pfVar17[1] = fStack_cc;
        pfVar17[2] = fStack_c8;
        pfVar17[3] = fStack_c4;
        pfVar17[4] = local_c0;
        pfVar17[5] = fStack_bc;
        pfVar17[6] = fStack_b8;
        pfVar17[7] = fStack_b4;

        // second set (B set, offset +8)
        local_70 = local_20 + local_40;
        fStack_6c = fStack_1c + fStack_3c;
        fStack_68 = fStack_18 + fStack_38;
        fStack_64 = fStack_14 + fStack_34;
        fVar20 = local_9c;
        fVar21 = local_94;
        FUN_00414aa0();
        fStack_c4 = fVar19;
        if ((uVar8 & 1) != 0) {
            fStack_c4 = local_e8;
        }
        local_c0 = local_8c + local_78;
        fStack_bc = local_88 + local_7c;
        fStack_b8 = local_80 + local_a8;
        fStack_b4 = local_74 + local_90;
        pfVar17[8] = local_d0;
        pfVar17[9] = fStack_cc;
        pfVar17[10] = fStack_c8;
        pfVar17[0xb] = fStack_c4;
        pfVar17[0xc] = local_c0;
        pfVar17[0xd] = fStack_bc;
        pfVar17[0xe] = fStack_b8;
        pfVar17[0xf] = fStack_b4;

        // third set (color/alpha only)
        fVar19 = local_78;
        fVar22 = local_7c;
        fVar23 = local_80;
        fVar24 = local_74;
        FUN_00414aa0();
        fStack_b8 = local_a4;
        fStack_b4 = local_b0;
        fStack_c4 = local_ec;
        pfVar17[0x10] = local_d0;
        pfVar17[0x11] = fStack_cc;
        pfVar17[0x12] = fStack_c8;
        pfVar17[0x13] = local_ec;
        pfVar17[0x14] = fVar20;
        pfVar17[0x15] = fVar21;
        pfVar17[0x16] = local_a4;
        pfVar17[0x17] = local_b0;

        fVar25 = local_ec;
        local_c0 = fVar20;
        fStack_bc = fVar21;
        FUN_00414aa0();
        fStack_c4 = local_e8;
        pfVar17[0x18] = local_d0;
        pfVar17[0x19] = fStack_cc;
        pfVar17[0x1a] = fStack_c8;
        pfVar17[0x1b] = local_e8;
        pfVar17[0x1c] = fVar19;
        pfVar17[0x1d] = fVar22;
        pfVar17[0x1e] = fVar23;
        pfVar17[0x1f] = fVar24;

        local_c0 = fVar19;
        fStack_bc = fVar22;
        fStack_b8 = fVar23;
        fStack_b4 = fVar24;
        FUN_00414aa0();
        fStack_b8 = local_a4;
        fStack_b4 = local_b0;
        pfVar17[0x20] = local_d0;
        pfVar17[0x21] = fStack_cc;
        pfVar17[0x22] = fStack_c8;
        pfVar17[0x23] = fVar25;
        pfVar17[0x24] = fVar20;
        pfVar17[0x25] = fVar21;
        pfVar17[0x26] = local_a4;
        pfVar17[0x27] = local_b0;

        // difference vectors for edges
        local_70 = local_40 - local_20;
        fStack_6c = fStack_3c - fStack_1c;
        fStack_68 = fStack_38 - fStack_18;
        fStack_64 = fStack_34 - fStack_14;
        fStack_c4 = fVar25;
        local_c0 = fVar20;
        fStack_bc = fVar21;
        FUN_00414aa0();
        if ((uVar8 & 1) == 0) {
            local_e8 = 0.0f;
        }
        local_c0 = fVar19 - local_8c;
        fStack_bc = fVar22 - local_88;
        fStack_b8 = fVar23 - local_a8;
        fStack_b4 = fVar24 - local_90;
        pfVar17[0x28] = local_d0;
        pfVar17[0x29] = fStack_cc;
        pfVar17[0x2a] = fStack_c8;
        pfVar17[0x2b] = local_e8;
        pfVar17[0x2c] = local_c0;
        pfVar17[0x2d] = fStack_bc;
        pfVar17[0x2e] = fStack_b8;
        pfVar17[0x2f] = fStack_b4;

        local_70 = local_50 - local_30;
        fStack_6c = fStack_4c - fStack_2c;
        fStack_68 = fStack_48 - fStack_28;
        fStack_64 = fStack_44 - fStack_24;
        fStack_c4 = local_e8;
        FUN_00414aa0();
        if ((uVar8 & 1) == 0) {
            local_ec = 0.0f;
        }
        local_c0 = fVar20 - local_a0;
        fStack_bc = fVar21 - local_84;
        fStack_b8 = local_a4 - local_e4;
        fStack_b4 = local_b0 - local_98;
        pfVar17[0x30] = local_d0;
        pfVar17[0x31] = fStack_cc;
        pfVar17[0x32] = fStack_c8;
        pfVar17[0x33] = local_ec;
        pfVar17[0x34] = local_c0;
        pfVar17[0x35] = fStack_bc;
        pfVar17[0x36] = fStack_b8;
        pfVar17[0x37] = fStack_b4;

        fStack_c4 = local_ec;
        FUN_0060cde0(); // submit vertex buffer to GPU
    }

    FUN_00533720(&local_e0); // cleanup
    return;
}