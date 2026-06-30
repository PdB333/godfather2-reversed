// FUNC_NAME: UnknownClass::`scalar deleting destructor'

void * __thiscall UnknownClass::scalarDeletingDestructor(UnknownClass *this, byte flags)
{
  // Call the actual destructor (at 0x00726b40)
  this->~UnknownClass();

  // If the low bit is set, free the memory using sized delete (size = 0x140 = 320 bytes)
  if ((flags & 1) != 0) {
    operator delete(this, 0x140);
  }

  return this;
}