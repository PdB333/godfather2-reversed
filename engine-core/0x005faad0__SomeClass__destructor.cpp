// FUNC_NAME: SomeClass::destructor
int * __thiscall SomeClass::destructor(int *this, byte flags)
{
  // Check if the internal pointer is non-null and free it
  if (*this != 0) {
    FUN_009c8f10(*this); // likely operator delete or free
  }
  // If the low bit of flags is set, also free the this pointer itself
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete on this
  }
  return this;
}