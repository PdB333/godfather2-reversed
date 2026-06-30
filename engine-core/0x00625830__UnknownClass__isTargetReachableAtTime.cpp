// FUNC_NAME: UnknownClass::isTargetReachableAtTime
uint __fastcall UnknownClass::isTargetReachableAtTime(uint param_1, int param_2)
{
  int *piVar1;
  
  if (param_2 < 1) {
    piVar1 = (int *)FUN_00625430();
  }
  else {
    piVar1 = (int *)(*(int *)(in_EAX + 0xc) + -8 + param_2 * 8);
    if (*(int **)(in_EAX + 8) <= piVar1) {
      return 0;
    }
  }
  if ((piVar1 != (int *)0x0) && ((*piVar1 == 4 || (*piVar1 == 3)))) {
    return 1;
  }
  return 0;
}