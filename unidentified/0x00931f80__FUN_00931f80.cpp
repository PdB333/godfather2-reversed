// FUNC_NAME: SomeClass::setSomeValue
void __thiscall SomeClass::setSomeValue(int this, undefined4 param_2)
{
  *(undefined4 *)(this + 0x60) = param_2; // +0x60: some member variable
  if ((DAT_01130590 & 1) == 0) {
    FUN_005c0d50(this + 0x14, &LAB_00931e00, 0); // likely a callback registration or initialization
    DAT_01130590 = DAT_01130590 | 1; // mark as initialized
  }
  return;
}