// FUNC_NAME: RenderManager::submitDrawableList
// Function address: 0x00512870
// Role: Submits a batch of drawable objects from a bitmask-sorted list to render command buffer.
// The function processes up to 'count' drawable indices starting from 'startIndex',
// performing visibility checks, transformations, and writing render commands to an allocated buffer.

// Notes: Uses EA EARS engine globals for profiling (DAT_012058d0 etc.).
// References global constants at 0x00e2af44 (visibility threshold), 0x00e2b1a4 (zero?),
// 0x00e2cd54 (identity?).

bool RenderManager::submitDrawableList(void* this, void* viewContext, uint startIndex, int count)
{
    int* bitmaskWord;
    float fVar2;
    float fVar3;
    uint uVar4;
    char cVar5;
    byte bVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    bool bVar10;
    undefined4* dstBuffer;
    uint uVar11;
    int iVar12;
    uint uVar13;
    int fsOffset;
    float fVar14;
    float fVar15;
    double dVar16;
    int remaining;
    uint currentIndex;
    int countdown;
    float floatVar148;
    undefined4 transform0[16]; // local_130 to local_100
    float local_110;
    float local_10c;
    float local_108;
    undefined4 local_104;
    float local_100;
    float fStack_fc;
    float fStack_f8;
    float fStack_f4;
    undefined4 local_f0;
    undefined4 local_ec;
    undefined4 local_e8;
    undefined4 local_e4;
    undefined4 local_e0;
    undefined4 local_dc;
    undefined4 local_d8;
    undefined4 local_d4;
    undefined4 local_d0;
    undefined4 uStack_cc;
    undefined4 uStack_c8;
    undefined4 uStack_c4;
    float local_c0;
    float local_bc;
    undefined4 local_b8;
    undefined4 local_b4;
    undefined4 local_b0;
    float local_ac;
    float local_a8;
    undefined4 local_a4;
    float local_a0;
    float fStack_9c;
    float fStack_98;
    float fStack_94;
    float local_90[4];
    float fStack_7c[4];
    float fStack_68[4];
    float local_50[4];
    float fStack_3c[4];
    float fStack_28[4];
    float fStack_14[4];

    // Early out: if object's Z distance is below threshold or special flag is set
    if ((*(float*)(this + 0x40) <= DAT_00e2af44) &&
        ((*(uint*)(*(int*)(this + 0x10) + 0x10c) & 0x800000) == 0))
    {
        return 1;
    }

    iVar12 = *(int*)(this + 0x58);
    if (iVar12 == 0)
    {
        iVar7 = *(int*)(this + 0x10);
        if (((((*(uint*)(iVar7 + 0x108) & 0x4000) == 0) && ((*(uint*)(iVar7 + 0x10c) & 0x180000) == 0)) &&
            (((*(byte*)(*(int*)(**(int**)(fsOffset + 0x2c) + 8) + *(int*)(this + 8)) & 4) == 0 ||
             ((*(uint*)(iVar7 + 0x108) & 0x20000000) == 0)))) &&
            (bVar10 = false, (*(byte*)(iVar7 + 0x104) & 0x80) == 0))
        {
            goto LAB_005128fb;
        }
    }
    bVar10 = true;

LAB_005128fb:
    iVar7 = **(int**)(fsOffset + 0x2c);
    if (((*(uint*)(*(int*)(this + 8) + *(int*)(iVar7 + 8)) & 0x200) == 0) ||
        (*(int*)(DAT_012234c4 + 0x24) == 0))
    {
        countdown = 0;
    }
    else
    {
        countdown = 1;
    }

    FUN_005376e0(); // some init
    DAT_012058e8 = &DAT_0121a380;
    FUN_0060a460(DAT_0121a390); // release or free
    FUN_0060a460(DAT_0121a394); // release or free

    local_e0 = DAT_00e2eff4; // some default color?
    if ((*(byte*)(*(int*)(this + 0x10) + 0x104) & 4) != 0)
    {
        local_e0 = *(undefined4*)(*(int*)(this + 0x10) + 0x128);
        remaining = CONCAT31((int3)((uint)iVar12 >> 8), DAT_01163840 != '\0');
        FUN_00537c40(remaining);
        FUN_005378e0();
        FUN_00537880();
    }

    local_dc = 0;
    local_d8 = 0;
    local_d4 = 0;
    FUN_0060add0(DAT_0121a390, DAT_0121b63c[6], &local_e0);

    if (*(int*)(this + 0x58) != 0)
    {
        FUN_005120c0(); // some state push
    }

    if (*DAT_0121b0ac != 0)
    {
        FUN_006063b0(); // profiling begin?
    }

    if (*(char*)(*(int*)(this + 0x10) + 0x60) == '\x01')
    {
        FUN_00537790(*(undefined4*)(this + 0x60)); // set active profile?
    }

    if ((*(uint*)(*(int*)(this + 0x10) + 0x104) & 0x100) != 0)
    {
        FUN_005121b0(); // some special mode
    }

    // Set profiling zone markers
    if (DAT_012058d0 < 7) DAT_012058d0 = 7;
    if (7 < DAT_00f15988) DAT_00f15988 = 7;
    _DAT_011f39f4 = (uint)(~*(byte*)(*(int*)(this + 0x10) + 0x10c) & 1);
    if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
    if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
    _DAT_011f3a10 = (uint)((byte)((uint)*(undefined4*)(*(int*)(this + 0x10) + 0x108) >> 0x1c) & 1);
    // ... more profiling zones (omitted for brevity, but they set _DAT_ globals accordingly)
    // (The full decompiled code includes many similar blocks)

    FUN_004ec7a0(); // some setup

    cVar5 = *(char*)(*(int*)(this + 0x10) + 0x112);
    fVar14 = DAT_00e2b1a4;
    if ((cVar5 != '\0') && (cVar5 != '\x02'))
    {
        fVar14 = 0.0f;
    }
    FUN_00537d80(countdown, fVar14, 0, *(uint*)(*(int*)(this + 0x10) + 0x10c) >> 0x1b & 0xffffff01);

    bVar6 = *(byte*)(*(int*)(this + 0x10) + 0x171);
    // More profiling zone assignments (omitted)
    // ...

    local_d0 = *(undefined4*)(this + 0x20);
    uStack_cc = *(undefined4*)(this + 0x24);
    uStack_c8 = *(undefined4*)(this + 0x28);
    uStack_c4 = *(undefined4*)(this + 0x2c);
    currentIndex = startIndex;

    iVar12 = *(int*)(this + 0x10);
    local_c0 = *(float*)(iVar12 + 0x184) * *(float*)(this + 0x38);
    local_bc = *(float*)(iVar12 + 0x188) * *(float*)(this + 0x3c);
    countdown = count;
    local_b8 = *(undefined4*)(*(int*)(this + 0x14) + 0x50);
    local_b4 = *(undefined4*)(*(int*)(this + 0x14) + 0x54);
    local_b0 = *(undefined4*)(this + 0x34);

    if ((*(byte*)(iVar12 + 0x104) & 0x40) == 0)
    {
        local_ac = DAT_00e4487c;
        local_a8 = DAT_00e447e8;
    }
    else
    {
        dVar16 = (double)(*(float*)(viewContext + 0x14c) * DAT_00e2cd54);
        FUN_00b9c041(); // sqrt approximation?
        local_ac = *(float*)(*(int*)(this + 0x10) + 0x134) * (DAT_00e44880 / (float)dVar16);
        local_a8 = *(float*)(*(int*)(this + 0x10) + 0x138) * (DAT_00e44880 / (float)dVar16);
    }

    local_a4 = DAT_00e44718;
    if ((*(byte*)(*(int*)(this + 0x10) + 0x104) & 0x80) == 0)
    {
        local_a4 = 0;
    }

    FUN_0060ab00(DAT_0121a390, DAT_0121b63c[4], &local_d0, 0xc);

    if (!bVar10)
    {
        iVar12 = *(int*)(this + 8) + *(int*)(iVar7 + 8);
        if ((*(byte*)(*(int*)(this + 8) + *(int*)(iVar7 + 8)) & 4) == 0)
        {
            // Clear arrays
            local_50[0] = DAT_00e2b1a4; local_50[1] = 0; local_50[2] = 0; local_50[3] = 0;
            fStack_3c[0] = 0; fStack_3c[1] = DAT_00e2b1a4; fStack_3c[2] = 0; fStack_3c[3] = 0;
            fStack_28[0] = 0; fStack_28[1] = 0; fStack_28[2] = DAT_00e2b1a4; fStack_28[3] = 0;
            fStack_14[0] = 0; fStack_14[1] = 0; fStack_14[2] = 0; fStack_14[3] = DAT_00e2b1a4;
        }
        else
        {
            memcpy(&local_50, (void*)(iVar12 + 0x50), 16);
            memcpy(&fStack_3c, (void*)(iVar12 + 0x60), 16);
            memcpy(&fStack_28, (void*)(iVar12 + 0x70), 16);
            memcpy(&fStack_14, (void*)(iVar12 + 0x80), 16);
        }

        // Second copy based on flag 0x2
        if ((*(byte*)(*(int*)(this + 0x10) + 0x104) & 2) == 0)
        {
            local_90[0] = DAT_00e2b1a4; local_90[1] = 0; local_90[2] = 0; local_90[3] = 0;
            fStack_7c[0] = 0; fStack_7c[1] = DAT_00e2b1a4; fStack_7c[2] = 0; fStack_7c[3] = 0;
            fStack_68[0] = 0; fStack_68[1] = 0; fStack_68[2] = DAT_00e2b1a4; fStack_68[3] = 0;
            fStack_14[0] = 0; fStack_14[1] = 0; fStack_14[2] = 0; fStack_14[3] = DAT_00e2b1a4; // note: reuse same array
        }
        else
        {
            memcpy(&local_90, (void*)(iVar12 + 0x50), 16);
            memcpy(&fStack_7c, (void*)(iVar12 + 0x60), 16);
            memcpy(&fStack_68, (void*)(iVar12 + 0x70), 16);
            // (same pattern, but offset differs? Actually the code copies from same offsets, possible bug?
            // The original code uses iVar12+0x50 etc. again, but with different arrays.
        }

        FUN_0060b020(DAT_0121a390, *DAT_0121b63c, &local_90);
        FUN_0060b020(DAT_0121a390, DAT_0121b63c[1], &local_50);
    }

    FUN_0060b020(DAT_0121a390, DAT_0121b63c[2], &DAT_01218e00);
    FUN_0060b020(DAT_0121a390, DAT_0121b63c[3], &DAT_01218d80);

    // Allocate output buffer and begin writing commands
    FUN_0060c8d0(0, &DAT_01198e20, 4, 0, 0x40000000, 4, count);
    dstBuffer = (undefined4*)FUN_0060cd00(0xd, 4, 0x80000000, count, 1);
    if (dstBuffer != (undefined4*)0x0)
    {
        remaining = count;
        fVar14 = DAT_00e2cd54; // 1.0 ?
        if (count != 0)
        {
            do
            {
                countdown = countdown - 1;
                bitmaskWord = (int*)(this + 0x80 + ((int)currentIndex >> 3) * 8);
                uVar13 = currentIndex & 7;
                if ((*bitmaskWord != 0) &&
                    (iVar12 = uVar13 * 0x50,
                     (*(byte*)(iVar12 + *bitmaskWord + 0x54 + *(int*)(iVar7 + 8)) & 1) == 0))
                {
                    if ((bVar10) || ((*(uint*)(*(int*)(this + 0x10) + 0x10c) & 0x800000) != 0))
                    {
                        FUN_00511250(this, bitmaskWord, uVar13); // some per-object function
                        fVar14 = DAT_00e2cd54;
                    }

                    uVar11 = *(uint*)(*(int*)(this + 0x10) + 0x10c);
                    if ((uVar11 & 0x800000) == 0)
                    {
                        fVar15 = *(float*)(this + 0x40);
                    }
                    else
                    {
                        local_a0 = local_100 - *(float*)(viewContext + 0x70);
                        fStack_9c = fStack_fc - *(float*)(viewContext + 0x74);
                        fStack_98 = fStack_f8 - *(float*)(viewContext + 0x78);
                        fStack_94 = fStack_f4 - *(float*)(viewContext + 0x7c);
                        fVar14 = local_110 * local_a0 + local_10c * fStack_9c + local_108 * fStack_98;
                        dVar16 = (double)((fVar14 * fVar14) /
                                         (local_a0 * local_a0 + fStack_9c * fStack_9c + fStack_98 * fStack_98 +
                                          (float)PTR_FUN_00e4462c));
                        FUN_00b9af10(); // sqrt?
                        fVar14 = (float)dVar16;
                        fVar15 = (DAT_00e445ac - fVar14 * DAT_00e2b04c) * fVar14 * fVar14 *
                                 *(float*)(this + 0x4c);
                        fVar14 = DAT_00e2cd54;
                    }

                    if (DAT_00e2af44 < fVar15)
                    {
                        remaining = remaining - 1;
                        FUN_0050a810((int*)(this + 0x10), bitmaskWord, fVar15);

                        iVar8 = *(int*)(iVar7 + 8);
                        iVar9 = *bitmaskWord;
                        fVar15 = *(float*)(iVar9 + uVar13 * 4 + iVar8);
                        if ((*(uint*)(*(int*)(this + 0x10) + 0x108) & 0x20000000) != 0)
                        {
                            fVar15 = fVar15 - (*(float*)(iVar12 + iVar9 + 0x58 + iVar8) - DAT_00e2b1a4) *
                                              *(float*)(*(int*)(this + 0x14) + 0xc);
                        }

                        fVar2 = *(float*)(iVar12 + iVar9 + 0x6c + iVar8);
                        iVar8 = iVar12 + iVar9 + iVar8;
                        if (fVar2 <= fVar15)
                        {
                            fVar15 = fVar2;
                        }

                        iVar12 = *(int*)(this + 0x14);
                        fVar2 = *(float*)(iVar12 + 0x88);
                        fVar3 = *(float*)(iVar12 + 0x8c);
                        floatVar148 = *(float*)(iVar12 + 0x70) * fVar15;
                        fVar15 = *(float*)(iVar12 + 0x74) * fVar15;

                        if ((uVar11 & 0x80) == 0)
                        {
                            floatVar148 = (float)(int)((floatVar148 - (float)(int)floatVar148) *
                                                      *(float*)(iVar12 + 0x80)) * fVar2;
                            fVar15 = (float)(int)((fVar15 - (float)(int)fVar15) *
                                                   *(float*)(iVar12 + 0x84)) * fVar3;
                        }

                        bVar6 = *(byte*)(iVar8 + 0x5c);
                        uVar4 = *(undefined4*)(iVar8 + 0x40);
                        // Write command data to dstBuffer
                        dstBuffer[0] = *(undefined4*)(iVar8 + 0x20);
                        dstBuffer[1] = *(undefined4*)(iVar8 + 0x24);
                        dstBuffer[2] = *(undefined4*)(iVar8 + 0x28);
                        dstBuffer[3] = uVar4;
                        dstBuffer[4] = local_f0;
                        dstBuffer[5] = local_ec;
                        dstBuffer[6] = local_e8;
                        uVar11 = (bVar6 & 0xffffff80) << 0x18;
                        uVar13 = (uint)fVar2 | uVar11;
                        dstBuffer[7] = local_e4;
                        dstBuffer[8] = (uint)floatVar148 | uVar11;
                        dstBuffer[9] = fVar15;
                        dstBuffer[10] = uVar13;
                        dstBuffer[0xb] = fVar3;

                        if (bVar10)
                        {
                            // Extended data if bVar10 set
                            dstBuffer[0xc] = local_130;
                            dstBuffer[0xd] = local_12c;
                            dstBuffer[0xe] = local_128;
                            dstBuffer[0xf] = local_124;
                            dstBuffer[0x10] = local_120;
                            dstBuffer[0x11] = local_11c;
                            dstBuffer[0x12] = local_118;
                            dstBuffer[0x13] = local_114;
                            dstBuffer[0x14] = local_110;
                            dstBuffer[0x15] = local_10c;
                            dstBuffer[0x16] = local_108;
                            dstBuffer[0x17] = local_104;
                            dstBuffer[0x18] = local_100;
                            dstBuffer[0x19] = fStack_fc;
                            dstBuffer[0x1a] = fStack_f8;
                            dstBuffer[0x1b] = fStack_f4;
                            dstBuffer += 0x1c;
                        }
                        else
                        {
                            FUN_0050a940(bitmaskWord);
                            dstBuffer[0xc] = uVar13;
                            cVar5 = *(char*)(*(int*)(this + 0x10) + 0x157);
                            dstBuffer[0xd] = (float)(int)cVar5 + fVar14;
                            uVar13 = 0x21 >> (cVar5 * '\x04' & 0x1fU) & 0xf;
                            dstBuffer[0xe] = (float)uVar13 + fVar14;
                            dstBuffer[0xf] = (float)(0x21 >> ((char)uVar13 * '\x04' & 0x1fU) & 0xf) + fVar14;
                            dstBuffer += 0x10;
                        }
                    }
                }

                currentIndex = currentIndex + 1;
                if ((int)*(short*)(this + 0x6e) <= (int)currentIndex)
                {
                    currentIndex = currentIndex - (int)*(short*)(this + 0x6e);
                }
            } while (countdown != 0);
        }

        if (0 < remaining)
        {
            _memset(dstBuffer, 0, remaining * ((-(uint)bVar10 & 0x30) + 0x40));
        }

        FUN_0060cde0(); // finalize allocation
        FUN_00537230(); // some sync
    }

    // End profiling zones
    if (*DAT_0121b0ac != 0)
    {
        uVar13 = *DAT_0121b0ac & 0xff;
        if ((&DAT_011eb8fc)[DAT_0121a394 * 0x10] != '\0')
        {
            uVar13 = uVar13 + 0x10;
        }
        FUN_00618d40();
        (&DAT_011d912c)[uVar13] = 0;
    }

    if (DAT_0121b0ac[1] != 0)
    {
        uVar13 = DAT_0121b0ac[1] & 0xff;
        if ((&DAT_011eb8fc)[DAT_0121a394 * 0x10] != '\0')
        {
            uVar13 = uVar13 + 0x10;
        }
        FUN_00618d40();
        (&DAT_011d912c)[uVar13] = 0;
    }

    if (((*(uint*)(*(int*)(this + 0x10) + 0x104) & 0x100) != 0) && (DAT_0121b0ac[3] != 0))
    {
        uVar13 = DAT_0121b0ac[3] & 0xff;
        if ((&DAT_011eb8fc)[DAT_0121a394 * 0x10] != '\0')
        {
            uVar13 = uVar13 + 0x10;
        }
        FUN_00618d40();
        (&DAT_011d912c)[uVar13] = 0;
    }

    if (*(int*)(this + 0x58) != 0)
    {
        FUN_005379d0(0, 0);
    }

    // Reset globals
    DAT_012058e8 = (undefined4*)0x0;
    DAT_0121a390 = 0;
    DAT_0121a394 = 0;

    // Reset profiling zones (opposite of above)
    if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
    if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
    _DAT_011f3a44 = 0;
    if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
    if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
    _DAT_011f3a3c = 7;
    if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
    if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
    _DAT_011f3a38 = 0;
    if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
    if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
    _DAT_011f3a14 = 0;
    if (DAT_012058d0 < 7) DAT_012058d0 = 7;
    if (7 < DAT_00f15988) DAT_00f15988 = 7;
    _DAT_011f39f4 = 1;
    if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
    if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
    _DAT_011f3a10 = 1;
    if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
    if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
    _DAT_011f3a30 = 1;

    FUN_00417cf0(1, 5, 6); // profiling end
    return 1;
}