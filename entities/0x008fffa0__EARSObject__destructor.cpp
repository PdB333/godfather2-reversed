// FUNC_NAME: EARSObject::destructor
int * __thiscall EARSObject::destructor(int *this, byte flags)
{
  // Check if the object's reference count or pointer is non-zero
  if (*this != 0) {
    // Call the internal cleanup/destruction function (likely frees resources)
    EARSObject::cleanup(this);
  }
  // If the low bit of flags is set, free the memory (operator delete)
  if ((flags & 1) != 0) {
    EARSObject::operatorDelete(this);
  }
  return this;
}