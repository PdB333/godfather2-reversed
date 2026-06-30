// FUNC_NAME: RefCounted::release
undefined1 * __fastcall FUN_004e8550(undefined4 param_1, undefined4 param_2, int *param_3)
{
  int *piVar1;
  char cVar2;
  undefined4 local_4;
  
  local_4 = 0;
  if (param_3 != (int *)0x0) {
    cVar2 = (**(code **)(*param_3 + 8))(param_2);
    if (cVar2 != '\0') {
      piVar1 = param_3 + 1;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        (**(code **)(*param_3 + 4))();
      }
      return (undefined1 *)&local_4;
    }
    piVar1 = param_3 + 1;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)(*param_3 + 4))();
    }
  }
  return (undefined1 *)0x0;
}