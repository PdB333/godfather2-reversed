// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)
{
  int *refCountPtr;
  int *refCountBase;
  int newRefCount;
  
  *this = &PTR_FUN_00d8b42c;  // Set vtable to base class destructor vtable
  FUN_004df600();              // Likely release/cleanup resources
  refCountBase = (int *)this[3];  // +0x0C: reference count pointer
  refCountPtr = refCountBase + 1; // +0x04: actual ref count value
  *refCountPtr = *refCountPtr + -1;  // Decrement reference count
  if (*refCountPtr == 0) {
    (**(code **)(*refCountBase + 4))();  // Call destructor on ref counted object
  }
  newRefCount = this[2];  // +0x08: another pointer/ref count
  if (newRefCount != 0) {
    *(undefined4 *)(newRefCount + 8) = 0;  // Clear reference
    this[2] = 0;
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // operator delete if flags indicate delete
  }
  return this;
}