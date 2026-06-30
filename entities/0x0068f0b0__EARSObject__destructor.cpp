// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)
{
  // Set vtable to first vtable pointer
  *this = &PTR_FUN_00d5c8d4;
  
  // If global object manager exists, notify it of destruction
  if (DAT_01129bb4 != (undefined4 *)0x0) {
    (**(code **)*DAT_01129bb4)(1);
  }
  
  // Set vtable to second vtable pointer (base class destructor)
  *this = &PTR_LAB_00d5c858;
  
  // Clear some global flag
  DAT_011299d0 = 0;
  
  // If bit 0 of flags is set, call operator delete
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}