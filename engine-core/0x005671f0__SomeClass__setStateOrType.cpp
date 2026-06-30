// FUNC_NAME: SomeClass::setStateOrType
void __thiscall setStateOrType(int this, undefined4 param_2)
{
  *(undefined4 *)(this + 0x18) = param_2;  // +0x18: some state/type value
  *(undefined1 *)(this + 0x14) = 2;        // +0x14: sub-state/flag (set to 2)
  *(undefined4 *)(this + 0x10) = 9;        // +0x10: main state/type (set to 9)
  return;
}