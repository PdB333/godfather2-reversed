// FUNC_NAME: PlayerSM::checkTransitionCondition
undefined1 __thiscall PlayerSM::checkTransitionCondition(int this, int param_2, undefined4 param_3, int param_4, undefined4 param_5)
{
  float fVar1;
  int *piVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  undefined8 local_18;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  uVar4 = false;
  fVar1 = (float)param_2;
  if (param_2 < 0) {
    fVar1 = fVar1 + DAT_00e44578;
  }
  fVar1 = fVar1 * DAT_00d5efb8;
  switch(param_4 + -0xb) {
  case 0: // Transition ID 11
    return true;
  case 1: // Transition ID 12
  case 5: // Transition ID 16
  case 6: // Transition ID 17
  case 0xd: // Transition ID 24
    iVar6 = *(int *)(*(int *)(this + 0x50) + 0x70);
    if (iVar6 == 0) {
      return true;
    }
    return iVar6 == 0x48;
  case 2: // Transition ID 13
    cVar3 = FUN_0086d6d0();
    if ((cVar3 != '\0') && (cVar3 = FUN_0086ee10(fVar1), cVar3 != '\0')) {
      return true;
    }
    break;
  case 3: // Transition ID 14
  case 0xc: // Transition ID 23
    cVar3 = FUN_0086e440(1,0);
    return cVar3 == '\0';
  case 4: // Transition ID 15
    uVar4 = FUN_0086e680();
    return uVar4;
  case 7: // Transition ID 18
    if (((*(uint *)(this + 0x6c) >> 1 & 1) != 0) && (_DAT_00d577a0 < *(float *)(this + 0x30)))
    {
      return true;
    }
    break;
  case 8: // Transition ID 19
    cVar3 = FUN_0086d6d0();
    if ((cVar3 != '\0') && (cVar3 = FUN_0086e440(1,0), cVar3 != '\0')) {
      return true;
    }
    break;
  case 9: // Transition ID 20
    if (*(int *)(this + 0x5c) != 0) {
      return (byte)(*(uint *)(*(int *)(this + 0x5c) + 0xc88) >> 0xc) & 1;
    }
    break;
  case 10: // Transition ID 21
    return ~(*(byte *)(*(int *)(this + 0x50) + 200) >> 3) & 1;
  case 0xb: // Transition ID 22
    if (*(float *)(this + 0xa4) <= 0.0) {
      return true;
    }
    break;
  case 0xe: // Transition ID 25
    piVar2 = *(int **)(this + 0x5c);
    if ((piVar2 != (int *)0x0) && (piVar2[0x3cb] != 1)) {
      iVar6 = FUN_00471610();
      pfVar7 = (float *)(iVar6 + 0x30);
      iVar5 = FUN_00471610();
      local_10 = *(float *)(iVar5 + 0x28);
      local_18 = *(undefined8 *)(iVar5 + 0x20);
      iVar5 = FUN_00471610();
      local_c = *(float *)(iVar5 + 0x30) - *pfVar7;
      local_8 = *(float *)(iVar5 + 0x34) - *(float *)(iVar6 + 0x34);
      local_4 = *(float *)(iVar5 + 0x38) - *(float *)(iVar6 + 0x38);
      FUN_0043a210(&local_c,&local_c);
      FUN_0043a210(&local_18,&local_18);
      if (local_18._4_4_ * local_8 + (float)local_18 * local_c + local_10 * local_4 < DAT_00d75fb4)
      {
        cVar3 = FUN_006c0050(pfVar7,0,0);
        if (cVar3 != '\0') {
          if (*(float *)(this + 0xa0) < _DAT_00d5780c) {
            *(float *)(this + 0xa0) = *(float *)(this + 0xa0) + DAT_012067e8;
            return false;
          }
          local_c = DAT_00e44564 - (float)local_18;
          local_8 = DAT_00e44564 - local_18._4_4_;
          local_4 = DAT_00e44564 - local_10;
          (**(code **)(*piVar2 + 700))(pfVar7,&local_c,0);
          return false;
        }
        uVar4 = true;
      }
      *(undefined4 *)(this + 0xa0) = 0;
      return (bool)uVar4;
    }
    break;
  case 0xf: // Transition ID 26
    (**(code **)(**(int **)(this + 0x5c) + 0x1b0))();
    fVar1 = *(float *)(this + 0x30);
    if ((float10)_DAT_00d75f50 <= extraout_ST0) {
      if ((*(float *)(this + 0xb4) <= fVar1 && fVar1 != *(float *)(this + 0xb4)) &&
         (DAT_00d5eee4 < fVar1)) {
        return true;
      }
    }
    else if ((fVar1 < DAT_00d58cbc) || (*(float *)(this + 0xb4) <= fVar1)) {
      return true;
    }
    break;
  case 0x10: // Transition ID 27
    iVar6 = FUN_00471610();
    FUN_006bff90(iVar6 + 0x30);
    if ((float10)_DAT_00d75f30 < extraout_ST0_00) {
      return true;
    }
    if (_DAT_00d75f34 < (float)extraout_ST0_00) {
      cVar3 = FUN_006c0050(iVar6 + 0x30,0,0);
      if (cVar3 != '\0') {
        return true;
      }
      return false;
    }
    return false;
  case 0x11: // Transition ID 28
    uVar4 = FUN_0086ebc0();
    return uVar4;
  case 0x12: // Transition ID 29
    (**(code **)(**(int **)(this + 0x5c) + 0x1b0))();
    if (extraout_ST0_01 < (float10)_DAT_00d75cf0) {
      return true;
    }
    break;
  case 0x13: // Transition ID 30
    cVar3 = FUN_0086ebc0();
    return cVar3 == '\0';
  default:
    uVar4 = FUN_0086b010(param_2,param_3,param_4,param_5);
  }
  return uVar4;
}