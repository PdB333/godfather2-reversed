// FUNC_NAME: SomeClass::setFlagAndTime
void __thiscall SomeClass::setFlagAndTime(int this, byte flagIndex)
{
  // Set a bit flag at offset +0x20 using the flag index (masked to 5 bits)
  *(byte *)(this + 0x20) = *(byte *)(this + 0x20) | (byte)(1 << (flagIndex & 0x1f));
  
  // Set a time value at offset +0x1c from a global base time + offset
  *(float *)(this + 0x1c) = DAT_01205228 + _DAT_00d69a6c;
}