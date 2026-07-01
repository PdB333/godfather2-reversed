// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d72e9c; // vtable pointer
  this[0xf] = &PTR_LAB_00d72e8c; // +0x3C
  this[0x12] = &PTR_LAB_00d72e88; // +0x48
  this[0x14] = &PTR_LAB_00d72e84; // +0x50
  FUN_004086d0(this + 0x1d); // +0x74 - sub-object constructor
  FUN_00408310(this + 0x1d); // +0x74 - sub-object init
  FUN_00408310(this + 0x1f); // +0x7C - another sub-object init
  if (this[0x3a] != 0) { // +0xE8 - check if pointer is non-null
    FUN_004daf90(this + 0x3a); // +0xE8 - release/destruct sub-object
  }
  this[0x14] = &PTR_LAB_00e32854; // +0x50 - override vtable entry
  FUN_0046c640(); // global init call
  return;
}