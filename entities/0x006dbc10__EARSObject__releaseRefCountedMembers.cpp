// FUNC_NAME: EARSObject::releaseRefCountedMembers
void __fastcall EARSObject::releaseRefCountedMembers(int *this)
{
  // Release the second ref-counted member (offset +0x08)
  if (this[2] != 0) {
    FUN_004daf90(this + 2); // likely releaseRef() or decRef()
  }
  // Release the first ref-counted member (offset +0x00)
  if (*this != 0) {
    FUN_004daf90(this); // likely releaseRef() or decRef()
  }
}