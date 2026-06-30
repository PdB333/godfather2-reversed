// FUNC_NAME: VisibilityManager::computeVisibilityOcclusion
void VideoSystem::visibilityCheck(int param_1, uint param_2, int param_3)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  float fVar7;
  int in_EAX;
  float *pfVar8;
  uint uVar9;
  uint uVar10;
  uint unaff_EBX;
  uint uVar11;
  int iVar12;
  float *pfVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  int local_40;
  byte local_38 [52];
  
  fVar7 = DAT_00e2b1a4;
  local_38[0] = *(byte *)(in_EAX + 0x60);
  local_38[1] = *(undefined1 *)(in_EAX + 0x120);
  local_38[2] = *(undefined1 *)(in_EAX + 0x1e0);
  local_38[3] = *(undefined1 *)(in_EAX + 0x2a0);
  local_38[4] = *(undefined1 *)(in_EAX + 0x360);
  local_38[5] = *(undefined1 *)(in_EAX + 0x420);
  local_38[6] = *(undefined1 *)(in_EAX + 0x4e0);
  local_38[7] = *(byte *)(in_EAX + 0x5a0);
  local_40 = 0;
  if (0 < param_3) {
    pfVar13 = (float *)(param_1 + 8);
    uVar10 = (uint)*(byte *)(in_EAX + 0x5a0);
    do {
      fVar1 = pfVar13[-2];
      fVar2 = pfVar13[-1];
      fVar3 = *pfVar13;
      fVar4 = pfVar13[1];
      uVar9 = 0;
      iVar12 = 0;
      pfVar8 = (float *)(in_EAX + 0x20);
      do {
        fVar14 = pfVar8[0xb] * fVar7 + pfVar8[10] * fVar3;
        fVar15 = pfVar8[9] * fVar2 + pfVar8[8] * fVar1;
        fVar16 = pfVar8[0xf] * fVar7 + pfVar8[0xe] * fVar3;
        fVar17 = pfVar8[0xd] * fVar2 + pfVar8[0xc] * fVar1;
        auVar5._4_4_ = -(uint)(fVar4 < pfVar8[-7] * fVar2 + pfVar8[-8] * fVar1 +
                                       pfVar8[-5] * fVar7 + pfVar8[-6] * fVar3);
        auVar5._0_4_ = -(uint)(fVar4 < pfVar8[-3] * fVar2 + pfVar8[-4] * fVar1 +
                                       pfVar8[-1] * fVar7 + pfVar8[-2] * fVar3);
        auVar5._8_4_ = -(uint)(fVar4 < pfVar8[5] * fVar2 + pfVar8[4] * fVar1 +
                                       pfVar8[7] * fVar7 + pfVar8[6] * fVar3);
        auVar5._12_4_ =
             -(uint)(fVar4 < pfVar8[1] * fVar2 + *pfVar8 * fVar1 +
                             pfVar8[3] * fVar7 + pfVar8[2] * fVar3);
        uVar11 = movmskps(unaff_EBX,auVar5);
        auVar6._4_4_ = -(uint)(fVar4 < fVar15 + fVar14);
        auVar6._0_4_ = -(uint)(fVar4 < fVar17 + fVar16);
        auVar6._8_4_ = -(uint)(fVar4 < fVar17 + fVar16);
        auVar6._12_4_ = -(uint)(fVar4 < fVar15 + fVar14);
        uVar10 = movmskps(uVar10,auVar6);
        unaff_EBX = (uint)local_38[iVar12];
        iVar12 = iVar12 + 1;
        pfVar8 = pfVar8 + 0x30;
        uVar10 = (0 < (int)(uVar10 | uVar11)) - 1 & unaff_EBX;
        uVar9 = uVar9 | uVar10;
      } while (iVar12 < 8);
      *(char *)(local_40 + param_2) = (char)uVar9;
      local_40 = local_40 + 1;
      pfVar13 = pfVar13 + 4;
      uVar10 = param_2;
    } while (local_40 < param_3);
  }
  return;
}