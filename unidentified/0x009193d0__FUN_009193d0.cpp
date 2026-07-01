// FUNC_NAME: SomeClass::destructor
int * __thiscall SomeClass::destructor(int *this, byte flags)
{
  // Check if the object's data pointer is non-null
  if (*this != 0) {
    // Call the virtual destructor or cleanup function stored at offset +0xC
    (*(code *)this[3])(*this);
  }
  // If the low bit of flags is set, free the memory (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // Likely operator delete or custom deallocation
  }
  return this;
}