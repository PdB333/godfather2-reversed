// FUNC_NAME: SomeClass::setSomeValue
void __thiscall SomeClass::setSomeValue(int this, undefined4 param_2)
{
  // +0x9c: some state/type field
  if (*(int *)(this + 0x9c) == 0) {
    // +0xcc: value field
    *(undefined4 *)(this + 0xcc) = param_2;
    return;
  }
  // If state is 0x48 (72), just set value directly
  if (*(int *)(this + 0x9c) != 0x48) {
    // Call some processing function before setting value
    FUN_00731fe0(param_2);
    *(undefined4 *)(this + 0xcc) = param_2;
    return;
  }
  *(undefined4 *)(this + 0xcc) = param_2;
  return;
}