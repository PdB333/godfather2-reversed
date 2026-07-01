// FUNC_NAME: SomeClass::isFlagSet
bool __fastcall SomeClass::isFlagSet(int this)
{
  // Check if bit 0 of byte at this+0x2c is set and the signed byte is negative (bit 7 set)
  // This likely checks two flags: a low bit flag and a high bit flag
  if (((*(byte *)(this + 0x2c) & 1) != 0) && ((char)*(byte *)(this + 0x2c) < '\0')) {
    return true;
  }
  return false;
}