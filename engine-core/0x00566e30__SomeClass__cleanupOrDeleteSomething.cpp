// FUNC_NAME: SomeClass::cleanupOrDeleteSomething

void __fastcall SomeClass::cleanupOrDeleteSomething(int this)
{
  if (*(int *)(this + 0x11c) != 0) {
    FUN_009c8eb0(*(int *)(this + 0x11c));
    *(int *)(this + 0x11c) = 0;
  }
  return;
}