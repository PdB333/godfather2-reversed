// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d74490;
  // Set additional function pointers at offsets +0x3C (0xF * 4) and +0x48 (0x12 * 4)
  this[0xf] = &PTR_LAB_00d74480;  // +0x3C
  this[0x12] = &PTR_LAB_00d7447c; // +0x48
  
  // If pointer at +0x58 (0x16 * 4) is non-null, free it
  if (this[0x16] != 0) {
    FUN_009c8c00(this[0x16]);  // likely operator delete or free
    this[0x16] = 0;
  }
  
  // Zero out fields at +0x50 and +0x54
  this[0x14] = 0;  // +0x50
  this[0x15] = 0;  // +0x54
  
  // Call base class or static initialization
  FUN_0083fbc0();
  
  // If flags bit 0 is set, call operator delete with size 0x5C
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x5c);  // likely operator delete(this, 0x5C)
  }
  
  return this;
}