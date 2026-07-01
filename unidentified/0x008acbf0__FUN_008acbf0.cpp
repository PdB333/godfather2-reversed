// FUNC_NAME: SomeClass::initFromParams
void __thiscall SomeClass::initFromParams(int this, undefined4 param_2)
{
  // +0x10: some sub-object
  FUN_004bb870(param_2, this + 0x10);
  // +0x30: another sub-object (likely a string or buffer)
  FUN_00657d20(this + 0x30);
  // +0x34: yet another sub-object
  FUN_004bc0e0(param_2, this + 0x34);
  return;
}