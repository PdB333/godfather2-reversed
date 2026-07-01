// FUNC_NAME: SomeClass::destructor
int * __thiscall SomeClass::destructor(int *this, byte flags)
{
  // Check if the object's data pointer is non-null and free it if so
  if (*this != 0) {
    FUN_004daf90(this);  // Likely operator delete or free
  }
  // If the low bit of flags is set, also free the object itself
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // Likely operator delete or free for the object
  }
  return this;
}