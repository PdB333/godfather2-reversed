// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d5d980;
  
  // Set additional function pointers at offsets +0x3C, +0x48, +0x50
  this[0xf] = &PTR_LAB_00d5d970;   // +0x3C
  this[0x12] = &PTR_LAB_00d5d96c;  // +0x48
  this[0x14] = &PTR_LAB_00d5d968;  // +0x50
  
  // If pointer at +0x140 is non-null, release it
  if (this[0x50] != 0) {           // +0x140
    FUN_004daf90(this + 0x50);     // likely operator delete or release
  }
  
  // Call some initialization function
  FUN_00474090();                  // likely base class constructor or init
  
  // If flags bit 0 is set, call operator delete with size 0x150
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x150);     // likely operator delete(this, 0x150)
  }
  
  return this;
}