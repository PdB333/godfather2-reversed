// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  if (this != (SomeClass *)0x0) {
    FUN_00598de0();
    this->vtable = &PTR_LAB_00d74620; // Set vtable pointer
    return;
  }
  FUN_00598de0();
  ppuRam00000000 = &PTR_LAB_00d74620; // Global vtable assignment
  return;
}