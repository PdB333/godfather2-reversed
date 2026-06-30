// FUNC_NAME: SomeClass::resetFlag
void __fastcall SomeClass::resetFlag(int this)
{
  *(undefined1 *)(this + 0x20) = 0;
  return;
}