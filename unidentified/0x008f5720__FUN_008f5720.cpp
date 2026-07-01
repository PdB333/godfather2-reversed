// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int param_1, undefined4 param_2, undefined4 param_3)
{
  FUN_008f4160();
  FUN_008f5190();
  FUN_008f2200(5, param_2, param_3, 1);
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & 0xffffefff;
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 0x4000;
  FUN_008f37a0();
  return;
}