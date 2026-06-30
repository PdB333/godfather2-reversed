// FUNC_NAME: SkeletonAnimation::blendBoneMatrices
void SkeletonAnimation::blendBoneMatrices(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  ushort uVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  float *pfVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  bool bVar19;
  bool bVar20;
  float fVar21;
  int in_EAX;
  int *piVar22;
  int *piVar23;
  int *piVar24;
  uint uVar25;
  int iVar26;
  int iVar27;
  float *pfVar28;
  int iVar29;
  float *pfVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  int *local_264;
  int local_260;
  float *local_250;
  float *local_248;
  float *local_244;
  int *local_238;
  int local_230;
  int local_214;
  char *local_20c;
  float *local_208;
  float *local_204;
  int local_1b0;
  float local_100;
  float fStack_fc;
  float fStack_f8;
  float fStack_f4;
  float local_d0 [4];
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  float local_b4;
  float local_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  float local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  float local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  float fStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  float fStack_54;
  
  fVar21 = DAT_00e2b1a4;
  iVar27 = *(int *)(param_1 + 0x70); // skeleton data pointer
  if ((((iVar27 == 0) || (*(int *)(iVar27 + 0x18) < 1)) || (*(int *)(iVar27 + 0x1c) == 0)) ||
     ((sVar5 = *(short *)(param_1 + 0x76), sVar5 < 0 || (*(int *)(iVar27 + 0x18) <= (int)sVar5)))) {
    iVar27 = 0;
  }
  else {
    iVar27 = *(int *)(iVar27 + 0x1c) + sVar5 * 0x18; // bone data offset
  }
  iVar29 = *(int *)(in_EAX + 0x3c); // animation data
  piVar7 = *(int **)(iVar27 + 0xc); // bone index list
  local_a0 = DAT_00e2b1a4;
  uStack_9c = 0;
  uStack_98 = 0;
  uStack_94 = 0;
  fVar33 = *(float *)(param_1 + 0x104); // blend weight
  fVar31 = *(float *)(iVar29 + 0x10) * fVar33; // scale x
  fVar32 = *(float *)(iVar29 + 0x14) * fVar33; // scale y
  local_208 = (float *)(*(int *)(in_EAX + 0x38) + 0x30); // output bone matrices
  local_204 = (float *)(iVar29 + 0x20); // animation translation
  local_20c = (char *)(*(int *)(in_EAX + 0x34) + 0x15); // bone flags
  uVar8 = *(uint *)(iVar27 + 8); // bone count
  fVar33 = *(float *)(iVar29 + 0x18) * fVar33; // scale z
  iVar29 = uVar8 * 2;
  if (*(int *)(param_1 + 0xb4) != 0) {
    iVar29 = 0;
    local_248 = (float *)uVar8;
    if (0 < (int)uVar8) {
      do {
        uVar25 = (uint)*(byte *)(*(int *)(param_1 + 0xb4) + iVar29);
        if ((uVar25 != 0xff) && ((int)local_248 < (int)uVar25)) {
          local_248 = (float *)uVar25;
        }
        iVar29 = iVar29 + 1;
      } while (iVar29 < (int)uVar8);
    }
    iVar29 = (int)local_248 * 2 + 2;
  }
  iVar29 = ((iVar29 + 1) * 0x10) / 0xc;
  piVar22 = (int *)FUN_0056ef10(iVar29); // allocate temporary matrix
  DAT_0120557c = piVar22 + 4;
  piVar23 = (int *)FUN_0056ef10(iVar29); // allocate temporary matrix
  piVar24 = (int *)FUN_0056ef10(iVar29); // allocate temporary matrix
  local_d0[2] = 0.0;
  local_d0[1] = 0.0;
  local_d0[0] = 0.0;
  local_d0[3] = DAT_00e2b1a4;
  local_b8 = 0;
  local_bc = 0;
  local_c0 = 0;
  local_b4 = DAT_00e2b1a4;
  iVar29 = *(int *)(*(int *)(in_EAX + 0x38) + 0xc); // bone count from skeleton
  local_1b0 = 0;
  bVar20 = false;
  local_230 = 1;
  if (1 < *(int *)(iVar27 + 8)) {
    local_248 = (float *)(piVar24 + 0x14);
    iVar26 = (int)DAT_0120557c - (int)(piVar24 + 4);
    fVar35 = DAT_00e2b04c;
    do {
      local_238 = piVar7 + 4;
      iVar9 = *(int *)(param_1 + 0xb4);
      if ((iVar9 == 0) || (*(byte *)(iVar9 + local_230) == 0xff)) {
        pfVar30 = (float *)(iVar26 + (int)local_248);
      }
      else {
        pfVar30 = (float *)((uint)*(byte *)(iVar9 + local_230) * 0x40 + *(int *)(param_1 + 0xb8));
      }
      pfVar28 = local_248;
      if ((iVar9 != 0) && (*(byte *)(iVar9 + local_230) != 0xff)) {
        pfVar28 = (float *)(piVar23 + (uint)*(byte *)(iVar9 + local_230) * 0x10 + 4);
      }
      iVar10 = *local_238;
      if (iVar10 == 0) {
        local_244 = (float *)(piVar22 + 4);
        *local_244 = fVar31;
        piVar22[5] = 0;
        piVar22[6] = 0;
        piVar22[7] = 0;
        piVar22[8] = 0;
        piVar22[9] = (int)fVar32;
        piVar22[10] = 0;
        piVar22[0xb] = 0;
        piVar22[0xc] = 0;
        piVar22[0xd] = 0;
        piVar22[0xe] = (int)fVar33;
        piVar22[0xf] = 0;
        piVar22[0x10] = 0;
        piVar22[0x11] = 0;
        piVar22[0x12] = 0;
        piVar22[0x13] = (int)fVar21;
      }
      else if ((iVar9 == 0) || (*(byte *)(iVar10 + iVar9) == 0xff)) {
        local_244 = (float *)(piVar22 + iVar10 * 0x10 + 4);
      }
      else {
        local_244 = (float *)((uint)*(byte *)(iVar10 + iVar9) * 0x40 + *(int *)(param_1 + 0xb8));
      }
      if (*local_238 == 0) {
        piVar24[4] = (int)fVar31;
        piVar24[5] = 0;
        piVar24[6] = 0;
        piVar24[7] = 0;
        piVar24[8] = 0;
        piVar24[9] = (int)fVar32;
        piVar24[10] = 0;
        piVar24[0xb] = 0;
        piVar24[0xc] = 0;
        piVar24[0xd] = 0;
        piVar24[0xe] = (int)fVar33;
        piVar24[0xf] = 0;
        piVar24[0x10] = 0;
        piVar24[0x11] = 0;
        piVar24[0x12] = 0;
        piVar24[0x13] = (int)fVar21;
      }
      local_250 = local_d0;
      iVar9 = piVar7[7];
      if (iVar9 == 2) {
        local_250 = (float *)(piVar7[5] * 0x20 + *(int *)(*(int *)(param_1 + 0x70) + 0x58));
      }
      else if ((local_230 < iVar29) && (*local_20c == '\\x02')) {
        if (iVar9 == 1) {
          local_250 = local_208;
        }
        else if (iVar9 == 3) {
          bVar20 = true;
        }
      }
      bVar19 = false;
      if (*(char *)(param_1 + 0xae) == '\\0') {
LAB_005759e4:
        fVar34 = DAT_00e2b1a4;
        fVar1 = local_250[2];
        fVar2 = *local_250;
        fVar3 = local_250[1];
        fVar4 = local_250[3];
        *pfVar28 = DAT_00e2b1a4 - (fVar3 * fVar3 + fVar1 * fVar1) * fVar35;
        pfVar28[4] = (fVar3 * fVar2 - fVar4 * fVar1) * fVar35;
        pfVar28[1] = (fVar4 * fVar1 + fVar3 * fVar2) * fVar35;
        pfVar28[5] = fVar34 - (fVar2 * fVar2 + fVar1 * fVar1) * fVar35;
        pfVar28[2] = (fVar1 * fVar2 - fVar4 * fVar3) * fVar35;
        pfVar28[3] = 0.0;
        pfVar28[6] = (fVar1 * fVar3 + fVar4 * fVar2) * fVar35;
        pfVar28[7] = 0.0;
        pfVar28[8] = (fVar4 * fVar3 + fVar1 * fVar2) * fVar35;
        pfVar28[9] = (fVar1 * fVar3 - fVar4 * fVar2) * fVar35;
        pfVar28[10] = fVar34 - (fVar3 * fVar3 + fVar2 * fVar2) * fVar35;
        pfVar28[0xb] = 0.0;
        FUN_00414aa0();
        pfVar28[0xf] = fVar34;
        fVar1 = *local_204;
        fVar2 = local_204[1];
        fVar3 = local_204[2];
        fVar4 = pfVar28[1];
        fVar34 = pfVar28[2];
        fVar12 = pfVar28[3];
        *pfVar30 = fVar1 * *pfVar28;
        pfVar30[1] = fVar1 * fVar4;
        pfVar30[2] = fVar1 * fVar34;
        pfVar30[3] = fVar1 * fVar12;
        fVar1 = pfVar28[5];
        fVar4 = pfVar28[6];
        fVar34 = pfVar28[7];
        pfVar30[4] = pfVar28[4] * fVar2;
        pfVar30[5] = fVar1 * fVar2;
        pfVar30[6] = fVar4 * fVar2;
        pfVar30[7] = fVar34 * fVar2;
        fVar1 = pfVar28[9];
        fVar2 = pfVar28[10];
        fVar4 = pfVar28[0xb];
        pfVar30[8] = fVar3 * pfVar28[8];
        pfVar30[9] = fVar3 * fVar1;
        pfVar30[10] = fVar3 * fVar2;
        pfVar30[0xb] = fVar3 * fVar4;
        FUN_00417560();
        FUN_00417560();
        fVar1 = local_250[4];
        fVar2 = local_250[5];
        fVar3 = local_250[6];
        fVar4 = local_250[7];
        fVar34 = local_244[5];
        fVar12 = local_244[6];
        fVar13 = local_244[1];
        fVar14 = local_244[2];
        fVar15 = local_244[9];
        fVar16 = local_244[10];
        fVar17 = local_244[0xd];
        fVar18 = local_244[0xe];
        pfVar30[0xc] = fVar2 * local_244[4] + fVar1 * *local_244 + fVar3 * local_244[8] +
                       fVar4 * local_244[0xc];
        pfVar30[0xd] = fVar2 * fVar34 + fVar1 * fVar13 + fVar3 * fVar15 + fVar4 * fVar17;
        pfVar30[0xe] = fVar2 * fVar12 + fVar1 * fVar14 + fVar3 * fVar16 + fVar4 * fVar18;
      }
      else {
        local_260 = local_1b0 * 0x20;
        local_264 = (int *)(*(int *)(param_1 + 0xa0) + local_260);
        if (*(short *)(param_1 + 0xa8) <= local_1b0) goto LAB_005759e4;
        do {
          if (local_230 != (short)local_264[1]) break;
          uVar6 = *(ushort *)((int)local_264 + 6);
          if ((char)uVar6 < '\\0') {
            bVar19 = true;
            if ((uVar6 & 1) == 0) {
              if ((uVar6 & 0x10) == 0) {
                if ((uVar6 & 0x20) == 0) {
                  if ((uVar6 & 4) == 0) {
                    fVar1 = *local_250;
                    fVar2 = local_250[2];
                    fVar3 = local_250[1];
                    fVar4 = local_250[3];
                    fVar34 = local_250[2];
                    *pfVar30 = DAT_00e2b1a4 - (fVar2 * fVar2 + fVar3 * fVar3) * fVar35;
                    pfVar30[1] = (fVar4 * fVar34 + fVar3 * fVar1) * fVar35;
                    pfVar30[4] = (fVar3 * fVar1 - fVar4 * fVar34) * fVar35;
                    fVar34 = DAT_00e2b1a4;
                    pfVar30[5] = DAT_00e2b1a4 - (fVar2 * fVar2 + fVar1 * fVar1) * fVar35;
                    pfVar30[2] = (fVar2 * fVar1 - fVar4 * fVar3) * fVar35;
                    pfVar30[3] = 0.0;
                    pfVar30[7] = 0.0;
                    pfVar30[0xb] = 0.0;
                    pfVar30[10] = fVar34 - (fVar3 * fVar3 + fVar1 * fVar1) * fVar35;
                    pfVar30[6] = (fVar2 * fVar3 + fVar4 * fVar1) * fVar35;
                    pfVar30[8] = (fVar4 * fVar3 + fVar2 * fVar1) * fVar35;
                    pfVar30[9] = (fVar2 * fVar3 - fVar4 * fVar1) * fVar35;
                    pfVar30[0xe] = 0.0;
                    pfVar30[0xd] = 0.0;
                    pfVar30[0xc] = 0.0;
                    pfVar30[0xf] = fVar34;
                  }
                  else {
                    pfVar11 = (float *)*local_264;
                    fVar1 = *pfVar11;
                    fVar2 = pfVar11[2];
                    fVar3 = pfVar11[1];
                    fVar4 = pfVar11[3];
                    *pfVar30 = DAT_00e2b1a4 - (fVar2 * fVar2 + fVar3 * fVar3) * fVar35;
                    pfVar30[4] = (fVar3 * fVar1 - fVar4 * fVar2) * fVar35;
                    fVar34 = DAT_00e2b1a4;
                    pfVar30[1] = (fVar4 * fVar2 + fVar3 * fVar1) * fVar35;
                    pfVar30[5] = fVar34 - (fVar2 * fVar2 + fVar1 * fVar1) * fVar35;
                    pfVar30[2] = (fVar2 * fVar1 - fVar4 * fVar3) * fVar35;
                    pfVar30[3] = 0.0;
                    pfVar30[7] = 0.0;
                    pfVar30[10] = fVar34 - (fVar3 * fVar3 + fVar1 * fVar1) * fVar35;
                    pfVar30[0xb] = 0.0;
                    pfVar30[6] = (fVar2 * fVar3 + fVar4 * fVar1) * fVar35;
                    pfVar30[8] = (fVar4 * fVar3 + fVar2 * fVar1) * fVar35;
                    pfVar30[9] = (fVar2 * fVar3 - fVar4 * fVar1) * fVar35;
                    pfVar30[0xe] = 0.0;
                    pfVar30[0xd] = 0.0;
                    pfVar30[0xc] = 0.0;
                    pfVar30[0xf] = fVar34;
                    FUN_00414aa0();
                  }
                  if ((*(byte *)((int)local_264 + 6) & 8 | 0x100) == 0) {
                    FUN_00414aa0();
                  }
                  else {
                    FUN_00414aa0();
                  }
                  FUN_00417560();
                  goto LAB_00575998;
                }
                FUN_00574760(pfVar30,local_244);
                fVar35 = DAT_00e2b04c;
              }
              else {
                FUN_00574860(local_244,CONCAT44(*local_264,local_250),local_264[2],uVar6);
                fVar35 = DAT_00e2b04c;
              }
            }
            else {
              fVar1 = local_250[2];
              fVar2 = *local_250;
              fVar3 = local_250[1];
              fVar4 = local_250[3];
              *pfVar28 = DAT_00e2b1a4 - (fVar1 * fVar1 + fVar3 * fVar3) * fVar35;
              pfVar28[1] = (fVar4 * fVar1 + fVar3 * fVar2) * fVar35;
              pfVar28[4] = (fVar3 * fVar2 - fVar4 * fVar1) * fVar35;
              fVar34 = DAT_00e2b1a4;
              pfVar28[5] = DAT_00e2b1a4 - (fVar1 * fVar1 + fVar2 * fVar2) * fVar35;
              pfVar28[2] = (fVar1 * fVar2 - fVar4 * fVar3) * fVar35;
              pfVar28[3] = 0.0;
              pfVar28[6] = (fVar1 * fVar3 + fVar4 * fVar2) * fVar35;
              pfVar28[7] = 0.0;
              pfVar28[8] = (fVar4 * fVar3 + fVar1 * fVar2) * fVar35;
              pfVar28[9] = (fVar1 * fVar3 - fVar4 * fVar2) * fVar35;
              pfVar28[10] = fVar34 - (fVar3 * fVar3 + fVar2 * fVar2) * fVar35;
              pfVar28[0xb] = 0.0;
              FUN_00414aa0();
              pfVar28[0xf] = fVar34;
              fVar1 = *local_204;
              fVar2 = local_204[1];
              fVar3 = local_204[2];
              fVar4 = pfVar28[1];
              fVar34 = pfVar28[2];
              fVar12 = pfVar28[3];
              *pfVar30 = fVar1 * *pfVar28;
              pfVar30[1] = fVar1 * fVar4;
              pfVar30[2] = fVar1 * fVar34;
              pfVar30[3] = fVar1 * fVar12;
              fVar1 = pfVar28[5];
              fVar4 = pfVar28[6];
              fVar34 = pfVar28[7];
              pfVar30[4] = pfVar28[4] * fVar2;
              pfVar30[5] = fVar1 * fVar2;
              pfVar30[6] = fVar4 * fVar2;
              pfVar30[7] = fVar34 * fVar2;
              fVar1 = pfVar28[9];
              fVar2 = pfVar28[10];
              fVar4 = pfVar28[0xb];
              pfVar30[8] = fVar3 * pfVar28[8];
              pfVar30[9] = fVar3 * fVar1;
              pfVar30[10] = fVar3 * fVar2;
              pfVar30[0xb] = fVar3 * fVar4;
              FUN_00417560();
              FUN_00417560();
              fVar1 = local_250[4];
              fVar2 = local_250[5];
              fVar3 = local_250[6];
              fVar4 = local_250[7];
              local_b0 = fVar2 * local_244[4] + fVar1 * *local_244 + fVar3 * local_244[8] +
                         fVar4 * local_244[0xc];
              fStack_ac = fVar2 * local_244[5] + fVar1 * local_244[1] + fVar3 * local_244[9] +
                          fVar4 * local_244[0xd];
              fStack_a8 = fVar2 * local_244[6] + fVar1 * local_244[2] + fVar3 * local_244[10] +
                          fVar4 * local_244[0xe];
              fStack_a4 = fVar2 * local_244[7] + fVar1 * local_244[3] + fVar3 * local_244[0xb] +
                          fVar4 * local_244[0xf];
              pfVar30[0xc] = local_b0;
              pfVar30[0xd] = fStack_ac;
              pfVar30[0xe] = fStack_a8;
              uVar6 = *(ushort *)((int)local_264 + 6);
              if ((uVar6 & 4) == 0) {
                if ((uVar6 & 8) == 0) {
                  if ((uVar6 & 0x100) != 0) {
                    iVar9 = *local_264;
                    fVar1 = *(float *)(iVar9 + 0x10);
                    fVar2 = *(float *)(iVar9 + 0x14);
                    fVar3 = *(float *)(iVar9 + 0x18);
                    local_100 = fVar2 * pfVar28[4] + fVar1 * *pfVar28 + fVar3 * pfVar28[8];
                    fStack_fc = fVar2 * pfVar28[5] + fVar1 * pfVar28[1] + fVar3 * pfVar28[9];
                    fStack_f8 = fVar2 * pfVar28[6] + fVar1 * pfVar28[2] + fVar3 * pfVar28[10];
                    if ((uVar6 & 0x200) != 0) {
                      fVar1 = *(float *)(param_1 + 0x108);
                      local_100 = fVar1 * local_100;
                      fStack_fc = fVar1 * fStack_fc;
                      fStack_f8 = fVar1 * fStack_f8;
                    }
                    fVar1 = pfVar28[0xf];
                    pfVar28[0xc] = local_100 + pfVar28[0xc];
                    pfVar28[0xd] = fStack_fc + pfVar28[0xd];
                    pfVar28[0xe] = fStack_f8 + pfVar28[0xe];
                    pfVar28[0xf] = fStack_f4 + pfVar28[0xf];
                    pfVar28[0xf] = fVar1;
                  }
                }
                else {
                  iVar9 = *local_264;
                  fVar2 = *(float *)(iVar9 + 0x14);
                  fVar3 = *(float *)(iVar9 + 0x18);
                  fVar4 = *(float *)(iVar9 + 0x1c);
                  fVar1 = pfVar30[0xf];
                  pfVar30[0xc] = *(float *)(iVar9 + 0x10) + pfVar30[0xc];
                  pfVar30[0xd] = fVar2 + pfVar30[0xd];
                  pfVar30[0xe] = fVar3 + pfVar30[0xe];
                  pfVar30[0xf] = fVar4 + pfVar30[0xf];
                  pfVar30[0xf] = fVar1;
                  iVar9 = *local_264;
                  fVar2 = *(float *)(iVar9 + 0x14);
                  fVar3 = *(float *)(iVar9 + 0x18);
                  fVar4 = *(float *)(iVar9 + 0x1c);
                  fVar1 = pfVar28[0xf];
                  pfVar28[0xc] = *(float *)(iVar9 + 0x10) + pfVar28[0xc];
                  pfVar28[0xd] = fVar2 + pfVar28[0xd];
                  pfVar28[0xe] = fVar3 + pfVar28[0xe];
                  pfVar28[0xf] = fVar4 + pfVar28[0xf];
                  pfVar28[0xf] = fVar1;
                }
              }
              else {
                if ((uVar6 & 8 | 0x100) != 0) {
                  FUN_00414aa0();
                }
                FUN_00417560();
LAB_00575998:
                FUN_00417560();
              }
            }
          }
          local_260 = local_260 + 0x20;
          local_264 = (int *)(*(int *)(param_1 + 0xa0) + local_260);
          local_1b0 = local_1b0 + 1;
        } while (local_1b0 < *(short *)(param_1 + 0xa8));
        if (!bVar19) goto LAB_005759e4;
      }
      local_20c = local_20c + 1;
      local_208 = local_208 + 8;
      local_248 = local_248 + 0x10;
      local_204 = local_204 + 4;
      local_230 = local_230 + 1;
      piVar7 = local_238;
    } while (local_230 < *(int *)(iVar27 + 8));
  }
  local_214 = 0;
  if (0 < *(short *)(param_1 + 0xaa)) {
    do {
      FUN_00417560();
      local_90 = local_a0;
      uStack_8c = uStack_9c;
      uStack_88 = uStack_98;
      uStack_84 = uStack_94;
      local_80 = uStack_94;
      fStack_7c = local_a0;
      uStack_78 = uStack_94;
      uStack_74 = uStack_94;
      local_70 = uStack_94;
      uStack_6c = uStack_94;
      fStack_68 = local_a0;
      uStack_64 = uStack_94;
      local_60 = uStack_94;
      uStack_5c = uStack_94;
      uStack_58 = uStack_94;
      fStack_54 = local_a0;
      FUN_00414aa0();
      FUN_00417560();
      FUN_00417560();
      local_214 = local_214 + 1;
    } while (local_214 < *(short *)(param_1 + 0xaa));
  }
  if (bVar20) {
    iVar29 = 1;
    if (1 < *(int *)(iVar27 + 8)) {
      iVar26 = *(int *)(iVar27 + 0xc) + 0x18;
      do {
        if (*(int *)(iVar26 + 4) == 3) {
          FUN_00417560();
        }
        iVar29 = iVar29 + 1;
        iVar26 = iVar26 + 0x10;
      } while (iVar29 < *(int *)(iVar27 + 8));
    }
  }
  iVar27 = DAT_01205560;
  *(char *)((int)piVar24 + 9) = *(char *)((int)piVar24 + 9) + -1;
  if (((char)piVar24[2] == '\\0') && (*(char *)((int)piVar24 + 9) == '\\0')) {
    iVar29 = *piVar24;
    piVar7 = (int *)piVar24[1];
    if (iVar29 != 0) {
      *(int **)(iVar29 + 4) = piVar7;
    }
    if (piVar7 == (int *)0x0) {
      *(undefined4 *)(iVar27 + 8) = *(undefined4 *)(iVar27 + 4);
      *(int *)(iVar27 + 4) = iVar29;
      if (iVar29 == 0) {
        *(undefined4 *)(iVar27 + 8) = *(undefined4 *)(iVar27 + 0xc);
      }
    }
    else {
      *piVar7 = iVar29;
    }
  }
  *(char *)((int)piVar23 + 9) = *(char *)((int)piVar23 + 9) + -1;
  DAT_01205584 = 0;
  if (((char)piVar23[2] == '\\0') && (*(char *)((int)piVar23 + 9) == '\\0')) {
    iVar29 = *piVar23;
    piVar7 = (int *)piVar23[1];
    if (iVar29 != 0) {
      *(int **)(iVar29 + 4) = piVar7;
    }
    if (piVar7 == (int *)0x0) {
      *(undefined4 *)(iVar27 + 8) = *(undefined4 *)(iVar27 + 4);
      *(int *)(iVar27 + 4) = iVar29;
      if (iVar29 == 0) {
        *(undefined4 *)(iVar27 + 8) = *(undefined4 *)(iVar27 + 0xc);
      }
    }
    else {
      *piVar7 = iVar29;
    }
  }
  *(char *)((int)piVar22 + 9) = *(char *)((int)piVar22 + 9) + -1;
  _DAT_01205580 = 0;
  if (((char)piVar22[2] == '\\0') && (*(char *)((int)piVar22 + 9) == '\\0')) {
    iVar29 = *piVar22;
    piVar7 = (int *)piVar22[1];
    if (iVar29 != 0) {
      *(int **)(iVar29 + 4) = piVar7;
    }
    if (piVar7 == (int *)0x0) {
      *(undefined4 *)(iVar27 + 8) = *(undefined4 *)(iVar27 + 4);
      *(int *)(iVar27 + 4) = iVar29;
      DAT_0120557c = (int *)0x0;
      if (iVar29 == 0) {
        *(undefined4 *)(iVar27 + 8) = *(undefined4 *)(iVar27 + 0xc);
        return;
      }
    }
    else {
      *piVar7 = iVar29;
    }
  }
  DAT_0120557c = (int *)0x0;
  return;
}