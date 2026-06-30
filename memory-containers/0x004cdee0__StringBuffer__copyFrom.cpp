// FUNC_NAME: StringBuffer::copyFrom
void __fastcall StringBuffer::copyFrom(int *this)
{
  int *srcBuffer;
  uint byteIndex;
  
  srcBuffer = (int *)*this;
  byteIndex = 0;
  if ((short)this[2] != 0) {
    do {
      *(byte *)(byteIndex + this[0]) = *(byte *)(byteIndex + (int)srcBuffer);
      byteIndex = byteIndex + 1;
    } while (byteIndex < (ushort)this[2]);
  }
  return;
}