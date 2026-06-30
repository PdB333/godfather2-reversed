// FUNC_NAME: EARSObject::EARSObject or BaseClass::constructor
void __fastcall EARSObject_constructor(undefined4 *this)
{
  *this = &PTR_FUN_00e3edf0;  // Set vtable pointer (+0x00)
  FUN_005d48a0();             // Call base class constructor (likely EARSNode or similar)
  return;
}