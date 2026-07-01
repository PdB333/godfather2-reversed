// FUNC_NAME: SomeClass::someMethod
undefined4 SomeClass::someMethod(undefined4 param_1)
{
  undefined4 uVar1;
  int local_10 [3];
  code *local_4;
  
  FUN_004d3bc0(param_1);
  uVar1 = FUN_0077aee0(local_10);
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]);
  }
  return uVar1;
}