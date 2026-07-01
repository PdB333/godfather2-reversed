// FUNC_NAME: SomeEARSObject::constructor (or similar initialization function)
undefined4 * __fastcall SomeEARSObject::constructor(undefined4 *this)
{
  // Initialize first field to 0 (likely vtable or some status/flag)
  *this = 0;
  
  // Call a sub-function (probably base class constructor or some setup)
  FUN_004d3b00(0);
  
  // Initialize fields at offsets +0x14, +0x18, +0x1C to 0
  this[5] = 0;  // +0x14
  this[6] = 0;  // +0x18
  this[7] = 0;  // +0x1C
  
  // Set byte at +0x20 to 0
  *(undefined1 *)(this + 8) = 0;  // +0x20, note: pointer arithmetic adds 8*4=32 bytes, but casting to undefined1* means only 1 byte
  
  // Set byte at +0x21 to 0
  *(undefined1 *)((int)this + 0x21) = 0;  // +0x21
  
  // Initialize field at +0x24 to -1 (0xFFFFFFFF) - likely an invalid handle/index
  this[9] = 0xffffffff;  // +0x24
  
  return this;
}