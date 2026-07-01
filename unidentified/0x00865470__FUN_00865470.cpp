// FUNC_NAME: SomeClass::destructor
int * __thiscall SomeClass::destructor(int *this, byte flags)
{
  // +0x0C: pointer to some allocated resource (e.g., a buffer or object)
  if (this[3] != 0) {
    // Free/release resource at offset +0x0C
    FUN_004daf90(this + 3);
  }
  // +0x00: pointer to another allocated resource (e.g., a buffer or object)
  if (*this != 0) {
    // Free/release resource at offset +0x00
    FUN_004daf90(this);
  }
  // If bit 0 of flags is set, also deallocate the this pointer itself (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}