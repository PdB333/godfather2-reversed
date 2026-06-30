// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d58b70;
  
  // Initialize various member pointers at known offsets
  this[0xf] = &PTR_LAB_00d58b60;   // +0x3C - some function table
  this[0x12] = &PTR_LAB_00d58b5c;  // +0x48 - another function table
  this[0x14] = &PTR_LAB_00d58b58;  // +0x50 - function pointer
  this[0x15] = &PTR_LAB_00d58af8;  // +0x54 - function pointer
  this[0x16] = &PTR_LAB_00d58a90;  // +0x58 - function pointer
  
  // Call base class constructor or initialization
  FUN_0046ea20();
  
  // If flag bit 0 is set, allocate memory (0x180 bytes)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x180);
  }
  
  return this;
}