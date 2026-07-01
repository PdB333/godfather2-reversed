// FUNC_NAME: SomeClass::setSomeFlag
void __fastcall SomeClass::setSomeFlag(int this)
{
  *(uint8_t *)(this + 0x3d) = 1; // +0x3d: some byte flag, set to true
  return;
}