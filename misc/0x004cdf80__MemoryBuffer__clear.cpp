// FUNC_NAME: MemoryBuffer::clear
void __fastcall MemoryBuffer::clear(int *this)
{
  uint i;
  
  i = 0;
  if ((short)this[2] != 0) {
    do {
      *(byte *)(i + *this) = 0;
      i = i + 1;
    } while (i < *(ushort *)(this + 2));
  }
  return;
}