// FUNC_NAME: CameraSystem::updateCamera
void __thiscall CameraSystem::updateCamera(int this, float deltaTime)
{
  float *pfVar1;
  int *piVar2;
  float *pfVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  bool bVar6;
  char cVar7;
  char cVar8;
  byte bVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  bool bVar13;
  float10 fVar14;
  float fVar15;
  double dVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  byte local_f2;
  float local_f0;
  float local_e8;
  float local_e0;
  float local_e4;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  int local_bc;
  undefined8 local_b8;
  float local_b0;
  undefined8 local_ac;
  float local_a4;
  float local_a0;
  float local_9c;
  float fStack_98;
  float local_94;
  float local_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  undefined8 local_7c;
  undefined4 local_74;
  float local_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_44;
  float fStack_40;
  float local_3c;
  undefined8 local_38;
  undefined4 local_30;
  float local_2c [3];
  undefined1 local_20 [28];
  
  DAT_0112a863 = 0;
  if (*(int *)(this + 0x124) == 0) {
    iVar11 = 0;
  }
  else {
    iVar11 = *(int *)(this + 0x124) + -0x48;
  }
  uVar12 = *(uint *)(iVar11 + 0x8e0) >> 9;
  local_f2 = (byte)uVar12 & 1;
  local_bc = iVar11;
  FUN_006c85e0(deltaTime);
  if (*(int *)(this + 0x124) == 0) {
    iVar10 = 0;
  }
  else {
    iVar10 = *(int *)(this + 0x124) + -0x48;
  }
  FUN_006ca4b0(iVar10,1,1,deltaTime);
  if (*(int *)(this + 0x6c) == -1) {
    FUN_006ca8e0(iVar11);
  }
  cVar7 = FUN_00410eb0();
  if (cVar7 == '\0') {
    FUN_006c9eb0(1,&local_e8,&local_e0,*(undefined4 *)(this + 0x1d8),
                 *(undefined4 *)(this + 0x1d8));
    FUN_006c8a60(&local_e8,&local_e0,*(undefined4 *)(this + 0x1d0),
                 *(undefined4 *)(this + 0x1d4));
    FUN_006c8b50(&local_e8,&local_e0);
  }
  else {
    FUN_006c9eb0(1,&local_e8,&local_e0,0,0);
  }
  cVar8 = FUN_007f47a0();
  if (cVar8 == '\0') {
    if ((((uVar12 & 1) == 0) && (cVar8 = FUN_006c9fe0(), cVar8 != '\0')) &&
       (-1 < *(int *)(iVar11 + 0x8e0))) {
      *(undefined1 *)(this + 0x108) = 1;
      *(byte *)(this + 0x10a) = local_f2;
      *(undefined4 *)(this + 0x114) = 0;
      *(undefined4 *)(this + 0x110) = 0;
      *(undefined4 *)(this + 0x10c) = 0;
      *(byte *)(this + 0x109) = local_f2;
    }
  }
  else {
    local_e8 = 0.0;
    local_e0 = 0.0;
  }
  iVar11 = FUN_006e07b0(iVar11);
  local_f2 = local_f2 & iVar11 != 0;
  if (local_f2 != 0) {
    local_d0 = *(float *)(DAT_01129944 + 0x108);
    fStack_cc = *(float *)(DAT_01129944 + 0x10c);
    fStack_c8 = *(float *)(DAT_01129944 + 0x110);
    fStack_c4 = _DAT_00d5780c;
    iVar10 = FUN_004262f0(0);
    FUN_0056b420(iVar10 + 0x40,&local_d0,local_20);
    piVar2 = (int *)(this + 0x1ec);
    if (iVar11 == 0) {
      iVar11 = 0;
    }
    else {
      iVar11 = iVar11 + 0x48;
    }
    if (*piVar2 != iVar11) {
      if (*piVar2 != 0) {
        FUN_004daf90(piVar2);
      }
      *piVar2 = iVar11;
      if (iVar11 != 0) {
        *(undefined4 *)(this + 0x1f0) = *(undefined4 *)(iVar11 + 4);
        *(int **)(iVar11 + 4) = piVar2;
      }
    }
    local_f2 = FUN_006e15a0(local_e8,local_e0,&local_60);
    if (local_f2 != 0) {
      fVar17 = local_58 - *(float *)(this + 0x28);
      fVar15 = local_60 - *(float *)(this + 0x20);
      if (_DAT_00d5f7bc <= fVar17 * fVar17 + fVar15 * fVar15) {
        fStack_6c = local_5c;
        local_70 = local_60;
        fStack_68 = local_58;
        fStack_64 = _DAT_00d5780c;
      }
      else {
        local_f2 = 0;
      }
    }
  }
  fVar15 = _DAT_00d5cf70;
  if (*(char *)(this + 0x108) == '\0') {
    pfVar3 = (float *)(this + 0xac);
    FUN_006c9880(this + 0x1bc,pfVar3,DAT_00e44564 - local_e0,deltaTime,0x3f800000);
    FUN_006c99c0(this + 0x1bc,this + 0xa8,local_e8,deltaTime,0x3f800000);
    fVar14 = (float10)FUN_006c8900(*pfVar3,deltaTime);
    *(float *)(this + 0xfc) =
         (float)((float10)*(float *)(this + 0xfc) - fVar14 * (float10)DAT_00e44748);
    if (DAT_0112a7a6 == '\0') {
      fVar14 = (float10)FUN_006c8900(*(undefined4 *)(this + 0xa8),deltaTime);
      *(float *)(this + 0x100) =
           (float)(fVar14 * (float10)DAT_00e44748 + (float10)*(float *)(this + 0x100));
    }
    iVar11 = local_bc;
    fVar14 = (float10)FUN_006d67e0(local_bc,*(undefined4 *)(this + 0x80),
                                   *(undefined4 *)(this + 0x144));
    fVar15 = (float)fVar14;
    if (*(float *)(this + 0xfc) <= fVar15) {
      if (*(float *)(this + 0xfc) < DAT_00e44564 - fVar15) {
        *(float *)(this + 0xfc) = DAT_00e44564 - fVar15;
        fVar17 = *pfVar3;
        bVar13 = fVar17 < 0.0;
        goto LAB_006e29e7;
      }
    }
    else {
      fVar17 = *pfVar3;
      *(float *)(this + 0xfc) = fVar15;
      bVar13 = 0.0 < fVar17;
LAB_006e29e7:
      if (bVar13 || fVar17 == 0.0) {
        fVar17 = 0.0;
      }
      *pfVar3 = fVar17;
    }
    fVar15 = *(float *)(this + 0x148);
    if (*(float *)(this + 0x100) <= fVar15) {
      if (DAT_00e44564 - fVar15 <= *(float *)(this + 0x100)) goto LAB_006e2af4;
      *(float *)(this + 0x100) = DAT_00e44564 - fVar15;
      fVar17 = *(float *)(this + 0xa8);
      bVar13 = fVar17 < 0.0;
    }
    else {
      fVar17 = *(float *)(this + 0xa8);
      *(float *)(this + 0x100) = fVar15;
      bVar13 = 0.0 < fVar17;
    }
    if (bVar13 || fVar17 == 0.0) {
      fVar17 = 0.0;
    }
    *(float *)(this + 0xa8) = fVar17;
  }
  else {
    *(undefined4 *)(this + 0xac) = 0;
    *(undefined4 *)(this + 0xa8) = 0;
    fVar14 = (float10)FUN_006c89b0(*(undefined4 *)(this + 0xfc),0,fVar15);
    *(float *)(this + 0xfc) = (float)fVar14;
    fVar14 = (float10)FUN_006c89b0(*(undefined4 *)(this + 0x100),0,_DAT_00d5cf70);
    *(float *)(this + 0x100) = (float)fVar14;
    iVar11 = local_bc;
    if (((float)(*(uint *)(this + 0xfc) & DAT_00e44680) < _DAT_00d5780c) &&
       ((float)((uint)(float)fVar14 & DAT_00e44680) < _DAT_00d5780c)) {
      *(undefined1 *)(this + 0x108) = 0;
    }
  }
LAB_006e2af4:
  fVar15 = *(float *)(this + 0x1b0);
  local_f0 = (*(float *)(this + 0x100) / *(float *)(this + 0x148)) * fVar15;
  if ((*(uint *)(iVar11 + 0x8e0) >> 0x1e & 1) != 0) {
    local_f0 = DAT_00e44564 - local_f0;
  }
  if (0.0 <= local_f0) {
    if (fVar15 < local_f0) {
      local_f0 = fVar15;
    }
  }
  else {
    local_f0 = 0.0;
  }
  fVar14 = (float10)FUN_006c89b0(*(undefined4 *)(this + 0x104),local_f0,
                                 *(undefined4 *)(this + 0x1b4));
  *(float *)(this + 0x104) = (float)fVar14;
  FUN_006dfe90(&local_9c,iVar11);
  local_d4 = *(float *)(this + 0xec);
  local_dc = *(float *)(this + 0xe4);
  local_d8 = *(float *)(this + 0xe8);
  *(ulonglong *)(this + 0x118) = CONCAT44(fStack_98,local_9c);
  local_90 = DAT_00e44564 - local_d4;
  *(float *)(this + 0x120) = local_94;
  fStack_8c = 0.0;
  fStack_84 = 0.0;
  fStack_88 = local_dc;
  FUN_0056afa0(&local_90,&local_90);
  uVar12 = *(uint *)(iVar11 + 0x8e0);
  bVar9 = (byte)(uVar12 >> 0x19) & 1;
  local_b8 = CONCAT44(fStack_8c,local_90);
  local_b0 = fStack_88;
  if ((bVar9 == 0) || (bVar13 = true, (uVar12 >> 0x1d & 1) == 0)) {
    bVar13 = false;
  }
  if ((bVar9 == 0) || ((uVar12 >> 0x1e & 1) == 0)) {
    bVar6 = false;
  }
  else {
    bVar6 = true;
  }
  if ((bVar13) || (bVar6)) {
    if (*(char *)(this + 0x10a) != '\0') {
      if (((((*(char *)(this + 0x109) == '\0') ||
            (DAT_00d5ef90 <= (float)((uint)local_e8 & DAT_00e44680))) ||
           (DAT_00d5ef90 <= (float)((uint)local_e0 & DAT_00e44680))) ||
          ((fVar17 = local_94 - *(float *)(this + 0x114),
           fVar15 = local_9c - *(float *)(this + 0x10c),
           DAT_00d5c454 <= fVar17 * fVar17 + fVar15 * fVar15 || (*(char *)(this + 0x109) == '\0')
           ))) && (cVar8 = FUN_006e22a0(&local_b8,&local_dc,&local_9c), cVar8 != '\0')) {
        *(undefined1 *)(this + 0x10a) = 0;
        *(undefined4 *)(this + 0x114) = 0;
        *(undefined4 *)(this + 0x110) = 0;
        *(undefined4 *)(this + 0x10c) = 0;
        goto LAB_006e2cac;
      }
      goto LAB_006e2cf7;
    }
    cVar8 = FUN_006e22a0(&local_b8,&local_dc,&local_9c);
    *(bool *)(this + 0x10a) = cVar8 == '\0';
    if (cVar8 == '\0') {
      *(ulonglong *)(this + 0x10c) = CONCAT44(fStack_98,local_9c);
      *(undefined1 *)(this + 0x10a) = 1;
      *(float *)(this + 0x114) = local_94;
      goto LAB_006e2cf7;
    }
LAB_006e2cac:
    fVar14 = (float10)FUN_006c89b0(*(undefined4 *)(this + 0xf0),0x3f800000,
                                   *(undefined4 *)(this + 0x15c));
    *(undefined1 *)(this + 0x109) = 1;
  }
  else {
LAB_006e2cf7:
    fVar14 = (float10)FUN_006c89b0(*(undefined4 *)(this + 0xf0),0,
                                   *(undefined4 *)(this + 0x15c));
  }
  *(float *)(this + 0xf0) = (float)fVar14;
  if (((*(uint *)(iVar11 + 0x8e0) >> 0x1a & 1) == 0) &&
     ((*(uint *)(iVar11 + 0x8e0) >> 0x19 & 1) != 0)) {
    iVar10 = 1;
  }
  else {
    iVar10 = 0;
  }
  fVar14 = (float10)FUN_006c89b0(*(undefined4 *)(this + 0xf4),(float)iVar10,
                                 *(undefined4 *)(this + 0x1ac));
  *(float *)(this + 0xf4) = (float)fVar14;
  if ((*(uint *)(iVar11 + 0x8e0) >> 0x1d & 1) == 0) {
    fVar15 = DAT_00e44564 - *(float *)(this + 0x154);
  }
  else {
    fVar15 = *(float *)(this + 0x154);
  }
  local_e4 = ((_DAT_00d5780c - *(float *)(this + 0xf0)) + _DAT_00d5780c) * DAT_00d5ef90;
  if (cVar7 == '\0') {
    fVar14 = (float10)FUN_006c89b0(*(undefined4 *)(this + 0xf8),fVar15,local_e4);
    *(float *)(this + 0xf8) = (float)fVar14;
  }
  else {
    *(float *)(this + 0xf8) = fVar15;
  }
  uVar5 = *(undefined8 *)(this + 0xd8);
  local_b0 = *(float *)(this + 0xe0);
  pfVar3 = (float *)(this + 0xd8);
  fVar15 = *(float *)(this + 0xf8) * *(float *)(this + 0xf0);
  *pfVar3 = fVar15 * local_90 + local_9c;
  *(float *)(this + 0xdc) = fVar15 * fStack_8c + fStack_98;
  *(float *)(this + 0xe0) = fVar15 * fStack_88 + local_94;
  fVar15 = *(float *)(this + 0x104);
  *pfVar3 = fVar15 * local_dc + *pfVar3;
  fVar17 = fVar15 * local_d8 + *(float *)(this + 0xdc);
  *(float *)(this + 0xdc) = fVar17;
  *(float *)(this + 0xe0) = fVar15 * local_d4 + *(float *)(this + 0xe0);
  if ((local_f2 == 0) && ((*(byte *)(iVar11 + 0x249f) & 1) == 0)) {
    local_b8._4_4_ = (float)((ulonglong)uVar5 >> 0x20);
    local_b8._0_4_ = (float)uVar5;
    fVar17 = fVar17 - local_b8._4_4_;
    fVar18 = *(float *)(this + 0xe0) - local_b0;
    fVar15 = *pfVar3 - (float)local_b8;
    fVar20 = SQRT(fVar18 * fVar18 + fVar17 * fVar17 + fVar15 * fVar15);
    fVar19 = *(float *)(this + 0x1b8) * deltaTime;
    if (fVar19 < fVar20) {
      fVar19 = fVar19 / fVar20;
      *pfVar3 = fVar15 * fVar19 + (float)local_b8;
      *(float *)(this + 0xdc) = fVar17 * fVar19 + local_b8._4_4_;
      *(float *)(this + 0xe0) = fVar18 * fVar19 + local_b0;
    }
  }
  if (bVar13) {
    fVar17 = DAT_00e44564 - *(float *)(this + 0x174);
    fVar15 = *(float *)(this + 0x100);
    if (fVar17 < fVar15) {
      fVar17 = *(float *)(this + 0x148);
LAB_006e304f:
      if (fVar15 < fVar17) {
        fVar17 = fVar15;
      }
    }
LAB_006e3057:
    *(float *)(this + 0x100) = fVar17;
  }
  else if (bVar6) {
    fVar17 = DAT_00e44564 - *(float *)(this + 0x148);
    fVar15 = *(float *)(this + 0x100);
    if (fVar17 < fVar15) {
      fVar17 = *(float *)(this + 0x174);
      goto LAB_006e304f;
    }
    goto LAB_006e3057;
  }
  local_b8 = uVar5;
  iVar11 = FUN_00471610();
  FUN_004a0370(&local_dc,&local_dc,iVar11 + 0x10,*(float *)(this + 0x100) * DAT_00e445c8);
  local_2c[0] = DAT_00e44564 - local_d4;
  local_2c[1] = 0.0;
  local_2c[2] = local_dc;
  FUN_004a0370(&local_dc,&local_dc,local_2c,
               (*(float *)(this + 0xfc) - *(float *)(this + 0x188)) * DAT_00e445c8);
  iVar11 = FUN_004262f0(0);
  fVar17 = _DAT_00d5780c - *(float *)(this + 0xf0);
  local_a0 = _DAT_00d5780c - *(float *)(iVar11 + 0x150) * _DAT_00d5f7b8;
  fVar15 = (*(float *)(this + 0x150) - *(float *)(this + 0x14c)) * fVar17 +
           *(float *)(this + 0x14c);
  fVar18 = local_a0 * _DAT_00e5129c + _DAT_00e51294;
  fVar15 = ((((local_a0 * _DAT_00e5129c + _DAT_00e51298) - fVar18) * fVar17 + fVar18) - fVar15) *
           *(float *)(this + 0x80) + fVar15;
  local_44 = fVar15 * local_dc + *pfVar3;
  fStack_40 = fVar15 * local_d8 + *(float *)(this + 0xdc);
  local_3c = fVar15 * local_d4 + *(float *)(this + 0xe0);
  local_e4 = *(float *)(this + 0x1a4);
  puVar4 = (undefined8 *)(this + 0xcc);
  if (cVar7 == '\0') {
    FUN_006c8940(puVar4,&local_44,local_e4,puVar4);
  }
  else {
    *puVar4 = CONCAT44(fStack_40,local_44);
    *(float *)(this + 0xd4) = local_3c;
  }
  dVar16 = (double)local_d8;
  FUN_00b9a9fa();
  local_b8 = CONCAT44(local_b8._4_4_,(float)dVar16);
  dVar16 = (double)(DAT_00e44564 - local_dc);
  FUN_00b9a9fa();
  fVar15 = (float)dVar16;
  local_f0 = *(float *)(this + 0x1a8);
  if (((*(float *)(this + 0xfc) == 0.0) && (local_e0 == 0.0)) && (local_e8 == 0.0)) {
    local_f0 = (local_f0 - _DAT_00d5cf70) * *(float *)(this + 0xf4) + _DAT_00d5cf70;
  }
  local_b8._4_4_ = fVar15;
  if (cVar7 == '\0') {
    fVar14 = (float10)FUN_006c89d0(*(undefined4 *)(this + 0xc0),(float)local_b8,local_f0);
    *(float *)(this + 0xc0) = (float)fVar14;
    fVar14 = (float10)FUN_006c89d0(*(undefined4 *)(this + 0xc4),local_b8._4_4_,local_f0);
    *(float *)(this + 0xc4) = (float)fVar14;
    *(undefined4 *)(this + 200) = 0;
  }
  else {
    *(float *)(this + 0xc0) = (float)local_b8;
    *(float *)(this + 0xc4) = fVar15;
    *(undefined4 *)(this + 200) = 0;
  }
  local_38 = *puVar4;
  local_30 = *(undefined4 *)(this + 0xd4);
  local_a4 = *(float *)(this + 200);
  local_ac = *(undefined8 *)(this + 0xc0);
  if (DAT_0112a7a6 != '\0') {
    FUN_006c8f00(local_e8,deltaTime,*(undefined4 *)(this + 0x180),*(undefined4 *)(this + 0x184),
                 pfVar3,&local_38,&local_ac);
    fVar15 = local_ac._4_4_;
    if (bVar13) {
      fVar17 = DAT_00e44564 - *(float *)(this + 0x174);
      if (fVar17 < local_ac._4_4_) {
        fVar17 = *(float *)(this + 0x148);
LAB_006e3429:
        if (local_ac._4_4_ < fVar17) goto LAB_006e3431;
      }
LAB_006e342e:
      fVar15 = fVar17;
    }
    else if (bVar6) {
      fVar17 = DAT_00e44564 - *(float *)(this + 0x148);
      if (fVar17 < local_ac._4_4_) {
        fVar17 = *(float *)(this + 0x174);
        goto LAB_006e3429;
      }
      goto LAB_006e342e;
    }
LAB_006e3431:
    local_a4 = local_a4 * DAT_00e445c8;
    local_ac = CONCAT44(fVar15 * DAT_00e445c8,(float)local_ac * DAT_00e445c8);
  }
  local_7c = local_38;
  local_74 = local_30;
  fVar14 = (float10)FUN_006ca5e0(pfVar3,&local_7c,&local_7c);
  fVar15 = _DAT_00d5780c;
  local_e4 = (float)fVar14;
  *(undefined4 *)(this + 0x20) = (undefined4)local_7c;
  *(float *)(this + 0x2c) = fVar15;
  local_7c._4_4_ = (fVar15 - local_e4) * _DAT_00e51290 + local_7c._4_4_;
  fVar17 = (fVar15 - local_e4) * _DAT_00e5128c;
  *(float *)(this + 0x24) = local_7c._4_4_;
  *(undefined4 *)(this + 0x28) = local_74;
  *(float *)(this + 0x40) = (float)local_ac;
  *(float *)(this + 0x44) = local_ac._4_4_;
  pfVar1 = (float *)(this + 0x40);
  *(float *)(this + 0x48) = local_a4;
  *(float *)(this + 0x4c) = fVar15;
  *pfVar1 = fVar17 + *pfVar1;
  *(float *)(this + 0x30) = *pfVar3;
  *(undefined4 *)(this + 0x34) = *(undefined4 *)(this + 0xdc);
  *(float *)(this + 0x3c) = fVar15;
  *(undefined4 *)(this + 0x38) = *(undefined4 *)(this + 0xe0);
  if ((*(uint *)(local_bc + 0x249c) >> 0x18 & 1) == 0) {
    if ((((*(uint *)(local_bc + 0x249c) >> 0x17 & 1) != 0) ||
        ((*(uint *)(local_bc + 0x8e0) >> 9 & 1) != 0)) && (local_f2 == 0)) {
      local_70 = *(float *)(this + 0x30) - *(float *)(this + 0x20);
      fStack_6c = *(float *)(this + 0x34) - *(float *)(this + 0x24);
      fStack_68 = *(float *)(this + 0x38) - *(float *)(this + 0x28);
      fStack_64 = *(float *)(this + 0x3c) - *(float *)(this + 0x2c);
      local_e4 = SQRT(fStack_6c * fStack_6c + fStack_68 * fStack_68 + local_70 * local_70);
      dVar16 = (double)(deltaTime * _DAT_00d5f560 * _DAT_00e51288);
      FUN_00b99fcb();
      fVar15 = DAT_00e44564 - local_e4 * (float)dVar16;
      *(float *)(this + 0x34) = *(float *)(this + 0x34) + fVar15;
      *(float *)(this + 0xdc) = *(float *)(this + 0xdc) + fVar15;
      goto LAB_006e39e0;
    }
    fVar17 = ((local_a0 * _DAT_00e51284 + DAT_00d5efa0) - *(float *)(this + 0x164)) *
             *(float *)(this + 0x80) + *(float *)(this + 0x164);
    *(float *)(this + 0x50) =
         (((((*(float *)(this + 400) + local_a0 * _DAT_00e51284) - *(float *)(this + 0x194)) *
            *(float *)(this + 0x80) + *(float *)(this + 0x194)) - fVar17) *
          *(float *)(this + 0xf4) + fVar17) * DAT_00e445c8;
  }
  else {
    *(undefined4 *)(this + 0x50) = DAT_00d5f7b4;
    fVar17 = _DAT_00e51250 * DAT_00e445c8;
    local_d0 = *(float *)(this + 0x30) - *(float *)(this + 0x20);
    fStack_cc = *(float *)(this + 0x34) - *(float *)(this + 0x24);
    fStack_c8 = *(float *)(this + 0x38) - *(float *)(this + 0x28);
    fStack_c4 = *(float *)(this + 0x3c) - *(float *)(this + 0x2c);
    local_e4 = SQRT(fStack_cc * fStack_cc + fStack_c8 * fStack_c8 + local_d0 * local_d0);
    dVar16 = (double)fVar17;
    FUN_00b99fcb();
    fVar15 = _DAT_00d5780c;
    *pfVar1 = fVar17 + *pfVar1;
    fVar17 = DAT_00e44564 - local_e4 * (float)dVar16;
    *(float *)(this + 0x34) = *(float *)(this + 0x34) + fVar17;
    *(float *)(this + 0xdc) = *(float *)(this + 0xdc) + fVar17;
  }
  if (local_f2 != 0) {
    local_5c = *(float *)(DAT_01129944 + 0x10c);
    local_58 = *(float *)(DAT_01129944 + 0x110);
    local_d0 = *pfVar3;
    fStack_cc = *(float *)(this + 0xdc);
    fStack_c8 = *(float *)(this + 0xe0);
    local_90 = *(float *)(this + 0x20) - local_d0;
    fStack_8c = *(float *)(this + 0x24) - fStack_cc;
    fStack_88 = *(float *)(this + 0x28) - fStack_c8;
    fStack_84 = *(float *)(this + 0x2c) - fVar15;
    local_a0 = SQRT(fStack_8c * fStack_8c + fStack_88 * fStack_88 + local_90 * local_90);
    dVar16 = (double)*pfVar1;
    fStack_c4 = fVar15;
    FUN_00b99e20();
    fVar15 = ((float)dVar16 / local_58) * local_a0 * local_5c + fStack_cc;
    fVar18 = local_d0 - local_70;
    fStack_cc = fVar15 - fStack_6c;
    fVar19 = fStack_c8 - fStack_68;
    fVar17 = fVar19 * fVar19 + fStack_cc * fStack_cc + fVar18 * fVar18;
    if (fVar17 <= DAT_00d5f2b4) {
      fVar17 = 0.0;
    }
    else {
      fVar17 = _DAT_00d5780c / SQRT(fVar17);
    }
    fStack_cc = fStack_cc * fVar17;
    *(float *)(this + 0x20) = local_a0 * fVar18 * fVar17 + local_d0;
    *(float *)(this + 0x24) = local_a0 * fStack_cc + fVar15;
    *(float *)(this + 0x28) = local_a0 * fVar19 * fVar17 + fStack_c8;
    *(float *)(this + 0x2c) = local_a0 * (fStack_c4 - fStack_64) + fStack_c4;
    local_d0 = fVar18 * fVar17;
    fStack_c8 = fVar19 * fVar17;
    fStack_c4 = fStack_c4 - fStack_64;
    FUN_00473bc0((float *)(this + 0x20),this + 0x30,0,this + 0x44,pfVar1,this + 0x48);
    fVar17 = DAT_00e44600;
    fVar15 = DAT_00d5f4b4;
    fVar18 = (*pfVar1 - *(float *)(this + 0xc0)) * DAT_00e44748 + *(float *)(this + 0xfc);
    fVar19 = (*(float *)(this + 0x44) - *(float *)(this + 0xc4)) * DAT_00e44748 +
             *(float *)(this + 0x100);
    *(float *)(this + 0xfc) = fVar18;
    *(float *)(this + 0x100) = fVar19;
    if (fVar17 < fVar18) {
      *(float *)(this + 0xfc) = fVar18 - fVar15;
    }
    if (fVar17 < fVar19) {
      *(float *)(this + 0x100) = fVar19 - fVar15;
    }
    fVar17 = DAT_00d5f4b0;
    if (*(float *)(this + 0xfc) < DAT_00d5f4b0) {
      *(float *)(this + 0xfc) = *(float *)(this + 0xfc) + fVar15;
    }
    if (*(float *)(this + 0x100) < fVar17) {
      *(float *)(this + 0x100) = *(float *)(this + 0x100) + fVar15;
    }
    *(float *)(this + 0xc0) = *pfVar1;
    *(undefined4 *)(this + 0xcc) = *(undefined4 *)(this + 0x20);
    *(float *)(this + 0xc4) = *(float *)(this + 0x44);
    *(undefined4 *)(this + 0xd0) = *(undefined4 *)(this + 0x24);
    *(undefined4 *)(this + 0xd4) = *(undefined4 *)(this + 0x28);
  }
LAB_006e39e0:
  DAT_0112a914 = *(undefined4 *)(this + 0xf0);
  DAT_0112a918 = *(undefined4 *)(this + 0xf8);
  DAT_0112a91c = *(undefined4 *)(this + 0x100);
  DAT_0112a920 = *(undefined4 *)(this + 0xfc);
  DAT_0112a924 = *(undefined8 *)(this + 0xcc);
  DAT_0112a92c = *(undefined4 *)(this + 0xd4);
  DAT_0112a930 = *(undefined8 *)pfVar3;
  DAT_0112a938 = *(undefined4 *)(this + 0xe0);
  DAT_0112a93c = *(undefined8 *)(this + 0xc0);
  DAT_0112a944 = *(undefined4 *)(this + 200);
  DAT_0112a908 = *(undefined8 *)(this + 0x118);
  DAT_0112a910 = *(undefined4 *)(this + 0x120);
  return;
}