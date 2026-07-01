// FUNC_NAME: SomeClass::readBitFieldValue
ushort __thiscall SomeClass::readBitFieldValue(int this, int bitFieldDesc)
{
  ushort result;
  
  result = 0;
  switch(*(undefined4 *)(bitFieldDesc + 0xc4)) {
  case 0:
    return *(byte *)(this + 0x100) >> 3 & 0xff01;
  case 1:
    return *(byte *)(this + 0x100) >> 4 & 0xff01;
  case 2:
    return *(byte *)(this + 0x100) >> 5 & 0xff01;
  case 3:
    return *(byte *)(this + 0x100) >> 6 & 0xff01;
  case 4:
    return (ushort)(*(byte *)(this + 0x100) >> 7);
  case 5:
    return *(byte *)(this + 0x101) & 0xff01;
  case 6:
    return *(ushort *)(this + 0x100) >> 9 & 0xff01;
  case 7:
    return *(ushort *)(this + 0x100) >> 10 & 0xff01;
  case 8:
    return *(ushort *)(this + 0x100) >> 0xb & 0xff01;
  case 9:
    result = *(ushort *)(this + 0x100) >> 0xc & 0xff01;
  }
  return result;
}