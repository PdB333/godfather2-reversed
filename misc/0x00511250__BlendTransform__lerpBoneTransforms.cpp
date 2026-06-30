// FUNC_NAME: BlendTransform::lerpBoneTransforms
void __thiscall lerpBoneTransforms(int thisObj, int *param2, int param3)
{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int iVar14;
  uint uVar15;
  byte *pbVar16;
  float *pfVar17;
  int iVar18;
  float *pfVar19;
  uint uVar20;
  int unaff_EDI;
  int unaff_FS_OFFSET;
  float in_XMM0_Da;
  float fVar21;
  float fVar22;
  double dVar23;
  undefined4 uVar24;
  float fVar25;
  float local_70 [4];
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 local_50 [76];
  
  iVar4 = **(int **)(unaff_FS_OFFSET + 0x2c); // get FS segment base for TLS
  // compute index into blend buffer: param3 * 0x50 + *param2 + TLS offset
  iVar14 = param3 * 0x50 + *param2 + *(int *)(iVar4 + 8);
  FUN_00414aa0(); // probably getFrameTime or similar
  uStack_54 = DAT_00e2b1a4; // global constant
  uVar24 = DAT_00e2b1a4;
  FUN_00414aa0();
  piVar1 = (int *)(thisObj + 0x10);
  local_70[3] = (float)uVar24;
  FUN_0050a940(param2); // clamp or normalize
  iVar18 = *piVar1; // skeleton pointer? +0x10
  if ((*(uint *)(iVar18 + 0x108) & 0x4000) == 0) { // check if blending is disabled
    iVar14 = (int)*(char *)(iVar18 + 0x157); // get bone index from skeleton
    uVar15 = 0x21 >> (*(char *)(iVar18 + 0x157) * '\\x04' & 0x1fU) & 0xf; // bit extraction for sibling/child
    uVar20 = 0x21 >> ((char)uVar15 * '\\x04' & 0x1fU) & 0xf;
    if ((*(byte *)(iVar18 + 0x104) & 2) == 0) { // no additive blend flag
      local_70[iVar14] = in_XMM0_Da; // store weight
      local_70[uVar15] = 0.0;
      local_70[uVar20] = 0.0;
      FUN_0056b8a0(local_70[1],local_70[0],local_70[2]); // blend weight normalization
    }
    else { // additive blend case
      dVar23 = (double)in_XMM0_Da;
      FUN_00b99fcb(); // sin/cos or slerp helper
      fVar21 = (float)dVar23;
      dVar23 = (double)in_XMM0_Da;
      FUN_00b99e20(); // another trig helper
      fVar25 = (float)dVar23;
      // compute indices into blend matrix buffer at thisObj+8
      puVar2 = (undefined4 *)((iVar14 + 5) * 0x10 + *(int *)(thisObj + 8) + *(int *)(iVar4 + 8));
      uVar24 = puVar2[1];
      uVar12 = puVar2[2];
      uVar13 = puVar2[3];
      puVar3 = (undefined4 *)(iVar14 * 0x10 + unaff_EDI); // output matrix
      *puVar3 = *puVar2;
      puVar3[1] = uVar24;
      puVar3[2] = uVar12;
      puVar3[3] = uVar13;
      iVar14 = (uVar20 + 5) * 0x10;
      pfVar17 = (float *)(*(int *)(thisObj + 8) + iVar14 + *(int *)(iVar4 + 8));
      fVar5 = *pfVar17;
      fVar6 = pfVar17[1];
      fVar7 = pfVar17[2];
      fVar8 = pfVar17[3];
      pfVar17 = (float *)(uVar15 * 0x10 + unaff_EDI);
      *pfVar17 = fVar21 * fVar5;
      pfVar17[1] = fVar21 * fVar6;
      pfVar17[2] = fVar21 * fVar7;
      pfVar17[3] = fVar21 * fVar8;
      fVar22 = DAT_00e44564; // global constant (maybe 1.0f)
      iVar18 = (uVar15 + 5) * 0x10;
      pfVar19 = (float *)(*(int *)(thisObj + 8) + iVar18 + *(int *)(iVar4 + 8));
      fVar9 = pfVar19[1];
      fVar10 = pfVar19[2];
      fVar11 = pfVar19[3];
      *pfVar17 = *pfVar19 * fVar25 + fVar21 * fVar5;
      pfVar17[1] = fVar9 * fVar25 + fVar21 * fVar6;
      pfVar17[2] = fVar10 * fVar25 + fVar21 * fVar7;
      pfVar17[3] = fVar11 * fVar25 + fVar21 * fVar8;
      pfVar17 = (float *)(*(int *)(thisObj + 8) + iVar14 + *(int *)(iVar4 + 8));
      fVar5 = *pfVar17;
      fVar6 = pfVar17[1];
      fVar7 = pfVar17[2];
      fVar8 = pfVar17[3];
      pfVar19 = (float *)(uVar20 * 0x10 + unaff_EDI);
      *pfVar19 = fVar5 * fVar25;
      pfVar19[1] = fVar6 * fVar25;
      pfVar19[2] = fVar7 * fVar25;
      pfVar19[3] = fVar8 * fVar25;
      fVar22 = fVar22 - fVar21;
      pfVar17 = (float *)(*(int *)(thisObj + 8) + iVar18 + *(int *)(iVar4 + 8));
      fVar9 = pfVar17[1];
      fVar10 = pfVar17[2];
      fVar11 = pfVar17[3];
      *pfVar19 = fVar22 * *pfVar17 + fVar5 * fVar25;
      pfVar19[1] = fVar22 * fVar9 + fVar6 * fVar25;
      pfVar19[2] = fVar22 * fVar10 + fVar7 * fVar25;
      pfVar19[3] = fVar22 * fVar11 + fVar8 * fVar25;
    }
  }
  else { // lerp mode (bit 0x4000 set)
    local_70[0] = (*(float *)(iVar14 + 0x30) - local_70[0]) * _DAT_00e2e084 + local_70[0];
    local_70[1] = (*(float *)(iVar14 + 0x34) - local_70[1]) * _DAT_00e2e084 + local_70[1];
    local_70[2] = (*(float *)(iVar14 + 0x38) - local_70[2]) * _DAT_00e2e084 + local_70[2];
    FUN_0050fe90(piVar1,in_XMM0_Da); // update blend weights
  }
  if ((*(char *)(thisObj + 0x70) == '\\x04') && // check for specific blend type
     (pbVar16 = (byte *)(*(int *)(iVar4 + 8) + *(int *)(thisObj + 8)), (*pbVar16 & 4) != 0)) {
    FUN_0056b420(pbVar16 + 0x50,&local_60,unaff_EDI + 0x30); // copy with offset
  }
  else {
    *(undefined4 *)(unaff_EDI + 0x30) = local_60;
    *(undefined4 *)(unaff_EDI + 0x34) = uStack_5c;
    *(undefined4 *)(unaff_EDI + 0x38) = uStack_58;
    *(undefined4 *)(unaff_EDI + 0x3c) = uStack_54;
  }
  if ((*(uint *)(*piVar1 + 0x10c) & 0x180000) != 0) {
    FUN_004e9fa0(); // accumulate blending
    FUN_004eb6a0(unaff_EDI + 0x30,*(uint *)(*piVar1 + 0x10c) >> 0x14 & 0xffffff01);
    FUN_0056b230(local_50); // finalize blend
    *(undefined4 *)(unaff_EDI + 0xc) = 0;
    *(undefined4 *)(unaff_EDI + 0x1c) = 0;
    *(undefined4 *)(unaff_EDI + 0x2c) = 0;
  }
  return;
}