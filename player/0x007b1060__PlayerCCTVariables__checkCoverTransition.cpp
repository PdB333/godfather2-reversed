// FUNC_NAME: PlayerCCTVariables::checkCoverTransition
undefined4 FUN_007b1060(int *this, int *otherEntity)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  float fStack_10;
  float local_c;
  float local_8;
  float local_4;
  
  piVar1 = otherEntity;
  if (otherEntity == (int *)0x0) {
    return 2;
  }
  cVar2 = FUN_007afbc0(this,otherEntity);
  if (cVar2 != '\0') {
    return 0;
  }
  cVar2 = FUN_00800c10();
  if (cVar2 == '\0') {
    return 0;
  }
  iVar3 = FUN_00471610();
  local_c = DAT_00e44564 - *(float *)(iVar3 + 0x20);
  local_8 = DAT_00e44564 - *(float *)(iVar3 + 0x24);
  local_4 = DAT_00e44564 - *(float *)(iVar3 + 0x28);
  fVar6 = (float10)(**(code **)(*otherEntity + 0x214))();
  otherEntity = (int *)(float)((float10)DAT_00d5eeec - fVar6);
  fVar6 = (float10)(**(code **)(*this + 0x214))();
  fStack_10 = (float)fVar6;
  cVar2 = FUN_00481660();
  if ((cVar2 != '\0') || (cVar2 = FUN_00481640(), cVar2 != '\0')) {
    otherEntity = (int *)_DAT_00d6bf98;
    fStack_10 = _DAT_00d6bf98;
  }
  cVar2 = (char)piVar1[0x6e3];
  if ((cVar2 != '\0') && (cVar2 != '\x01')) {
    cVar2 = FUN_00481640();
    if ((cVar2 == '\0') && (cVar2 = FUN_00481660(), cVar2 == '\0')) {
      return 2;
    }
    if ((char)piVar1[0x6e3] != '\x04') {
      return 2;
    }
  }
  iVar3 = FUN_00471610();
  iVar4 = FUN_00471610();
  cVar2 = FUN_007f7f30(iVar4 + 0x30,iVar3 + 0x30,&local_c,param_2);
  if (cVar2 == '\0') {
    return 2;
  }
  iVar3 = FUN_00471610();
  iVar4 = FUN_00471610();
  iVar5 = FUN_00471610();
  cVar2 = FUN_007f7f30(iVar5 + 0x30,iVar4 + 0x30,iVar3 + 0x20,fStack_10);
  if ((cVar2 != '\0') && (cVar2 = FUN_00800c10(), cVar2 != '\0')) {
    return 1;
  }
  return 2;
}