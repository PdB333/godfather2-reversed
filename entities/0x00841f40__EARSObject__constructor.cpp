// FUNC_NAME: EARSObject::constructor
undefined4 * __fastcall EARSObject::constructor(undefined4 *this)
{
  // Call base class constructor 6 times (likely for multiple inheritance or vtable setup)
  FUN_005953b0(); // BaseObject::constructor
  FUN_005953b0(); // BaseObject::constructor
  FUN_005953b0(); // BaseObject::constructor
  FUN_005953b0(); // BaseObject::constructor
  FUN_005953b0(); // BaseObject::constructor
  FUN_005953b0(); // BaseObject::constructor

  // Set vtable pointer
  *this = &PTR_LAB_00d747cc; // EARSObject vtable

  return this;
}