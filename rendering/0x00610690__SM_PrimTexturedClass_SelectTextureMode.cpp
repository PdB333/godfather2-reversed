// Xbox PDB: SM_PrimTexturedClass::SelectTextureMode
// FUNC_NAME: Renderer::submitDrawCall
void Renderer::submitDrawCall(int param_1, int param_2, undefined4 *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  float *pfVar10;
  uint uVar11;
  undefined4 *puVar12;
  float fVar13;
  undefined4 local_4;
  
  if (DAT_011f4234 == 0) {
    FUN_00612210(&DAT_00f15990);
  }
  if (param_3 == (undefined4 *)0x0) {
    FUN_00612a60();
    local_4 = 0x10;
  }
  else {
    if ((DAT_011f4230 < 0x1000) && (DAT_011f4230 * 0x38 != -0x11a0f28)) {
      if (*(int *)(&DAT_011a0f30 + DAT_011f4230 * 0x38) == 9) {
        DAT_01127774 = DAT_01127878;
        DAT_01127868 = FUN_0060a580(DAT_01127878,"lodBias");
        if (DAT_012058e8 == &PTR_PTR_01127760) {
          FUN_0060a460(DAT_01127774);
          FUN_0060aa90(DAT_01127774,DAT_01127868,DAT_01127840);
        }
        FUN_00619950();
      }
      else if (*(int *)(&DAT_011a0f30 + DAT_011f4230 * 0x38) == 8) {
        DAT_01127774 = DAT_01127884;
        DAT_01127868 = FUN_0060a580(DAT_01127884,"lodBias");
        if (DAT_012058e8 == &PTR_PTR_01127760) {
          FUN_0060a460(DAT_01127774);
          FUN_0060aa90(DAT_01127774,DAT_01127868,DAT_01127840);
        }
      }
      else {
        DAT_01127774 = DAT_01127874;
        DAT_01127868 = FUN_0060a580(DAT_01127874,"lodBias");
        if (DAT_012058e8 == &PTR_PTR_01127760) {
          FUN_0060a460(DAT_01127774);
          FUN_0060aa90(DAT_01127774,DAT_01127868,DAT_01127840);
        }
        FUN_00619900();
      }
    }
    FUN_00619650();
    local_4 = 0x18;
  }
  fVar5 = DAT_011f422c;
  fVar4 = DAT_011f4228;
  fVar3 = DAT_011f4224;
  fVar2 = DAT_011f4220;
  fVar1 = DAT_00e448b8;
  puVar8 = (undefined4 *)(param_1 + 8);
  pfVar10 = (float *)(param_2 + 0xc);
  iVar9 = 4;
  puVar6 = &DAT_011f4240;
  puVar12 = param_3;
  do {
    *puVar6 = puVar8[-2];
    puVar6[1] = puVar8[-1];
    puVar6[2] = *puVar8;
    if (param_2 == 0) {
      *(char *)(puVar6 + 3) = (char)(int)(fVar2 * fVar1);
      *(char *)((int)puVar6 + 0xd) = (char)(int)(fVar3 * fVar1);
      *(char *)((int)puVar6 + 0xe) = (char)(int)(fVar4 * fVar1);
      fVar13 = fVar5;
    }
    else {
      *(char *)(puVar6 + 3) = (char)(int)(pfVar10[-3] * fVar1);
      *(char *)((int)puVar6 + 0xd) = (char)(int)(pfVar10[-2] * fVar1);
      *(char *)((int)puVar6 + 0xe) =
           (char)(int)(*(float *)((param_2 - param_1) + (int)puVar8) * fVar1);
      fVar13 = *pfVar10;
    }
    *(char *)((int)puVar6 + 0xf) = (char)(int)(fVar13 * fVar1);
    puVar7 = puVar6 + 4;
    if (param_3 != (undefined4 *)0x0) {
      puVar6[4] = *puVar12;
      puVar7 = puVar6 + 6;
      puVar6[5] = puVar12[1];
    }
    puVar8 = puVar8 + 4;
    pfVar10 = pfVar10 + 4;
    puVar12 = puVar12 + 4;
    iVar9 = iVar9 + -1;
    puVar6 = puVar7;
  } while (iVar9 != 0);
  FUN_0060cc10(5,4,&DAT_011f4240,local_4);
  if (param_3 == (undefined4 *)0x0) {
    if (DAT_01127958 != 0) {
      uVar11 = DAT_01127958 & 0xff;
      if ((&DAT_011eb8fc)[DAT_011278cc * 0x10] != '\\0') {
        uVar11 = uVar11 + 0x10;
      }
      FUN_00618d40();
      (&DAT_011d912c)[uVar11] = 0;
    }
  }
  else {
    if (DAT_01127800 != 0) {
      uVar11 = DAT_01127800 & 0xff;
      if ((&DAT_011eb8fc)[DAT_01127774 * 0x10] != '\\0') {
        uVar11 = uVar11 + 0x10;
      }
      FUN_00618d40();
      (&DAT_011d912c)[uVar11] = 0;
    }
    _DAT_01127804 = 0;
    _DAT_01127808 = 0;
    _DAT_0112780c = 0;
    _DAT_01127810 = 0;
    _DAT_01127814 = 0;
    _DAT_01127818 = 0;
    _DAT_0112781c = 0;
  }
  DAT_012058f0 = 0;
  DAT_012058e8 = (undefined **)0x0;
  if (DAT_011f4234 == 0) {
    FUN_00612210(&DAT_011f6b70);
  }
  return;
}