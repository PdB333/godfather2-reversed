// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int thisPtr, int param2, char param3)
{
  if (*(int *)(thisPtr + 0x60) != 0) {
    FUN_004bb620(&stack0x0000000c);
    if (param3 != '\0') {
      *(uint *)(thisPtr + 0x7c) = *(uint *)(thisPtr + 0x7c) | 0x80;
      FUN_008a9d20(0xffffffff);
      FUN_00407430();
      return;
    }
    FUN_008a9b20(param2 + 1);
  }
  FUN_00407430();
  return;
}