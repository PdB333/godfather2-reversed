// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d5da8c;  // vtable setup
  this[0xf] = &PTR_LAB_00d5da7c; // +0x3C: some member pointer
  this[0x12] = &PTR_LAB_00d5da78; // +0x48: some member pointer
  FUN_004086d0(this + 0x14); // +0x50: sub-object constructor
  FUN_00408310(this + 0x14); // +0x50: sub-object initialization
  FUN_004086d0(&DAT_0120e93c); // global static object constructor
  FUN_0046c640(); // some global initialization
  return;
}