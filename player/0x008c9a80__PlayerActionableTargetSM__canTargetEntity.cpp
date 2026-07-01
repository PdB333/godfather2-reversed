// FUNC_NAME: PlayerActionableTargetSM::canTargetEntity
undefined4 __thiscall PlayerActionableTargetSM::canTargetEntity(int this, int *targetEntity)
{
  int *piVar1;
  char cVar2;
  undefined1 uVar3;
  bool bVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  undefined4 uStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  
  piVar1 = targetEntity;
  uStack_1c = (float)CONCAT13(1,(undefined3)uStack_1c);
  if (*(int *)(this + 8) == 0) {
    piVar5 = (int *)0x0;
  }
  else {
    piVar5 = (int *)(*(int *)(this + 8) + -0x48);
  }
  if (targetEntity == piVar5) {
    return 0;
  }
  if ((*(int *)(this + 8) != 0) && (*(int *)(this + 8) != 0x48)) {
    if (*(int *)(this + 8) == 0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)(*(int *)(this + 8) + -0x48);
    }
    targetEntity = (int *)0x0;
    cVar2 = (**(code **)(*piVar5 + 0x10))(0x55859efa,&targetEntity);
    if ((cVar2 != '\0') && (targetEntity != (int *)0x0)) {
      if (((uint)targetEntity[0x238] >> 4 & 1) != 0) {
        return 0;
      }
      if (((uint)targetEntity[0x238] >> 1 & 1) != 0) {
        return 0;
      }
      cVar2 = FUN_00800c10();
      if (cVar2 != '\0') {
        return 0;
      }
    }
  }
  switch(*(int *)(this + 0x40) + -1) {
  case 0:
    iVar6 = FUN_00713340(piVar1,0x369ac561);
    if (iVar6 == 0) {
      return 0;
    }
    cVar2 = FUN_00690150(0x30);
    goto joined_r0x008c9c36;
  case 1:
    iVar6 = FUN_00713340(piVar1,0x369ac561);
    if (iVar6 == 0) {
      return 0;
    }
    uVar3 = FUN_00690150(0x30);
    targetEntity = (int *)CONCAT31(targetEntity._1_3_,uVar3);
    iVar6 = FUN_007e5080(iVar6);
    if ((iVar6 == 0) || (cVar2 = FUN_0071ec90(0), cVar2 == '\0')) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    if (((char)targetEntity == '\0') && (!bVar4)) {
      return 0;
    }
    uStack_1c = (float)CONCAT13((char)targetEntity == '\0',(undefined3)uStack_1c);
    break;
  case 2:
    iVar6 = FUN_006dc8e0(piVar1,0x383225a1);
    if (iVar6 == 0) {
      return 0;
    }
    cVar2 = FUN_00690150(0x30);
    if (cVar2 == '\0') {
      return 0;
    }
    if ((*(int *)(this + 8) != 0) && (*(int *)(this + 8) != 0x48)) {
      if (*(int *)(this + 8) == 0) {
        iVar6 = 0;
      }
      else {
        iVar6 = *(int *)(this + 8) + -0x48;
      }
      iVar6 = FUN_00713340(iVar6,0x369ac561);
      if ((iVar6 != 0) && (cVar2 = FUN_00690150(0x30), cVar2 == '\0')) {
        return 0;
      }
    }
    uStack_1c = (float)((uint)uStack_1c & 0xffffff);
    break;
  case 4:
    iVar6 = FUN_00713340(piVar1,0x369ac561);
    if (iVar6 == 0) {
      return 0;
    }
    cVar2 = FUN_00690150(0x30);
joined_r0x008c9c36:
    if (cVar2 != '\0') {
      return 0;
    }
  }
  if (uStack_1c._3_1_ == '\0') {
    return 1;
  }
  FUN_008c98a0(&fStack_c);
  (**(code **)(*piVar1 + 0x4c))(&fStack_18);
  uStack_1c = uStack_1c * DAT_00d5eee4;
  fStack_18 = fStack_18 * DAT_00d5eee4;
  fStack_14 = fStack_14 * DAT_00d5eee4;
  iVar6 = FUN_00471610();
  uStack_1c = (*(float *)(iVar6 + 0x30) + uStack_1c) - fStack_10;
  fStack_14 = (*(float *)(iVar6 + 0x38) + fStack_14) - fStack_8;
  fVar9 = (*(float *)(iVar6 + 0x34) + fStack_18) - fStack_c;
  if ((*(int *)(this + 0x40) == 4) ||
     (fStack_14 * fStack_14 + uStack_1c * uStack_1c + fVar9 * fVar9 <=
      *(float *)(this + 0x2c) * *(float *)(this + 0x2c))) {
    fStack_18 = 0.0;
    FUN_0043a210(&uStack_1c,&uStack_1c);
    iVar6 = FUN_00471610();
    FUN_0043a210(&fStack_10,iVar6 + 0x20);
    if (fStack_10 * uStack_1c + fStack_c * fStack_18 + fStack_8 * fStack_14 <
        DAT_00e44564 - (float)targetEntity) {
      if ((*(byte *)(this + 0x34) & 1) == 0) {
        return 1;
      }
      iVar6 = FUN_00471610();
      iVar7 = FUN_00471610();
      iVar8 = FUN_00471610();
      if (*(float *)(iVar7 + 0x24) * *(float *)(this + 0x24) +
          *(float *)(this + 0x20) * *(float *)(iVar6 + 0x20) +
          *(float *)(iVar8 + 0x28) * *(float *)(this + 0x28) < 0.0) {
        return 1;
      }
    }
  }
  return 0;
}