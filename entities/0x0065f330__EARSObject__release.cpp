// FUNC_NAME: EARSObject::release
undefined1 EARSObject::release(int *param_1)

{
  int *piVar1;
  undefined1 uVar2;
  int in_EAX;
  
  if (*(char *)(in_EAX + 0x24) == '\0') {
    if (param_1 != (int *)0x0) {
      piVar1 = param_1 + 2;
      *piVar1 = *piVar1 + -1;
      if (*piVar1 == 0) {
        (**(code **)(*param_1 + 8))();
      }
    }
    return 0;
  }
  uVar2 = FUN_0065e7b0(param_1);
  FUN_0064b440();
  if (param_1 != (int *)0x0) {
    piVar1 = param_1 + 2;
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
      (**(code **)(*param_1 + 8))();
    }
  }
  return uVar2;
}