// FUNC_NAME: EARSObject::updateTransform
void __thiscall EARSObject::updateTransform(float *this, float *param_2, float *param_3, float *param_4, char param_5, int *param_6)
{
  float *pfVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *local_40;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  pfVar1 = this + 0x11;
  *(undefined1 *)(this + 0x10) = 0;
  if (*pfVar1 != 0.0) {
    FUN_004daf90(pfVar1);
    *pfVar1 = 0.0;
  }
  if (this[0x46] != 0.0) {
    FUN_004daf90(this + 0x46);
    this[0x46] = 0.0;
  }
  local_2c = this[0x1f];
  local_28 = 0.0;
  if (local_2c != 0.0) {
    local_28 = *(float *)((int)local_2c + 4);
    *(float **)((int)local_2c + 4) = &local_2c;
  }
  local_24 = this[0x21];
  pfVar1 = this + 0x22;
  local_38 = *pfVar1;
  local_34 = 0.0;
  if (local_38 != 0.0) {
    local_34 = *(float *)((int)local_38 + 4);
    *(float **)((int)local_38 + 4) = &local_38;
  }
  local_30 = this[0x24];
  fVar7 = *param_2;
  if (fVar7 == 0.0) {
    local_40 = (float *)0x0;
  }
  else {
    local_40 = (float *)param_2[2];
  }
  if (param_5 == '\0') {
    FUN_005f5ce0();
    if (((param_6 != (int *)0x0) && (*param_6 != 0)) && (param_6[2] != 0)) {
      FUN_005f7ba0(param_6);
    }
    FUN_005f5ce0();
    if (pfVar1 != param_2) {
      fVar7 = *param_2;
      if (*pfVar1 != fVar7) {
        if (*pfVar1 != 0.0) {
          FUN_004daf90(pfVar1);
        }
        *pfVar1 = fVar7;
        if (fVar7 != 0.0) {
          this[0x23] = *(float *)((int)fVar7 + 4);
          *(float **)((int)fVar7 + 4) = pfVar1;
        }
      }
    }
    this[0x24] = param_2[2];
    this[0x18] = *param_3;
    this[0x19] = param_3[1];
    this[0x1a] = param_3[2];
  }
  else {
    pfVar1 = this + 0x1c;
    if ((pfVar1 != param_2) && (*pfVar1 != fVar7)) {
      if (*pfVar1 != 0.0) {
        FUN_004daf90(pfVar1);
      }
      *pfVar1 = fVar7;
      if (fVar7 != 0.0) {
        this[0x1d] = *(float *)((int)fVar7 + 4);
        *(float **)((int)fVar7 + 4) = pfVar1;
      }
    }
    this[0x1e] = param_2[2];
    if (this + 0x1f != pfVar1) {
      fVar7 = *pfVar1;
      if (this[0x1f] != fVar7) {
        if (this[0x1f] != 0.0) {
          FUN_004daf90(this + 0x1f);
        }
        this[0x1f] = fVar7;
        if (fVar7 != 0.0) {
          this[0x20] = *(float *)((int)fVar7 + 4);
          *(float **)((int)fVar7 + 4) = this + 0x1f;
        }
      }
    }
    this[0x21] = this[0x1e];
    this[0x18] = *local_40;
    this[0x19] = local_40[1];
    this[0x1a] = local_40[2];
    *param_3 = this[0x18];
    param_3[1] = this[0x19];
    param_3[2] = this[0x1a];
    FUN_005fe2e0(this,param_2,this + 0x22,0);
  }
  FUN_00414aa0();
  fVar7 = 0.0;
  this[0x38] = 0.0;
  this[0x30] = 0.0;
  this[0x44] = 0.0;
  this[0x43] = 0.0;
  if ((this[0x22] == 0.0) || ((float *)this[0x24] == (float *)0x0)) {
    this[0x2d] = (float)((uint)this[0x2d] | 1);
    this[0x3f] = 0.0;
    this[0x3e] = 0.0;
    this[0x3d] = 0.0;
    this[0x42] = 0.0;
    this[0x41] = 0.0;
    this[0x40] = 0.0;
    goto LAB_00600f97;
  }
  pfVar1 = (float *)this[0x24];
  if (param_5 == '\0') {
    pfVar1 = local_40;
  }
  local_20 = *pfVar1 - *this;
  fStack_1c = pfVar1[1] - this[1];
  fVar6 = pfVar1[2] - this[2];
  fStack_14 = fStack_14 - this[3];
  fVar4 = fStack_1c * fStack_1c + local_20 * local_20 + fVar6 * fVar6;
  fStack_18 = fVar7;
  if (DAT_00e2cbe0 < fVar4) {
    fVar7 = SQRT(fVar4);
    fStack_18 = DAT_00e2b1a4 / fVar7;
  }
  local_20 = fStack_18 * local_20;
  fStack_1c = fStack_18 * fStack_1c;
  fStack_18 = fStack_18 * fVar6;
  dVar3 = (double)local_20;
  this[0x31] = fVar7;
  FUN_00b9a9fa();
  fVar7 = (float)dVar3;
  this[0x3f] = fVar7;
  dVar3 = (double)fStack_1c;
  FUN_00b9a9fa();
  fVar4 = DAT_00e44564 - (float)dVar3;
  this[0x42] = fVar4;
  if ((param_4 == (float *)0x0) || (param_5 != '\0')) {
    this[0x3e] = fVar7;
    this[0x3d] = fVar7;
    this[0x41] = fVar4;
    this[0x40] = fVar4;
    if (param_4 != (float *)0x0) {
      *param_4 = local_20;
      param_4[1] = fStack_1c;
      param_4[2] = fStack_18;
    }
    goto LAB_00600f97;
  }
  dVar3 = (double)*param_4;
  FUN_00b9a9fa();
  fVar5 = DAT_00e44588;
  fVar6 = DAT_00e2afac;
  fVar4 = DAT_00e2a848;
  fVar2 = (float)dVar3;
  fVar7 = fVar7 - fVar2;
  this[0x3e] = fVar2;
  if (fVar7 <= fVar6) {
    if (fVar7 < fVar5) {
      fVar7 = fVar7 + fVar4;
    }
  }
  else {
    fVar7 = fVar7 - fVar4;
  }
  fVar2 = fVar2 - fVar7;
  this[0x3d] = fVar2;
  if (fVar2 <= fVar6) {
    if (fVar2 < fVar5) {
      fVar2 = fVar2 + fVar4;
      goto LAB_00600e29;
    }
  }
  else {
    fVar2 = fVar2 - fVar4;
LAB_00600e29:
    this[0x3d] = fVar2;
  }
  dVar3 = (double)param_4[1];
  FUN_00b9a9fa();
  fVar4 = DAT_00e2afac;
  fVar5 = DAT_00e44564 - (float)dVar3;
  fVar6 = this[0x42] - fVar5;
  this[0x41] = fVar5;
  fVar7 = DAT_00e2a848;
  if (fVar6 <= fVar4) {
    if (fVar6 < DAT_00e44588) {
      fVar6 = fVar6 + DAT_00e2a848;
    }
  }
  else {
    fVar6 = fVar6 - DAT_00e2a848;
  }
  fVar5 = fVar5 - fVar6;
  this[0x40] = fVar5;
  if (fVar5 <= fVar4) {
    if (fVar5 < DAT_00e44588) {
      fVar5 = fVar5 + fVar7;
      goto LAB_00600ee3;
    }
  }
  else {
    fVar5 = fVar5 - fVar7;
LAB_00600ee3:
    this[0x40] = fVar5;
  }
  fVar4 = this[0x31] * DAT_00e2cd54;
  this[0x3b] = fVar4;
  fVar7 = DAT_00e44968;
  if (0.0 < fVar4) {
    fVar7 = DAT_00e2b1a4 / fVar4;
  }
  this[0x3c] = fVar7;
  this[0x34] = 0.0;
  this[0x35] = 0.0;
  this[0x36] = 0.0;
  this[0x38] = 2.8026e-45;
LAB_00600f97:
  FUN_005f5ce0();
  if ((code *)this[0x29] != (code *)0x0) {
    (*(code *)this[0x29])(this,&local_2c,&local_38,this + 0x1f,this + 0x22);
  }
  if (local_38 != 0.0) {
    pfVar1 = *(float **)((int)local_38 + 4);
    if (pfVar1 == &local_38) {
      *(float *)((int)local_38 + 4) = local_34;
    }
    else {
      if ((float *)pfVar1[1] != &local_38) {
        do {
          pfVar1 = (float *)pfVar1[1];
        } while ((float *)pfVar1[1] != &local_38);
      }
      pfVar1[1] = local_34;
    }
  }
  if (local_2c != 0.0) {
    pfVar1 = *(float **)((int)local_2c + 4);
    if (pfVar1 == &local_2c) {
      *(float *)((int)local_2c + 4) = local_28;
      return;
    }
    if ((float *)pfVar1[1] != &local_2c) {
      do {
        pfVar1 = (float *)pfVar1[1];
      } while ((float *)pfVar1[1] != &local_2c);
    }
    pfVar1[1] = local_28;
  }
  return;
}