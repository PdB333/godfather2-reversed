// FUNC_NAME: AudioManager::processSoundEvent
void AudioManager::processSoundEvent(int param_1, int* param_2, float* param_3, float* param_4, float* param_5,
                 int* param_6, int param_7, float param_8)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  int *puVar4;
  float fVar5;
  double dVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int *piVar10;
  long long uVar11;
  int *local_184;
  int *piStack_180;
  char cStack_179;
  int *local_178;
  int local_174;
  float fStack_170;
  float fStack_16c;
  float fStack_168;
  float fStack_160;
  float fStack_15c;
  float fStack_158;
  float fStack_154;
  short uStack_148;
  int uStack_134;
  float fStack_130;
  float fStack_12c;
  float fStack_128;
  int uStack_124;
  int uStack_120;
  int uStack_11c;
  int uStack_118;
  int uStack_114;
  float fStack_110;
  int uStack_10c;
  int uStack_108;
  int uStack_104;
  int uStack_100;
  float fStack_fc;
  int uStack_f8;
  int uStack_f4;
  int uStack_f0;
  int uStack_ec;
  float fStack_e8;
  int uStack_e4;
  int uStack_e0;
  int uStack_dc;
  int uStack_d8;
  float fStack_d4;
  float fStack_d0;
  int uStack_cc;
  int uStack_c8;
  int uStack_c4;
  int uStack_c0;
  float fStack_bc;
  int uStack_b8;
  int uStack_b4;
  int uStack_b0;
  int uStack_ac;
  float fStack_a8;
  int uStack_a4;
  int uStack_a0;
  int uStack_9c;
  int uStack_98;
  float fStack_94;
  float fStack_90;
  int uStack_8c;
  int uStack_88;
  int uStack_84;
  int uStack_80;
  float fStack_7c;
  int uStack_78;
  int uStack_74;
  int uStack_70;
  int uStack_6c;
  float fStack_68;
  int uStack_64;
  int uStack_60;
  int uStack_5c;
  int uStack_58;
  float fStack_54;
  float fStack_50;
  int uStack_4c;
  int uStack_48;
  int uStack_44;
  int uStack_40;
  float fStack_3c;
  int uStack_38;
  int uStack_34;
  int uStack_30;
  int uStack_2c;
  float fStack_28;
  int uStack_24;
  int uStack_20;
  int uStack_1c;
  int uStack_18;
  float fStack_14;
  
  fVar5 = param_3[8];
  if (*(int *)(*param_2 + 0xc) == 0xb) {
    fVar5 = param_3[9];
  }
  local_178 = (int *)FUN_005566a0(param_2,fVar5);
  if ((local_178 == (int *)0x0) &&
     ((((param_6 == (int *)0x0 ||
        (local_184 = local_178, cVar2 = (**(code **)(*param_6 + 0x10))(0x55859efa,&local_184),
        cVar2 == '\\0')) || (local_184 == (int *)0x0)) ||
      (local_178 = (int *)FUN_007f7de0(param_7), local_178 == (int *)0x0)))) {
    local_174 = 1;
  }
  else {
    local_174 = *local_178;
  }
  iVar3 = FUN_00541470(param_2[7]);
  if (iVar3 == 9) {
    local_174 = 0x67;
  }
  else if (((local_174 == 0x65) || (local_174 == 100)) && (param_6 != (int *)0x0)) {
    local_184 = (int *)0x0;
    cVar2 = (**(code **)(*param_6 + 0x10))(0x55859efa,&local_184);
    if (((cVar2 != '\\0') && (local_184 != (int *)0x0)) && (((uint)local_184[0x208] >> 3 & 1) != 0))
    {
      local_174 = 1;
    }
  }
  else if ((local_174 == 0x69) && (0.0 < param_8)) {
    fStack_130 = *param_5;
    fStack_12c = param_5[1];
    fStack_128 = param_5[2];
    fVar9 = fStack_130 - *param_4;
    fVar7 = fStack_12c - param_4[1];
    fVar8 = fStack_128 - param_4[2];
    fVar5 = fVar9 * fVar9 + fVar8 * fVar8 + fVar7 * fVar7;
    uStack_124 = 0;
    if (fVar5 == 0.0) {
      param_8 = DAT_00e44564 - param_8;
      fStack_160 = *param_3 * param_8;
      fStack_15c = param_3[1] * param_8;
      fStack_158 = param_3[2] * param_8;
      fStack_154 = param_3[3] * param_8;
    }
    else {
      fVar5 = _DAT_00d5780c / SQRT(fVar5);
      fStack_160 = fVar5 * fVar9 * param_8;
      fStack_15c = fVar7 * fVar5 * param_8;
      fStack_158 = fVar8 * fVar5 * param_8;
      fStack_154 = fVar5 * 0.0 * param_8;
    }
    FUN_005417d0();
  }
  local_184 = (int *)0x1ff;
  if (param_6 == (int *)0x0) {
    if (local_178 != (int *)0x0) {
      local_184 = (int *)((-(uint)((local_178[1] & 0x800U) != 0) & 0xffffffc0) + 0x80);
    }
  }
  else {
    local_184 = (int *)(**(code **)(*param_6 + 0x58))();
  }
  puVar4 = (int *)FUN_004352c0();
  uStack_120 = *puVar4;
  uStack_11c = puVar4[1];
  uStack_118 = puVar4[2];
  uStack_114 = puVar4[3];
  if (((iVar3 == 5) || (iVar3 == 0xe)) || (iVar3 == 0x10)) {
    fStack_160 = *param_5 - *param_4;
    fStack_15c = param_5[1] - param_4[1];
    fStack_158 = param_5[2] - param_4[2];
    local_178 = (int *)CONCAT31(local_178._1_3_,1);
  }
  else {
    fStack_160 = *param_4 - *param_5;
    fStack_15c = param_4[1] - param_5[1];
    fStack_158 = param_4[2] - param_5[2];
    local_178 = (int *)((uint)local_178._1_3_ << 8);
  }
  fStack_154 = 0.0;
  FUN_0056afa0(&fStack_160,&fStack_160);
  fStack_170 = fStack_160;
  uVar11 = CONCAT44(&fStack_130,param_3);
  fStack_16c = fStack_15c;
  fStack_168 = fStack_158;
  piVar10 = local_178;
  FUN_00851d10();
  fStack_d0 = _DAT_00d5780c;
  uStack_cc = 0;
  uStack_c8 = 0;
  uStack_c4 = 0;
  fStack_110 = _DAT_00d5780c;
  uStack_10c = 0;
  uStack_108 = 0;
  uStack_104 = 0;
  uStack_c0 = 0;
  fStack_bc = _DAT_00d5780c;
  uStack_b8 = 0;
  uStack_b4 = 0;
  uStack_100 = 0;
  fStack_fc = _DAT_00d5780c;
  uStack_f8 = 0;
  uStack_f4 = 0;
  uStack_b0 = 0;
  uStack_ac = 0;
  fStack_a8 = _DAT_00d5780c;
  uStack_a4 = 0;
  uStack_f0 = 0;
  uStack_ec = 0;
  fStack_e8 = _DAT_00d5780c;
  uStack_e4 = 0;
  uStack_a0 = 0;
  uStack_9c = 0;
  uStack_98 = 0;
  fStack_94 = _DAT_00d5780c;
  uStack_e0 = 0;
  uStack_dc = 0;
  uStack_d8 = 0;
  fStack_d4 = _DAT_00d5780c;
  FUN_00851a40(&fStack_d0,&fStack_170,param_5,piVar10,uVar11);
  FUN_00851a40(&fStack_110,&fStack_130,param_5);
  fStack_90 = fStack_d0;
  uStack_80 = uStack_c0;
  uStack_8c = uStack_cc;
  fStack_7c = fStack_bc;
  uStack_88 = uStack_c8;
  uStack_78 = uStack_b8;
  uStack_84 = 0;
  uStack_74 = 0;
  uStack_70 = uStack_b0;
  fStack_50 = fStack_110;
  uStack_4c = uStack_10c;
  uStack_48 = uStack_108;
  uStack_6c = uStack_ac;
  uStack_40 = uStack_100;
  fStack_68 = fStack_a8;
  fStack_3c = fStack_fc;
  uStack_64 = 0;
  uStack_60 = uStack_a0;
  uStack_44 = 0;
  uStack_38 = uStack_f8;
  uStack_34 = 0;
  uStack_24 = 0;
  uStack_5c = uStack_9c;
  uStack_30 = uStack_f0;
  uStack_20 = uStack_e0;
  uStack_58 = uStack_98;
  uStack_2c = uStack_ec;
  uStack_1c = uStack_dc;
  fStack_54 = _DAT_00d5780c;
  fStack_28 = fStack_e8;
  uStack_18 = uStack_d8;
  fStack_14 = _DAT_00d5780c;
  if (((iVar3 == 1) || (iVar3 == 5)) ||
     ((iVar3 == 0xe ||
      (((iVar3 == 0x10 || (iVar3 == 8)) ||
       (fStack_170 = (float)((uint)fStack_170 & 0xffffff00), iVar3 == 0x12)))))) {
    fStack_170 = (float)CONCAT31(fStack_170._1_3_,1);
  }
  if ((iVar3 == 1) || (iVar3 == 8)) {
    cVar2 = '\\0';
  }
  else {
    cVar2 = '\\x01';
  }
  uStack_134 = CONCAT31(uStack_134._1_3_,cVar2);
  dVar6 = (double)(float)((uint)(fStack_158 * fStack_128 + fStack_15c * fStack_12c +
                                fStack_160 * fStack_130) & DAT_00e44680);
  FUN_00b9b988(&fStack_50,&fStack_90);
  FUN_00853630(&piStack_180,param_6,fStack_170,uStack_134,(float)dVar6);
  piVar10 = DAT_0112de00;
  if (DAT_0112de00 != (int *)0x0) {
    *(char *)(DAT_0112de00 + 2) = local_178._0_1_;
    if (*piVar10 != 0) {
      piVar1 = (int *)(*piVar10 + 4);
      *piVar1 = *piVar1 + -1;
      if (((int *)*piVar10)[1] == 0) {
        (**(code **)(*(int *)*piVar10 + 4))();
      }
      *piVar10 = 0;
    }
    *piVar10 = (int)piStack_180;
    if (piStack_180 != (int *)0x0) {
      piStack_180[1] = piStack_180[1] + 1;
    }
    *(short *)((int)piVar10 + 6) = (short)local_174;
  }
  if ((cVar2 != '\\0') && ((int)(char)param_2[4] + (int)param_2 != 0)) {
    FUN_004af8c0(&fStack_170,0x2005);
    fVar5 = 0.0;
    if (fStack_170 != 0.0) {
      fVar5 = fStack_170;
    }
    if (((fVar5 != 0.0) && (*(int *)((int)fVar5 + 4) != 0)) &&
       (iVar3 = FUN_009c8e50(0x34), iVar3 != 0)) {
      (**(code **)(*param_6 + 0x58))(&piStack_180);
      puVar4 = (int *)FUN_004150c0();
      if (puVar4 != (int *)0x0) {
        cStack_179 = FUN_004a44a0(fVar5,puVar4);
        if (cStack_179 == '\\0') {
          (**(code **)*puVar4)(1);
        }
        else {
          FUN_00853540(fVar5);
          FUN_004a4bd0(&fStack_160);
          piVar10 = DAT_0112de00;
          if (DAT_0112de00 != (int *)0x0) {
            *(short *)((int)DAT_0112de00 + 6) = uStack_148;
            *(char *)((int)piVar10 + 9) = 1;
            FUN_0043a750(*(int *)((int)fVar5 + 4) + 0xc);
          }
        }
        if (cStack_179 != '\\0') goto LAB_0085572c;
      }
    }
  }
  FUN_0044b4e0(&fStack_110,&fStack_d0);
  piVar10 = local_184;
  if (piStack_180 != (int *)0x0) {
    piStack_180[1] = piStack_180[1] + 1;
  }
  cVar2 = FUN_00854b50(&fStack_110,CONCAT44(uStack_11c,uStack_120),CONCAT44(uStack_114,uStack_118),
                       local_184,piStack_180);
  if ((cVar2 != '\\0') && (DAT_0112de00 != (int *)0x0)) {
    *(short *)(DAT_0112de00 + 1) = (short)piVar10;
  }
LAB_0085572c:
  if ((piStack_180 != (int *)0x0) && (piStack_180[1] = piStack_180[1] + -1, piStack_180[1] == 0)) {
    (**(code **)(*piStack_180 + 4))();
  }
  return;
}