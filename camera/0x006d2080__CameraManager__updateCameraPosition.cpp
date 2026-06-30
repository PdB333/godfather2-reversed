// FUNC_NAME: CameraManager::updateCameraPosition
void __thiscall CameraManager::updateCameraPosition(int this, undefined4 param_2, char param_3)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  bool bVar4;
  bool bVar5;
  float fVar6;
  float fVar7;
  undefined4 *puVar8;
  int iVar9;
  undefined *puVar10;
  float *pfVar11;
  float fVar12;
  int local_ac;
  int local_a8;
  int *local_a4;
  float local_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  float fStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 100) = 0;
  if (DAT_0112a862 == '\0') {
    *(undefined4 *)(this + 0xe8) = 0;
  }
  else {
    *(float *)(this + 0xe8) = DAT_00e5116c + DAT_00d58cbc;
    DAT_0112a862 = '\0';
  }
  DAT_00e510d0 = DAT_00e510cc;
  DAT_0112a860 = 0;
  *(undefined4 *)(this + 0xd0) = param_2;
  *(float *)(this + 0x50) = DAT_00e51104 * DAT_00e445c8;
  *(float *)(this + 0xe0) = DAT_0112a870;
  puVar8 = (undefined4 *)FUN_00471610(); // Get camera transform matrix
  local_90 = *puVar8;
  uStack_8c = puVar8[1];
  uStack_88 = puVar8[2];
  uStack_84 = puVar8[3];
  local_80 = puVar8[4];
  uStack_7c = puVar8[5];
  uStack_78 = puVar8[6];
  uStack_74 = puVar8[7];
  local_70 = puVar8[8];
  uStack_6c = puVar8[9];
  uStack_68 = puVar8[10];
  uStack_64 = puVar8[0xb];
  local_60 = puVar8[0xc];
  uStack_58 = puVar8[0xe];
  uStack_54 = puVar8[0xf];
  fStack_5c = *(float *)(this + 0xe0) + (float)puVar8[0xd];
  if (param_3 == '\0') {
    iVar9 = *(int *)(*(int *)(DAT_012233a0 + 4) + *(int *)(this + 0xd4) * 4);
    bVar5 = false;
    if (iVar9 == 0) {
      iVar9 = 0;
    }
    else {
      iVar9 = iVar9 + -0x1f30;
    }
    uVar1 = *(undefined4 *)(&DAT_00002494 + iVar9);
    bVar4 = false;
    local_ac = 0;
    local_a8 = 0;
    local_a4 = (int *)0x0;
    do {
      iVar9 = FUN_00424c90(uVar1);
      if (iVar9 == 4) goto LAB_006d224d;
      if (bVar4) {
        local_ac = FUN_00425030(uVar1,&local_a4,&local_ac);
        if (local_a8 == local_ac) goto LAB_006d224d;
      }
      else {
        local_ac = FUN_00425030(uVar1,&local_a4,0);
        bVar4 = true;
        local_a8 = local_ac;
      }
    } while ((local_a4 == (int *)0x0) ||
            (puVar10 = (undefined *)(**(code **)(*local_a4 + 0x10))(), puVar10 != &DAT_00e078fa));
    if (local_a4[0x52] == 2) {
      bVar5 = true;
    }
LAB_006d224d:
    puVar8 = (undefined4 *)FUN_00425060(&local_a0,param_2);
    *(undefined4 *)(this + 0x40) = *puVar8;
    fVar12 = _DAT_00d5780c;
    *(undefined4 *)(this + 0x44) = puVar8[1];
    uVar1 = puVar8[2];
    *(float *)(this + 0x4c) = fVar12;
    *(undefined4 *)(this + 0x48) = uVar1;
    if ((bVar5) && (DAT_0112a8dc == _DAT_00d577a0)) {
      DAT_0112a8dc = DAT_00e511bc;
    }
    *(float *)(this + 0x40) = DAT_0112a8dc * DAT_00e445c8 + *(float *)(this + 0x40);
    DAT_0112a8dc = 0.0;
    FUN_0056b8a0(*(undefined4 *)(this + 0x44),*(undefined4 *)(this + 0x40),
                 *(undefined4 *)(this + 0x48),&fStack_50);
    local_a0 = fStack_40 * 0.0 + fStack_50 * 0.0 + _DAT_00d5780c * fStack_30;
    fStack_9c = fStack_3c * 0.0 + fStack_4c * 0.0 + _DAT_00d5780c * fStack_2c;
    fStack_98 = fStack_38 * 0.0 + fStack_48 * 0.0 + _DAT_00d5780c * fStack_28;
    fStack_94 = 0.0;
    iVar9 = FUN_00471610();
    uVar1 = *(undefined4 *)(iVar9 + 0x34);
    uVar2 = *(undefined4 *)(iVar9 + 0x38);
    uVar3 = *(undefined4 *)(iVar9 + 0x3c);
    *(undefined4 *)(this + 0x90) = *(undefined4 *)(iVar9 + 0x30);
    *(undefined4 *)(this + 0x94) = uVar1;
    *(undefined4 *)(this + 0x98) = uVar2;
    *(undefined4 *)(this + 0x9c) = uVar3;
    fVar12 = *(float *)(this + 0x94) + DAT_0112a870;
    *(float *)(this + 0x94) = fVar12;
    fVar12 = fVar12 + DAT_00e51128;
    *(undefined4 *)(this + 0x30) = *(undefined4 *)(this + 0x90);
    *(float *)(this + 0x34) = fVar12;
    *(float *)(this + 0x3c) = _DAT_00d5780c;
    fVar12 = DAT_00e44564;
    *(undefined4 *)(this + 0x38) = *(undefined4 *)(this + 0x98);
    fVar12 = fVar12 - DAT_00e51178;
    *(float *)(this + 0x20) = fVar12 * local_a0 + *(float *)(this + 0x30);
    *(float *)(this + 0x24) = fVar12 * fStack_9c + *(float *)(this + 0x34);
    *(float *)(this + 0x28) = fVar12 * fStack_98 + *(float *)(this + 0x38);
    *(float *)(this + 0x2c) = fVar12 * fStack_94 + *(float *)(this + 0x3c);
  }
  else {
    FUN_006d1f00();
    *(undefined4 *)(this + 0x20) = *(undefined4 *)(this + 0x70);
    *(undefined4 *)(this + 0x24) = *(undefined4 *)(this + 0x74);
    *(undefined4 *)(this + 0x28) = *(undefined4 *)(this + 0x78);
    *(undefined4 *)(this + 0x2c) = *(undefined4 *)(this + 0x7c);
    *(undefined4 *)(this + 0x30) = *(undefined4 *)(this + 0xc0);
    *(undefined4 *)(this + 0x34) = *(undefined4 *)(this + 0xc4);
    *(undefined4 *)(this + 0x38) = *(undefined4 *)(this + 200);
    *(undefined4 *)(this + 0x3c) = *(undefined4 *)(this + 0xcc);
  }
  fVar7 = fRam0112a85c;
  fVar6 = fRam0112a858;
  fVar12 = fRam0112a854;
  pfVar11 = (float *)(this + 0x20);
  local_a0 = *pfVar11 - _DAT_0112a850;
  fStack_9c = *(float *)(this + 0x24) - fRam0112a854;
  fStack_98 = *(float *)(this + 0x28) - fRam0112a858;
  fStack_94 = *(float *)(this + 0x2c) - fRam0112a85c;
  if ((SQRT(fStack_9c * fStack_9c + fStack_98 * fStack_98 + local_a0 * local_a0) < DAT_00e446f4) &&
     (DAT_0112a861 != '\0')) {
    *pfVar11 = _DAT_0112a850;
    *(float *)(this + 0x24) = fVar12;
    *(float *)(this + 0x28) = fVar6;
    *(float *)(this + 0x2c) = fVar7;
    uVar3 = uRam0112a84c;
    uVar2 = uRam0112a848;
    uVar1 = uRam0112a844;
    *(undefined4 *)(this + 0x30) = _DAT_0112a840;
    *(undefined4 *)(this + 0x34) = uVar1;
    *(undefined4 *)(this + 0x38) = uVar2;
    *(undefined4 *)(this + 0x3c) = uVar3;
  }
  DAT_0112a861 = 0;
  (**(code **)**(undefined4 **)(this + 0xd8))(pfVar11,(undefined4 *)(this + 0x30),&local_60);
  *(undefined4 *)(this + 0xb0) = uStack_6c;
  *(undefined4 *)(this + 0xb4) = uStack_68;
  *(undefined4 *)(this + 0xb8) = uStack_64;
  *(undefined4 *)(this + 0xbc) = local_60;
  return;
}