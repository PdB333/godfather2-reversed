// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(undefined4 param_1, undefined4 param_2)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  uVar3 = 0;
  uVar2 = 0;
  uVar1 = FUN_00445f00(param_1); // Get some value from param_1
  FUN_00856780(param_2, uVar1, uVar2, uVar3, uVar4); // Call with param_2 and the value
  return;
}