// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d7388c; // vtable pointer assignment
  FUN_0082ba50(); // base class constructor call
  this[0xc] = &PTR_LAB_00e32854; // +0x30: another vtable or interface pointer
  FUN_00821f60(); // member initialization
  return;
}