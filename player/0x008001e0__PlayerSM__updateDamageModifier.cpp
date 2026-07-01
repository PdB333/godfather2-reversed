// FUNC_NAME: PlayerSM::updateDamageModifier
int __thiscall PlayerSM::updateDamageModifier(PlayerSM *this, float param_2)
{
  float fVar1;
  float fVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  float10 fVar7;
  int local_4;
  
  fVar1 = param_2;
  local_4 = 0;
  if (((((((uint)this[0x23a] >> 10 & 1) == 0) && (*(int *)((int)param_2 + 0xc) != 0)) &&
       (iVar5 = *(int *)((int)param_2 + 0xc) + -0x48, iVar5 != 0)) &&
      ((cVar3 = FUN_00481640(), cVar3 == '\0' && (cVar3 = FUN_00481660(), cVar3 == '\0')))) &&
     (cVar3 = (**(code **)(*this + 0x228))(iVar5), cVar3 != '\0')) {
    *(undefined4 *)((int)fVar1 + 0x2c) = 0;
    local_4 = 1;
    uVar4 = FUN_0084d420(*(undefined4 *)((int)fVar1 + 0x30));
    if (((uVar4 & 1) != 0) ||
       (uVar4 = FUN_0084d420(*(undefined4 *)((int)fVar1 + 0x30)), (uVar4 & 2) != 0)) {
      local_4 = 2;
    }
  }
  if (*(float *)((int)fVar1 + 0x2c) <= 0.0 && *(float *)((int)fVar1 + 0x2c) != 0.0) {
    *(undefined4 *)((int)fVar1 + 0x2c) = 0;
    local_4 = 1;
  }
  if (((*(int *)((int)fVar1 + 0xc) != 0) && (*(int *)((int)fVar1 + 0xc) != 0x48)) &&
     (this[0x7bd] != -1)) {
    if (*(int *)((int)fVar1 + 0xc) == 0) {
      piVar6 = (int *)0x0;
    }
    else {
      piVar6 = (int *)(*(int *)((int)fVar1 + 0xc) + -0x48);
    }
    param_2 = 0.0;
    cVar3 = (**(code **)(*piVar6 + 0x10))(0x55859efa,&param_2);
    if (((cVar3 != '\0') && (param_2 != 0.0)) &&
       ((*(int *)((int)param_2 + 0x1ef4) == this[0x7bd] &&
        ((*(int *)(DAT_0112b9b4 + 0x40) != 0 &&
         (iVar5 = FUN_007fa620(*(int *)(DAT_0112b9b4 + 0x40),0x5ade71cd), iVar5 != 0)))))) {
      *(float *)((int)fVar1 + 0x2c) = *(float *)(iVar5 + 0x1b8) * *(float *)((int)fVar1 + 0x2c);
    }
  }
  if (*(int *)((int)fVar1 + 0x30) == 2) {
    piVar6 = (int *)FUN_0043b870(DAT_01131040);
    if (((uint)this[0x238] >> 4 & 1) != 0) {
      param_2 = 0.0;
      cVar3 = (**(code **)(*this + 0x10))(0x383225a1,&param_2);
      if ((((cVar3 != '\0') && (param_2 != 0.0)) ||
          ((piVar6 != (int *)0x0 &&
           ((cVar3 = FUN_006eb940(), cVar3 != '\0' &&
            (cVar3 = (**(code **)(*piVar6 + 0x1c))(0x100), cVar3 != '\0')))))) &&
         ((iVar5 = **(int **)(DAT_012233a0 + 4), iVar5 != 0 && (iVar5 != 0x1f30)))) {
        *(float *)((int)fVar1 + 0x2c) = *(float *)(iVar5 + 0xd4) * *(float *)((int)fVar1 + 0x2c);
      }
    }
    if (((this[0x7b5] == 0x637b907) && (*(int *)((int)fVar1 + 0xc) != 0)) &&
       (*(int *)((int)fVar1 + 0xc) != 0x48)) {
      if (*(int *)((int)fVar1 + 0xc) == 0) {
        piVar6 = (int *)0x0;
      }
      else {
        piVar6 = (int *)(*(int *)((int)fVar1 + 0xc) + -0x48);
      }
      param_2 = 0.0;
      cVar3 = (**(code **)(*piVar6 + 0x10))(0x55859efa,&param_2);
      fVar2 = param_2;
      if (((cVar3 != '\0') && (param_2 != 0.0)) && (cVar3 = FUN_00481660(), cVar3 == '\0')) {
        fVar7 = (float10)FUN_008c7630(*(undefined4 *)((int)fVar2 + 0x1ed4));
        param_2 = (float)fVar7;
        if (fVar7 != (float10)1) {
          *(float *)((int)fVar1 + 0x2c) = *(float *)((int)fVar1 + 0x2c) * param_2;
        }
      }
    }
  }
  if (((*(int *)((int)fVar1 + 0x38) != 6) && (local_4 != 4)) &&
     ((*(int *)((int)fVar1 + 0x30) != 0xb && (*(int *)((int)fVar1 + 0x30) != 1)))) {
    *(float *)((int)fVar1 + 0x2c) = (float)this[0x75a] * *(float *)((int)fVar1 + 0x2c);
  }
  if ((((uint)this[0x238] >> 0xb & 1) != 0) || (((uint)this[0x239] >> 0xd & 1) != 0)) {
    FUN_00800040(DAT_01205228,fVar1);
  }
  return local_4;
}