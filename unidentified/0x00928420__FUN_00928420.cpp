// FUNC_NAME: SomeClass::addRef
void __fastcall SomeClass::addRef(int this)
{
  if (*(int *)(this + 0x54) == 0) {
    FUN_005c1ad0(); // likely initializes some resource or performs first-time setup
    *(uint *)(this + 0x50) = *(uint *)(this + 0x50) | 2; // set flag bit 1 in +0x50
  }
  *(int *)(this + 0x54) = *(int *)(this + 0x54) + 1; // increment reference count at +0x54
}