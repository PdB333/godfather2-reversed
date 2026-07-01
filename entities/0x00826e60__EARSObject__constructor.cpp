// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  *this = &PTR_FUN_00d73510;  // vtable pointer
  this[1] = &PTR_LAB_00d73500; // secondary vtable or interface pointer
  FUN_004639e0(0xa8896ed8);    // EARS::Memory::allocate or reference counting
  this[1] = &PTR_LAB_00e30fe0; // update secondary pointer
  *this = &PTR_LAB_00d734f8;   // final vtable assignment
  _DAT_0112db5c = 0;           // global reference count or debug flag
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);        // operator delete if flag set (placement new cleanup)
  }
  return this;
}