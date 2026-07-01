// FUNC_NAME: EARSObject::copyFrom
undefined4 * __thiscall EARSObject::copyFrom(undefined4 *this, undefined4 *other)
{
  // Copy the first 3 dwords (likely position/rotation data)
  this[0] = other[0];
  this[1] = other[1];
  this[2] = other[2];
  
  // Clear some state flags at offsets +0x10 and +0x14
  this[4] = 0;  // +0x10
  this[5] = 0;  // +0x14
  this[6] = 0;  // +0x18
  
  // Call cleanup/release function on the source's state data at +0x10
  FUN_00792320(other + 4);  // other + 0x10
  
  // Copy a single byte at offset +0x0C (likely a flag or enum)
  *(undefined1 *)(this + 3) = *(undefined1 *)(other + 3);  // +0x0C
  
  return this;
}