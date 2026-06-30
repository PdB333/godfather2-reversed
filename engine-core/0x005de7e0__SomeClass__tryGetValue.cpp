// FUNC_NAME: SomeClass::tryGetValue
undefined4 SomeClass::tryGetValue(undefined4 param_1, undefined4 param_2, undefined4 *param_3)

{
  undefined4 in_EAX;
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_005dc670(in_EAX);
  if (iVar1 != 0) {
    uVar2 = FUN_005dd910(param_2);
    *param_3 = uVar2;
    return 1;
  }
  return 0;
}