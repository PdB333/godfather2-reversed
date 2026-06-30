// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClassDestructor(undefined4 *this)
{
  *this = &PTR_FUN_00d5c8d4; // vtable pointer for destructor phase 1
  if (DAT_01129bb4 != (undefined4 *)0x0) {
    // Call a virtual function on a global singleton (possibly a manager)
    (**(code **)*DAT_01129bb4)(1);
  }
  *this = &PTR_LAB_00d5c858; // vtable pointer for destructor phase 2
  DAT_011299d0 = 0; // Clear a global flag or pointer
  return;
}