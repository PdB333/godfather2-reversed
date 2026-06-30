// FUN_00512870: Renderer::submitCommandBuffer
undefined4 __thiscall Renderer::submitCommandBuffer(CRenderContext* thisContext, void* cameraData, uint startIndex, int count)
{
  int* piVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  char cVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bForceUpdate;
  undefined4* dstBuffer;
  uint uVar11;
  int iVar12;
  uint uVar13;
  int unaff_FS_OFFSET;
  float fVar14;
  float fVar15;
  double dVar16;
  int loopCounter;
  uint currentIndex;
  int arrayIndex;
  float local_f4;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  float local_110;
  float local_10c;
  float local_108;
  undefined4 local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
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
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  float local_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  float local_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  float local_54;
  float local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  float local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  float local_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  float local_14;

  // Early exit: if certain conditions are met (e.g., object too small or flag set), return 1
  if ((*(float*)(thisContext + 0x40) <= DAT_00e2af44) &&
      ((*(uint*)(*(int*)(thisContext + 0x10) + 0x10c) & 0x800000) == 0)) {
    return 1;
  }

  iVar12 = *(int*)(thisContext + 0x58);
  if (iVar12 == 0) {
    iVar7 = *(int*)(thisContext + 0x10);
    if (((((*(uint*)(iVar7 + 0x108) & 0x4000) == 0) && ((*(uint*)(iVar7 + 0x10c) & 0x180000) == 0)) &&
        (((*(byte*)(*(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 8) + *(int*)(thisContext + 8)) & 4) == 0 ||
         ((*(uint*)(iVar7 + 0x108) & 0x20000000) == 0)))) &&
       (bForceUpdate = false, (*(byte*)(iVar7 + 0x104) & 0x80) == 0))
      goto skipForceUpdate;
  }
  bForceUpdate = true;
skipForceUpdate:
  iVar7 = **(int**)(unaff_FS_OFFSET + 0x2c); // Get PEB pointer for global state access

  // Determine if we should use high detail rendering
  if (((*(uint*)(*(int*)(thisContext + 8) + *(int*)(iVar7 + 8)) & 0x200) == 0) ||
      (*(int*)(DAT_012234c4 + 0x24) == 0)) {
    arrayIndex = 0;
  } else {
    arrayIndex = 1;
  }

  FUN_005376e0(); // Begin render state setup
  DAT_012058e8 = &DAT_0121a380;
  FUN_0060a460(DAT_0121a390); // Clear some render states
  FUN_0060a460(DAT_0121a394);
  local_e0 = DAT_00e2eff4; // Default projection/view matrix

  if ((*(byte*)(*(int*)(thisContext + 0x10) + 0x104) & 4) != 0) {
    local_e0 = *(undefined4*)(*(int*)(thisContext + 0x10) + 0x128);
    loopCounter = CONCAT31((int3)((uint)iVar12 >> 8), DAT_01163840 != '\0');
    FUN_00537c40(loopCounter);
    FUN_005378e0();
    FUN_00537880();
  }

  local_dc = 0;
  local_d8 = 0;
  local_d4 = 0;
  FUN_0060add0(DAT_0121a390, DAT_0121b63c[6], &local_e0); // Set world matrix?

  if (*(int*)(thisContext + 0x58) != 0) {
    FUN_005120c0(); // Initialize additional states
  }

  if (*DAT_0121b0ac != 0) {
    FUN_006063b0(); // Clear audio?
  }

  if (*(char*)(*(int*)(thisContext + 0x10) + 0x60) == '\x01') {
    FUN_00537790(*(undefined4*)(thisContext + 0x60));
  }

  if ((*(uint*)(*(int*)(thisContext + 0x10) + 0x104) & 0x100) != 0) {
    FUN_005121b0(); // Enable special effect
  }

  // Clamp global resolution/minimum and set z-buffer constants
  if (DAT_012058d0 < 7) DAT_012058d0 = 7;
  if (7 < DAT_00f15988) DAT_00f15988 = 7;
  _DAT_011f39f4 = (uint)(~*(byte*)(*(int*)(thisContext + 0x10) + 0x10c) & 1);
  if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
  if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
  _DAT_011f3a10 = (uint)((byte)((uint)*(undefined4*)(*(int*)(thisContext + 0x10) + 0x108) >> 0x1c) & 1);
  if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
  if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
  _DAT_011f3a30 = 1;
  if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
  if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
  _DAT_011f3a44 = 1;

  FUN_004ec7a0(); // Set viewport?

  cVar5 = *(char*)(*(int*)(thisContext + 0x10) + 0x112);
  fVar14 = DAT_00e2b1a4;
  if ((cVar5 != '\0') && (cVar5 != '\x02')) {
    fVar14 = 0.0f;
  }
  FUN_00537d80(arrayIndex, fVar14, 0, *(uint*)(*(int*)(thisContext + 0x10) + 0x10c) >> 0x1b & 0xffffff01);

  bVar6 = *(byte*)(*(int*)(thisContext + 0x10) + 0x171);
  // Clamp and set more z-buffer registers
  if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
  if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
  _DAT_011f3a3c = 7;
  if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
  if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
  _DAT_011f3a38 = (uint)bVar6;
  if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
  if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
  _DAT_011f3a14 = (uint)(bVar6 != 0);

  // Copy the 4x4 transformation matrix from context (+0x20)
  local_d0 = *(undefined4*)(thisContext + 0x20);
  uStack_cc = *(undefined4*)(thisContext + 0x24);
  uStack_c8 = *(undefined4*)(thisContext + 0x28);
  uStack_c4 = *(undefined4*)(thisContext + 0x2c);

  currentIndex = startIndex;
  iVar12 = *(int*)(thisContext + 0x10);
  // Scaling factors from context and object
  local_c0 = *(float*)(iVar12 + 0x184) * *(float*)(thisContext + 0x38);
  local_bc = *(float*)(iVar12 + 0x188) * *(float*)(thisContext + 0x3c);

  loopCounter = count;
  // More data from sub-object
  local_b8 = *(undefined4*)(*(int*)(thisContext + 0x14) + 0x50);
  local_b4 = *(undefined4*)(*(int*)(thisContext + 0x14) + 0x54);
  local_b0 = *(undefined4*)(thisContext + 0x34);

  if ((*(byte*)(iVar12 + 0x104) & 0x40) == 0) {
    local_ac = DAT_00e4487c;
    local_a8 = DAT_00e447e8;
  } else {
    dVar16 = (double)(*(float*)(cameraData + 0x14c) * DAT_00e2cd54);
    FUN_00b9c041();
    local_ac = *(float*)(*(int*)(thisContext + 0x10) + 0x134) * (DAT_00e44880 / (float)dVar16);
    local_a8 = *(float*)(*(int*)(thisContext + 0x10) + 0x138) * (DAT_00e44880 / (float)dVar16);
  }

  local_a4 = DAT_00e44718;
  if ((*(byte*)(*(int*)(thisContext + 0x10) + 0x104) & 0x80) == 0) {
    local_a4 = 0;
  }

  // Set the model matrix (local_d0 is 3x4? size 0xc = 12 bytes)
  FUN_0060ab00(DAT_0121a390, DAT_0121b63c[4], &local_d0, 0xc);

  if (!bForceUpdate) {
    iVar12 = *(int*)(thisContext + 8) + *(int*)(iVar7 + 8);
    // Copy two sets of 4x4 transformation matrices from the global state
    if ((*(byte*)(*(int*)(thisContext + 8) + *(int*)(iVar7 + 8)) & 4) == 0) {
      local_50 = DAT_00e2b1a4;
      uStack_4c = 0; uStack_48 = 0; uStack_44 = 0;
      local_40 = 0;
      local_3c = DAT_00e2b1a4;
      uStack_38 = 0; uStack_34 = 0;
      local_30 = 0;
      uStack_2c = 0;
      local_28 = DAT_00e2b1a4;
      uStack_24 = 0;
      local_20 = 0; uStack_1c = 0; uStack_18 = 0;
      local_14 = DAT_00e2b1a4;
    } else {
      local_50 = *(float*)(iVar12 + 0x50);
      uStack_4c = *(undefined4*)(iVar12 + 0x54);
      uStack_48 = *(undefined4*)(iVar12 + 0x58);
      uStack_44 = *(undefined4*)(iVar12 + 0x5c);
      local_40 = *(undefined4*)(iVar12 + 0x60);
      local_3c = *(float*)(iVar12 + 100);
      uStack_38 = *(undefined4*)(iVar12 + 0x68);
      uStack_34 = *(undefined4*)(iVar12 + 0x6c);
      local_30 = *(undefined4*)(iVar12 + 0x70);
      uStack_2c = *(undefined4*)(iVar12 + 0x74);
      local_28 = *(float*)(iVar12 + 0x78);
      uStack_24 = *(undefined4*)(iVar12 + 0x7c);
      local_20 = *(undefined4*)(iVar12 + 0x80);
      uStack_1c = *(undefined4*)(iVar12 + 0x84);
      uStack_18 = *(undefined4*)(iVar12 + 0x88);
      local_14 = *(float*)(iVar12 + 0x8c);
    }

    if ((*(byte*)(*(int*)(thisContext + 0x10) + 0x104) & 2) == 0) {
      local_90 = DAT_00e2b1a4;
      uStack_8c = 0; uStack_88 = 0; uStack_84 = 0;
      local_80 = 0;
      local_7c = DAT_00e2b1a4;
      uStack_78 = 0; uStack_74 = 0;
      local_70 = 0;
      uStack_6c = 0;
      local_68 = DAT_00e2b1a4;
      uStack_64 = 0;
      local_60 = 0; uStack_5c = 0; uStack_58 = 0;
      local_54 = DAT_00e2b1a4;
    } else {
      local_90 = *(float*)(iVar12 + 0x50);
      uStack_8c = *(undefined4*)(iVar12 + 0x54);
      uStack_88 = *(undefined4*)(iVar12 + 0x58);
      uStack_84 = *(undefined4*)(iVar12 + 0x5c);
      local_80 = *(undefined4*)(iVar12 + 0x60);
      local_7c = *(float*)(iVar12 + 100);
      uStack_78 = *(undefined4*)(iVar12 + 0x68);
      uStack_74 = *(undefined4*)(iVar12 + 0x6c);
      local_70 = *(undefined4*)(iVar12 + 0x70);
      uStack_6c = *(undefined4*)(iVar12 + 0x74);
      local_68 = *(float*)(iVar12 + 0x78);
      uStack_64 = *(undefined4*)(iVar12 + 0x7c);
      local_60 = *(undefined4*)(iVar12 + 0x80);
      uStack_5c = *(undefined4*)(iVar12 + 0x84);
      uStack_58 = *(undefined4*)(iVar12 + 0x88);
      local_54 = *(float*)(iVar12 + 0x8c);
    }

    // Set two more matrices (lighting/view dependent?)
    FUN_0060b020(DAT_0121a390, *DAT_0121b63c, &local_90);
    FUN_0060b020(DAT_0121a390, DAT_0121b63c[1], &local_50);
  }

  // Set two more matrices from global constants
  FUN_0060b020(DAT_0121a390, DAT_0121b63c[2], &DAT_01218e00);
  FUN_0060b020(DAT_0121a390, DAT_0121b63c[3], &DAT_01218d80);

  // Allocate buffer for command list
  FUN_0060c8d0(0, &DAT_01198e20, 4, 0, 0x40000000, 4, count);
  dstBuffer = (undefined4*)FUN_0060cd00(0xd, 4, 0x80000000, count, 1);

  if (dstBuffer != (undefined4*)0x0) {
    loopCounter = count;
    fVar14 = DAT_00e2cd54;
    if (count != 0) {
      do {
        arrayIndex--;
        piVar1 = (int*)(thisContext + 0x80 + ((int)currentIndex >> 3) * 8);
        uVar13 = currentIndex & 7;
        if ((*piVar1 != 0) &&
           (iVar12 = uVar13 * 0x50,
           (*(byte*)(iVar12 + *piVar1 + 0x54 + *(int*)(iVar7 + 8)) & 1) == 0)) {
          if ((bForceUpdate) || ((*(uint*)(*(int*)(thisContext + 0x10) + 0x10c) & 0x800000) != 0)) {
            FUN_00511250(thisContext, piVar1, uVar13);
            fVar14 = DAT_00e2cd54;
          }
          uVar11 = *(uint*)(*(int*)(thisContext + 0x10) + 0x10c);
          if ((uVar11 & 0x800000) == 0) {
            fVar15 = *(float*)(thisContext + 0x40);
          } else {
            local_a0 = local_100 - *(float*)(cameraData + 0x70);
            local_9c = local_fc - *(float*)(cameraData + 0x74);
            local_98 = local_f8 - *(float*)(cameraData + 0x78);
            local_94 = local_f4 - *(float*)(cameraData + 0x7c);
            fVar14 = local_110 * local_a0 + local_10c * local_9c + local_108 * local_98;
            dVar16 = (double)((fVar14 * fVar14) /
                             (local_a0 * local_a0 + local_9c * local_9c + local_98 * local_98 +
                             (float)PTR_FUN_00e4462c));
            FUN_00b9af10();
            fVar14 = (float)dVar16;
            fVar15 = (DAT_00e445ac - fVar14 * DAT_00e2b04c) * fVar14 * fVar14 *
                     *(float*)(thisContext + 0x4c);
            fVar14 = DAT_00e2cd54;
          }
          if (DAT_00e2af44 < fVar15) { // Visibility test passed
            loopCounter--;
            FUN_0050a810((int*)(thisContext + 0x10), piVar1, fVar15);
            iVar8 = *(int*)(iVar7 + 8);
            iVar9 = *piVar1;
            fVar15 = *(float*)(iVar9 + uVar13 * 4 + iVar8);
            if ((*(uint*)(*(int*)(thisContext + 0x10) + 0x108) & 0x20000000) != 0) {
              fVar15 = fVar15 - (*(float*)(iVar12 + iVar9 + 0x58 + iVar8) - DAT_00e2b1a4) *
                                *(float*)(*(int*)(thisContext + 0x14) + 0xc);
            }
            fVar2 = *(float*)(iVar12 + iVar9 + 0x6c + iVar8);
            iVar8 = iVar12 + iVar9 + iVar8;
            if (fVar2 <= fVar15) {
              fVar15 = fVar2;
            }
            iVar12 = *(int*)(thisContext + 0x14);
            fVar2 = *(float*)(iVar12 + 0x88);
            fVar3 = *(float*)(iVar12 + 0x8c);
            local_148 = *(float*)(iVar12 + 0x70) * fVar15;
            fVar15 = *(float*)(iVar12 + 0x74) * fVar15;
            if ((uVar11 & 0x80) == 0) {
              local_148 = (float)(int)((local_148 - (float)(int)local_148) *
                                      *(float*)(iVar12 + 0x80)) * fVar2;
              fVar15 = (float)(int)((fVar15 - (float)(int)fVar15) * *(float*)(iVar12 + 0x84)) *
                       fVar3;
            }
            bVar6 = *(byte*)(iVar8 + 0x5c);
            uVar4 = *(undefined4*)(iVar8 + 0x40);
            *dstBuffer = *(undefined4*)(iVar8 + 0x20);
            dstBuffer[1] = *(undefined4*)(iVar8 + 0x24);
            dstBuffer[2] = *(undefined4*)(iVar8 + 0x28);
            dstBuffer[3] = uVar4;
            dstBuffer[4] = local_f0;
            dstBuffer[5] = local_ec;
            dstBuffer[6] = local_e8;
            uVar11 = (bVar6 & 0xffffff80) << 0x18;
            uVar13 = (uint)fVar2 | uVar11;
            dstBuffer[7] = local_e4;
            dstBuffer[8] = (uint)local_148 | uVar11;
            dstBuffer[9] = fVar15;
            dstBuffer[10] = uVar13;
            dstBuffer[0xb] = fVar3;
            if (bForceUpdate) {
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
              dstBuffer[0x19] = local_fc;
              dstBuffer[0x1a] = local_f8;
              dstBuffer[0x1b] = local_f4;
              dstBuffer = dstBuffer + 0x1c;
            } else {
              FUN_0050a940(piVar1);
              dstBuffer[0xc] = uVar13;
              cVar5 = *(char*)(*(int*)(thisContext + 0x10) + 0x157);
              dstBuffer[0xd] = (float)(int)cVar5 + fVar14;
              uVar13 = 0x21 >> (cVar5 * '\x04' & 0x1fU) & 0xf;
              dstBuffer[0xe] = (float)uVar13 + fVar14;
              dstBuffer[0xf] = (float)(0x21 >> ((char)uVar13 * '\x04' & 0x1fU) & 0xf) + fVar14;
              dstBuffer = dstBuffer + 0x10;
            }
          }
        }
        currentIndex++;
        if ((int)*(short*)(thisContext + 0x6e) <= (int)currentIndex) {
          currentIndex -= (int)*(short*)(thisContext + 0x6e);
        }
      } while (loopCounter != 0);
    }
    if (0 < loopCounter) {
      _memset(dstBuffer, 0, loopCounter * ((-(uint)bForceUpdate & 0x30) + 0x40));
    }
    FUN_0060cde0();
    FUN_00537230();
  }

  // Cleanup audio channels?
  if (*DAT_0121b0ac != 0) {
    uVar13 = *DAT_0121b0ac & 0xff;
    if ((&DAT_011eb8fc)[DAT_0121a394 * 0x10] != '\0') {
      uVar13 += 0x10;
    }
    FUN_00618d40();
    (&DAT_011d912c)[uVar13] = 0;
  }
  if (DAT_0121b0ac[1] != 0) {
    uVar13 = DAT_0121b0ac[1] & 0xff;
    if ((&DAT_011eb8fc)[DAT_0121a394 * 0x10] != '\0') {
      uVar13 += 0x10;
    }
    FUN_00618d40();
    (&DAT_011d912c)[uVar13] = 0;
  }
  if (((*(uint*)(*(int*)(thisContext + 0x10) + 0x104) & 0x100) != 0) && (DAT_0121b0ac[3] != 0)) {
    uVar13 = DAT_0121b0ac[3] & 0xff;
    if ((&DAT_011eb8fc)[DAT_0121a394 * 0x10] != '\0') {
      uVar13 += 0x10;
    }
    FUN_00618d40();
    (&DAT_011d912c)[uVar13] = 0;
  }

  if (*(int*)(thisContext + 0x58) != 0) {
    FUN_005379d0(0, 0);
  }

  // Reset global render state
  DAT_012058e8 = (undefined4*)0x0;
  DAT_0121a390 = 0;
  DAT_0121a394 = 0;

  // Restore z-buffer constants
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

  FUN_00417cf0(1, 5, 6); // Set some final state
  return 1;
}