// FUNC_NAME: SomeClass::initializeSomething
void __fastcall SomeClass::initializeSomething(int this)
{
  if (*(char *)(this + 0x180) == '\0') {
    // Call a sub-function to perform initialization
    FUN_008dc4b0();
    // Call a virtual function at offset 0x28 from the vtable at +0x58
    (**(code **)(*(int *)(this + 0x58) + 0x28))(0x20);
    // Mark as initialized
    *(undefined1 *)(this + 0x180) = 1;
  }
  return;
}