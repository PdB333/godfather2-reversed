// FUNC_NAME: SomeClass::resetSomeState
void __fastcall SomeClass::resetSomeState(int this)
{
  *(undefined4 *)(this + 0x74) = 0; // +0x74: some integer field, likely a counter or flag
  *(undefined4 *)(this + 0x78) = 0; // +0x78: another integer field, likely related
  return;
}