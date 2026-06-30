// FUNC_NAME: SomeClass::delegateDispatch

int SomeClass::delegateDispatch(int* param_1, undefined4* param_2)
{
  if (param_1 != (int *)0x0) {
    FUN_00620210();
  }
  // Virtual call: dispatch to vtable entry +4, passing args from param_2
  // +0x00: param_2[0] (this pointer?)
  // +0x08: param_2[2]
  // +0x0C: param_2[3]
  // +0x10: param_2[4]
  (**(code **)(*param_1 + 4))(*param_2, param_2[2], param_2[3], param_2[4]);
  return 1;
}