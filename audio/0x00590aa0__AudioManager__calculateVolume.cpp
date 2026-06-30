// FUNC_NAME: AudioManager::calculateVolume
float AudioManager::calculateVolume(int param_2, int *param_3)
{
  float fVar1;
  uint uVar2;
  int *piVar3;
  float fVar4;
  float fVar5;
  
  piVar3 = param_3;
  FUN_00591440(this, param_2, param_3);
  uVar2 = *(uint *)(*(int *)(param_2 + 4) + 0xc);
  if ((uint)piVar3[1] <= uVar2) {
    param_3 = (int *)0x0;
    FUN_00591c00(&param_3);
  }
  fVar1 = *(float *)(*piVar3 + uVar2 * 4);
  if (*(char *)(param_2 + 1) < '\x02') {
    return (float10)DAT_00e2b1a4;
  }
  fVar4 = fVar1;
  FUN_00591160();
  param_3 = (int *)fVar4;
  FUN_00591160();
  if (fVar1 <= 0.0) {
    return (float10)(float)param_3;
  }
  fVar5 = fVar4;
  if ((fVar1 < DAT_00e2b1a4) && (fVar5 = (float)param_3, (float)param_3 != fVar4)) {
    return (float10)((fVar4 - (float)param_3) * fVar1 + (float)param_3);
  }
  return (float10)fVar5;
}