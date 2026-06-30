// FUNC_NAME: SomeClass::allocateOrCreateSomething
undefined4 FUN_00685e60(undefined4 param_1, undefined4 param_2)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;
  iVar1 = FUN_0043b980(0x230, &local_c, param_2);
  if (iVar1 != 0) {
    uVar2 = FUN_00902b20(param_1);
    return uVar2;
  }
  return 0;
}