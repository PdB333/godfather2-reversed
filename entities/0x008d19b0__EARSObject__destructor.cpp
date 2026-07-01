// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)

{
  *this = &PTR_EARSObject_vtable; // vtable pointer
  this[3] = &PTR_LAB_00d7d04c; // set some internal pointer
  if (this[10] != 0) {
    // call a virtual method on the object at this[0xd] (likely a cleanup function)
    (*(code *)this[0xd])(this[10]);
  }
  this[3] = &PTR_LAB_00d7d048; // reset pointer
  _DAT_0112f9b4 = 0; // clear some global flag
  FUN_004083d0(); // likely memory deallocation or manager notification
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete if flags indicate to free memory
  }
  return this;
}