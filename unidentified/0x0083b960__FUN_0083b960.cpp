// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  if (this[6] != 0) {
    // Release or delete resource at offset +0x18 (this[6])
    FUN_004daf90(this + 6);
  }
  if (this[4] != 0) {
    // Release or delete resource at offset +0x10 (this[4])
    FUN_004daf90(this + 4);
  }
  // Set vtable pointer to base class destructor vtable
  *this = &PTR_LAB_00e2f0c0;
  return;
}