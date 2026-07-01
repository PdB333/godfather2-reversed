// FUNC_NAME: SomeClass::checkSomeCondition
undefined4 __thiscall FUN_008155a0(int this, char *param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(this + 0x5c) != 0) {
    if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
      uVar1 = FUN_004d4b70();
      return uVar1;
    }
    if (*(int *)(this + 0x5c) != 0) {
      return 0xffffffff;
    }
  }
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    return 1;
  }
  return 0;
}