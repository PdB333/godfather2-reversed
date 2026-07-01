// FUNC_NAME: SomeClass::resetSomething
void __fastcall SomeClass::resetSomething(int this)
{
  *(undefined4 *)(this + 0x78) = 0;  // +0x78: some field, likely a pointer or handle
  FUN_007ac530(0);                    // call to another function with parameter 0
  return;
}