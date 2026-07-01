// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::~SomeClass(undefined4 *this)
{
  *this = &PTR_FUN_00d737b4; // vtable setup for base class
  FUN_0082a730(); // likely base class destructor
  this[0xc] = &PTR_FUN_00d7343c; // vtable override for this class
  if (this[0x23] != 0) { // +0x8C - check if some resource exists
    FUN_004daf90(this + 0x23); // release resource at +0x8C
  }
  this[0xc] = &PTR_LAB_00e32854; // restore base vtable
  FUN_00821f60(); // final cleanup
  return;
}