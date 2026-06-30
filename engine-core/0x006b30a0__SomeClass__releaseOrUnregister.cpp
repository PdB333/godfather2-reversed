// FUNC_NAME: SomeClass::releaseOrUnregister
void __fastcall SomeClass::releaseOrUnregister(int this)
{
  if (*(int *)(this + 0x174) != 0) {
    FUN_008c7d50(*(int *)(this + 0x174), this);
  }
  return;
}