// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)

{
  *this = &PTR_FUN_00d6f480;
  this[0xf] = &PTR_LAB_00d6f470;
  this[0x12] = &PTR_LAB_00d6f46c;
  this[0x14] = &PTR_LAB_00d6f468;
  FUN_004086d0(this + 0x2b); // Initialize sub-object at offset +0xAC
  FUN_00408310(this + 0x2b); // Another sub-object init
  FUN_00408310(this + 0x2d); // Initialize sub-object at offset +0xB4
  this[0x14] = &PTR_LAB_00e32854; // Override vtable entry at +0x50
  FUN_0046c640(); // Global initialization call
  return;
}