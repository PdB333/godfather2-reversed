// FUNC_NAME: BitStream::writeBits
int __thiscall BitStream::writeBits(int *this, byte *data)
{
  int result;
  int iVar1;
  
  if ((this[1] < 2) && (iVar1 = FUN_00667740(), iVar1 != 0)) {
    return iVar1;
  }
  this[2] = 0; // +0x08: bitPosition
  this[0] = 0; // +0x00: bytePosition
  _memset((void *)this[3], 0, this[1] * 4); // +0x0C: buffer, +0x04: bufferSize
  if (0 < in_EAX) {
    do {
      in_EAX = in_EAX + -1;
      iVar1 = FUN_00668e40(8);
      if (iVar1 != 0) {
        return iVar1;
      }
      *(uint *)this[3] = *(uint *)this[3] | (uint)*data;
      this[0] = this[0] + 1;
      data = data + 1;
    } while (0 < in_EAX);
  }
  FUN_00665b10();
  return 0;
}