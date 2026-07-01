// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d80b7c; // vtable setup
  this[0xf] = &PTR_LAB_00d80b6c; // +0x3C: some member pointer
  this[0x12] = &PTR_LAB_00d80b68; // +0x48: some member pointer
  FUN_004086d0(this + 0x18); // initialize sub-object at +0x60
  FUN_00408310(this + 0x18); // initialize sub-object at +0x60
  FUN_004086d0(this + 0x1a); // initialize sub-object at +0x68
  FUN_00408310(this + 0x1a); // initialize sub-object at +0x68
  FUN_0046c640(); // some global initialization call
  return;
}