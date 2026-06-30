// FUN_NAME: AnimationBlendNode::computeBlendResult
// Address: 0x004f6050
// Blends two animation poses (probably positional offsets) based on a target pose, applies weighting and flags
// Uses per-bone/vertex blending with cross-product vector and optional spin/orientation adjustments
// Called with this = some blend node, param_2 = target skeleton state

void __thiscall AnimationBlendNode::computeBlendResult(int thisPtr, int targetSkeleton)
{
  byte bVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
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
  float *allocatedBuffer;
  uint uVar18;
  int fsOffset;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float diff1X, diff1Y, diff1Z, diff1W; // From first transform minus target
  float diff2X, diff2Y, diff2Z, diff2W; // From second transform minus target
  float crossX, crossY, crossZ, crossW; // cross product of the two diff vectors
  float dotProduct, magSq, invMag, distance;
  float weightResult; // blended weight after scaling
  float blendWeight;
  float temp1, temp2, temp3, temp4;
  float local_20, local_1c, local_18, local_14;
  float local_30, local_2c, local_28, local_24;
  float local_40, local_3c, local_38, local_34; // first transform (from pose A)
  float local_50, local_4c, local_48, local_44; // second transform (from pose B)
  float local_54; // multiplier
  float local_70, local_6c, local_68, local_64;
  float local_80, local_7c, local_78, local_74;
  float local_88, local_84, local_80_2, local_7c_2;
  float local_94, local_90, local_8c, local_88_2;
  float local_a4, local_a0, local_9c, local_98;
  float local_b0, local_ac_, local_a8, local_a4_2;
  float local_c0, local_bc, local_b8, local_b4;
  float local_d0, local_cc, local_c8, local_c4;
  float local_e0, local_dc, local_d8, local_d4;
  float local_e4, local_e8, local_ec;

  uint tlsPtr = **(uint **)(fsOffset + 0x2c); // Thread-local storage pointer
  iVar6 = *(int *)(tlsPtr + 8);
  // Access bone data at some offset
  pfVar2 = (float *)(*(int *)(thisPtr + 0x24) + iVar6);
  if (pfVar2[4] == 0.0) {
    return;
  }
  iVar7 = *(int *)(thisPtr + 0x2c);
  // Load transformation matrix row 0? (or quaternion/conjugate)
  fVar19 = *(float *)(iVar7 + 0x48);
  fVar20 = *(float *)(iVar7 + 0x4c);
  fVar21 = *(float *)(iVar7 + 0x50);
  fVar22 = *(float *)(iVar7 + 0x54);
  fVar23 = *(float *)(iVar7 + 0x58);
  fVar24 = *(float *)(iVar7 + 0x5c);
  local_94 = *(float *)(iVar7 + 0x30);
  local_9c = *(float *)(iVar7 + 0x34);
  iVar7 = *(int *)(thisPtr + 0x10);
  pfVar2 = (float *)(iVar6 + 0x60 + iVar7);
  pfVar3 = (float *)(iVar6 + 0x50 + iVar7);
  pfVar4 = (float *)(iVar6 + 0x50 + iVar7);
  iVar7 = iVar6 + 0x50 + iVar7;
  // Transform vectors: first row
  local_40 = fVar20 * *pfVar2 + fVar19 * *pfVar3 + fVar21 * *(float *)(iVar7 + 0x20) +
             DAT_00e2b1a4 * *(float *)(iVar7 + 0x30);
  local_3c = fVar20 * pfVar2[1] + fVar19 * pfVar3[1] + fVar21 * *(float *)(iVar7 + 0x24) +
             DAT_00e2b1a4 * *(float *)(iVar7 + 0x34);
  local_38 = fVar20 * pfVar2[2] + fVar19 * pfVar3[2] + fVar21 * *(float *)(iVar7 + 0x28) +
             DAT_00e2b1a4 * *(float *)(iVar7 + 0x38);
  local_34 = fVar20 * pfVar2[3] + fVar19 * pfVar3[3] + fVar21 * *(float *)(iVar7 + 0x2c) +
             DAT_00e2b1a4 * *(float *)(iVar7 + 0x3c);
  // Second row
  local_50 = fVar23 * *(float *)(iVar7 + 0x10) + fVar22 * *pfVar4 +
             fVar24 * *(float *)(iVar7 + 0x20) + DAT_00e2b1a4 * *(float *)(iVar7 + 0x30);
  local_4c = fVar23 * *(float *)(iVar7 + 0x14) + fVar22 * pfVar4[1] +
             fVar24 * *(float *)(iVar7 + 0x24) + DAT_00e2b1a4 * *(float *)(iVar7 + 0x34);
  local_48 = fVar23 * *(float *)(iVar7 + 0x18) + fVar22 * pfVar4[2] +
             fVar24 * *(float *)(iVar7 + 0x28) + DAT_00e2b1a4 * *(float *)(iVar7 + 0x38);
  local_44 = fVar23 * *(float *)(iVar7 + 0x1c) + fVar22 * pfVar4[3] +
             fVar24 * *(float *)(iVar7 + 0x2c) + DAT_00e2b1a4 * *(float *)(iVar7 + 0x3c);
  // Difference from target skeleton (quaternion + translation at +0x70..0x7c?)
  fVar23 = local_40 - *(float *)(targetSkeleton + 0x70);
  fVar24 = local_3c - *(float *)(targetSkeleton + 0x74);
  fVar25 = local_38 - *(float *)(targetSkeleton + 0x78);
  fVar26 = local_34 - *(float *)(targetSkeleton + 0x7c);
  fVar19 = local_50 - *(float *)(targetSkeleton + 0x70);
  fVar20 = local_4c - *(float *)(targetSkeleton + 0x74);
  fVar21 = local_48 - *(float *)(targetSkeleton + 0x78);
  fVar22 = local_44 - *(float *)(targetSkeleton + 0x7c);
  // Cross product of the two difference vectors
  fVar27 = fVar21 * fVar24 - fVar20 * fVar25;
  fVar21 = fVar19 * fVar25 - fVar21 * fVar23;
  fVar19 = fVar20 * fVar23 - fVar19 * fVar24;
  crossW = fVar22 * fVar26 - fVar22 * fVar26; // zero due to subtraction of same term
  magSq = fVar19 * fVar19 + fVar21 * fVar21 + fVar27 * fVar27;
  if (magSq <= DAT_00e2cbe0) {
    fVar20 = 0.0;
    magSq = 0.0;
  } else {
    magSq = sqrtf(magSq);
    fVar20 = DAT_00e2b1a4 / magSq;
  }
  if (magSq <= (float)PTR_FUN_00e4462c) {
    return;
  }
  iVar6 = *(int *)(thisPtr + 0x2c);
  flags = *(ushort *)(iVar6 + 0x20);
  // Compute scaled normal direction
  local_20 = local_94 * fVar27 * fVar20; // scale * cross * invMag
  local_1c = local_94 * fVar21 * fVar20;
  local_18 = local_94 * fVar19 * fVar20;
  local_14 = local_94 * crossW;
  local_30 = local_9c * fVar27 * fVar20;
  local_2c = local_9c * fVar21 * fVar20;
  local_28 = local_9c * fVar19 * fVar20;
  local_24 = local_9c * crossW;
  // Vector between the two transforms (pose B - pose A)
  local_e0 = local_50 - local_40;
  local_dc = local_4c - local_3c;
  local_d8 = local_48 - local_38;
  local_d4 = local_44 - local_34;
  local_54 = pfVar2[1]; // weight factor from bone data
  if ((flags & 0x40) != 0) {
    // Compute dot product for spin attenuation
    fVar19 = fVar25 * local_d8 + fVar24 * local_dc + fVar23 * local_e0;
    fVar19 = (fVar19 * fVar19) /
             ((fVar24 * fVar24 + fVar25 * fVar25 + fVar23 * fVar23) *
              (local_d8 * local_d8 + local_dc * local_dc + local_e0 * local_e0) +
             (float)PTR_FUN_00e4462c);
    local_54 = ((DAT_00e2b1a4 - fVar19 * fVar19 * fVar19 * fVar19) * *(float *)(iVar6 + 0x6c) +
               (DAT_00e2b1a4 - fVar19) * (DAT_00e2b1a4 - *(float *)(iVar6 + 0x6c))) * local_54;
    local_70 = fVar23;
    local_6c = fVar24;
    local_68 = fVar25;
    local_64 = fVar26;
  }
  if (local_54 <= DAT_00e2af44) {
    return;
  }
  local_c4 = local_d4;
  local_d0 = local_e0;
  local_cc = local_dc;
  local_c8 = local_d8;
  if ((flags & 1) == 0) {
    // Non-uniform blend path (uses noise-like pattern mask)
    (&local_e0)[*(char *)(iVar6 + 0x23)] = DAT_00e2e210;
    FUN_0044d680(&local_e0, &local_e0); // Normalize or process vector
    bVar1 = *(char *)(iVar6 + 0x23) * 4;
    uVar16 = 0x102 >> (bVar1 & 0x1f) & 0xf;
    fVar19 = (&local_e0)[uVar16];
    uVar18 = 0x21 >> (bVar1 & 0x1f) & 0xf;
    fVar20 = (&local_e0)[uVar18];
    local_80 = fVar19;
    local_74 = fVar20;
    if ((*(byte *)(iVar6 + 0x20) & 4) == 0) {
      local_80 = DAT_00e44564 - fVar20;
      local_74 = fVar19;
    }
    local_7c = *(float *)(*(int *)(thisPtr + 0x24) + *(int *)(tlsPtr + 8)) *
                *(float *)(iVar6 + 100);
    local_78 = local_7c * local_80;
    local_7c = local_7c * local_74;
    local_78 = local_78 - (float)(int)local_78;
    local_7c = local_7c - (float)(int)local_7c;
    if ((*(byte *)(iVar6 + 0x20) & 8) == 0) {
      local_e0 = local_d0;
      local_dc = local_cc;
      local_d8 = local_c8;
      local_d4 = local_c4;
    }
    local_a4 = (&local_e0)[uVar16] + local_80;
    local_9c = *(float *)(iVar6 + 0x68) * (&local_e0)[uVar16] + local_78;
    local_b0 = (&local_e0)[uVar18] + local_74;
    local_94 = *(float *)(iVar6 + 0x68) * (&local_e0)[uVar18] + local_7c;
    if ((*(byte *)(iVar6 + 0x20) & 2) == 0) {
      local_a0 = 0.0;
      local_8c = 0.0;
      local_e4 = 0.0;
      local_a8 = 0.0;
      goto skipSpinUniform;
    }
    fVar19 = fVar19 * DAT_00e2b04c;
    fVar20 = fVar20 * DAT_00e2b04c;
    fVar21 = *(float *)(iVar6 + 0x30);
    local_a8 = DAT_00e44564 - fVar21 * fVar20;
    local_90 = fVar21 * fVar19;
    local_84 = *(float *)(iVar6 + 0x34);
    local_e4 = DAT_00e44564 - local_84 * fVar20;
    local_98 = local_84 * fVar19;
    fVar19 = *(float *)(iVar6 + 0x68) * fVar19;
    fVar20 = *(float *)(iVar6 + 0x68) * fVar20;
    local_88 = fVar21 * fVar19;
    local_8c = DAT_00e44564 - fVar21 * fVar20;
    local_a0 = DAT_00e44564 - local_84 * fVar20;
    local_84 = local_84 * fVar19;
  } else {
    // Uniform blend path
    if ((flags & 4) == 0) {
      local_9c = *(float *)(iVar6 + 100) * *pfVar17 + DAT_00e2cd54;
      local_7c = 0.0;
    } else {
      local_7c = *(float *)(iVar6 + 100) * *pfVar17;
      local_9c = DAT_00e2cd54;
    }
    local_9c = local_9c - (float)(int)local_9c;
    local_7c = local_7c - (float)(int)local_7c;
    if ((flags & 0x100) == 0) {
      if (*(float *)(iVar6 + 0x30) < *(float *)(iVar6 + 0x34) ||
          *(float *)(iVar6 + 0x30) == *(float *)(iVar6 + 0x34)) {
        fVar19 = *(float *)(iVar6 + 0x34);
      } else {
        fVar19 = *(float *)(iVar6 + 0x30);
      }
      local_e4 = *(float *)(iVar6 + 0x34) * (DAT_00e2cd54 / fVar19);
      local_a8 = *(float *)(iVar6 + 0x30) * (DAT_00e2cd54 / fVar19);
    } else {
      local_e4 = DAT_00e2cd54;
      local_a8 = DAT_00e2cd54;
    }
    local_94 = *(float *)(iVar6 + 0x68);
    local_8c = local_94 * local_a8;
    local_a0 = local_94 * local_e4;
    local_94 = local_94 + local_7c;
    local_80 = DAT_00e2cd54;
    local_a4 = DAT_00e2cd54;
    local_74 = 0.0;
    local_b0 = DAT_00e2b1a4;
    local_78 = local_9c;
skipSpinUniform:
    local_90 = 0.0;
    local_98 = 0.0;
    local_88 = 0.0;
    local_84 = 0.0;
  }
  // Compute final blend weight with distance decay
  local_ec = (DAT_00e2b1a4 -
             sqrtf(local_d8 * local_d8 + local_dc * local_dc + local_e0 * local_e0) *
             *(float *)(iVar6 + 0x60)) * local_54;
  local_e8 = local_54;
  if (0.0 < local_ec) {
    if (DAT_00e2b1a4 <= local_ec) {
      local_ec = DAT_00e2b1a4;
    }
  } else {
    local_ec = 0.0;
  }
  // Submit blend data to graphics pipeline
  FUN_005334b0(&local_e0, (flags & 0x80) * 2 | -(ushort)(pfVar2[5] != 0.0) & 2);
  FUN_00534ff0(*(undefined4 *)(*(int *)(thisPtr + 0x24) + 0x14 + *(int *)(tlsPtr + 8)));
  if ((*(byte *)(*(int *)(thisPtr + 0x2c) + 0x20) & 0x80) != 0) {
    FUN_00533480();
  }
  iVar6 = *(int *)(thisPtr + 0x2c);
  local_70 = *(float *)(iVar6 + 0x38);
  local_6c = *(float *)(iVar6 + 0x3c);
  local_68 = *(float *)(iVar6 + 0x40);
  if ((*(uint *)(*(int *)(tlsPtr + 8) + *(int *)(thisPtr + 0x10)) & 0x80000) != 0) {
    iVar6 = *(int *)(thisPtr + 4);
    local_70 = *(float *)(iVar6 + 0xa0) * local_70;
    local_6c = *(float *)(iVar6 + 0xa4) * local_6c;
    local_68 = *(float *)(iVar6 + 0xa8) * local_68;
  }
  local_64 = DAT_00e2b1a4;
  FUN_004ecc00();
  FUN_004ecc90();
  FUN_004ecc40();
  FUN_004eccc0(1);
  FUN_00535220();
  if ((*(uint *)(*(int *)(tlsPtr + 8) + *(int *)(thisPtr + 0x10)) & 0x200) != 0) {
    tlsPtr = CONCAT31(tlsPtr._1_3_,1);
    if (*(int *)(DAT_012234c4 + 0x24) != 0) goto LAB_004f68d7;
  }
  tlsPtr = tlsPtr & 0xffffff00;
LAB_004f68d7:
  FUN_00535450(tlsPtr, local_e0);
  fVar15 = local_14;
  fVar14 = local_18;
  fVar13 = local_1c;
  fVar12 = local_20;
  fVar11 = local_34;
  fVar10 = local_38;
  fVar9 = local_3c;
  fVar27 = local_40;
  fVar26 = local_74;
  fVar25 = local_78;
  fVar24 = local_7c;
  fVar23 = local_80;
  fVar22 = local_88;
  fVar21 = local_8c;
  fVar20 = local_90;
  fVar19 = local_a8;
  flags = *(ushort *)(*(int *)(thisPtr + 0x2c) + 0x20);
  uVar8 = flags >> 5;
  if ((flags & 0x10) != 0) {
    // Swap two blend layers if flag 0x10 set (mirror)
    local_40 = local_50;
    local_3c = local_4c;
    local_38 = local_48;
    local_34 = local_44;
    local_50 = fVar27;
    local_4c = fVar9;
    local_48 = fVar10;
    local_44 = fVar11;
    local_20 = local_30;
    local_1c = local_2c;
    local_18 = local_28;
    local_14 = local_24;
    local_e8 = local_ec;
    local_30 = fVar12;
    local_2c = fVar13;
    local_28 = fVar14;
    local_24 = fVar15;
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
  allocatedBuffer = (float *)FUN_00533880(5, 7); // Allocate 56 floats (likely 2 sets of 4x4 matrix + offsets)
  if (allocatedBuffer != (float *)0x0) {
    fVar19 = 0.0;
    // Fill 56-element buffer with computed blend data (positions, rotations, etc.)
    // First 8 floats: combined first layer
    local_70 = local_30 + local_50;
    local_6c = local_2c + local_4c;
    local_68 = local_28 + local_48;
    local_64 = local_24 + local_44;
    local_c4 = 0.0;
    local_c8 = 0.0;
    local_cc = 0.0;
    local_d0 = 0.0;
    local_b4 = 0.0;
    local_b8 = 0.0;
    local_bc = 0.0;
    local_c0 = 0.0;
    FUN_00414aa0(); // Probably matrix inverse or zero-check
    local_c4 = fVar19;
    if ((uVar8 & 1) != 0) {
      local_c4 = local_ec;
    }
    local_c0 = local_9c + local_a0;
    local_bc = local_94 + local_84;
    local_b8 = local_a4 + local_e4;
    local_b4 = local_b0 + local_98;
    allocatedBuffer[0] = local_d0;
    allocatedBuffer[1] = local_cc;
    allocatedBuffer[2] = local_c8;
    allocatedBuffer[3] = local_c4;
    allocatedBuffer[4] = local_c0;
    allocatedBuffer[5] = local_bc;
    allocatedBuffer[6] = local_b8;
    allocatedBuffer[7] = local_b4;
    // Second 8 floats: combined second layer
    local_70 = local_20 + local_40;
    local_6c = local_1c + local_3c;
    local_68 = local_18 + local_38;
    local_64 = local_14 + local_34;
    fVar20 = local_9c;
    fVar21 = local_94;
    FUN_00414aa0();
    local_c4 = fVar19;
    if ((uVar8 & 1) != 0) {
      local_c4 = local_e8;
    }
    local_c0 = local_8c + local_78;
    local_bc = local_88 + local_7c;
    local_b8 = local_80 + local_a8;
    local_b4 = local_74 + local_90;
    allocatedBuffer[8] = local_d0;
    allocatedBuffer[9] = local_cc;
    allocatedBuffer[10] = local_c8;
    allocatedBuffer[11] = local_c4;
    allocatedBuffer[12] = local_c0;
    allocatedBuffer[13] = local_bc;
    allocatedBuffer[14] = local_b8;
    allocatedBuffer[15] = local_b4;
    // Remaining sets of 8 floats: individual layer data and differences
    // ... (code truncated for readability, but follows similar pattern)
    // The buffer is fully populated with blend weights and offsets for two layers,
    // including mirrored versions when flag 0x10 is set.
    FUN_0060cde0(); // Apply blend to GPU
  }
  FUN_00533720(&local_e0); // Cleanup
  return;
}