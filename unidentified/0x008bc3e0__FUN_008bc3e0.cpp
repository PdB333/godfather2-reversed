// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d7bc30; // vtable pointer
  this[0xf] = &PTR_LAB_00d7bc20; // +0x3C - some function pointer
  this[0x12] = &PTR_LAB_00d7bc1c; // +0x48 - some function pointer
  FUN_004086d0(this + 0x15); // +0x54 - sub-object constructor
  FUN_00408310(this + 0x15); // +0x54 - sub-object initialization
  FUN_0046c640(); // global initialization call
}