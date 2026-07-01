// FUNC_NAME: EARSObject::destructor
int * __thiscall EARSObject::destructor(int *this, byte flags)
{
  // Check if the object's vtable pointer is non-null (object is valid)
  if (*this != 0) {
    // Call the virtual destructor via the vtable at offset +0x0C (index 3)
    (*(code *)this[3])(*this);
  }
  // If the low bit of flags is set, deallocate the memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete or memory deallocation
  }
  return this;
}