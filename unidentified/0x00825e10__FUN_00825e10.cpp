// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d73470;
  
  // Initialize member pointers at offsets 0x3C (0xF * 4) and 0x48 (0x12 * 4)
  this[0xf] = &PTR_LAB_00d73460;
  this[0x12] = &PTR_LAB_00d7345c;
  
  // Call sub-constructor on member at offset 0x50 (0x14 * 4)
  FUN_004086d0(this + 0x14);
  
  // Initialize sub-object at offset 0x50
  FUN_00408310(this + 0x14);
  
  // If pointer at offset 0x58 (0x16 * 4) is non-null, call function pointer at offset 0x64 (0x19 * 4)
  if (this[0x16] != 0) {
    (*(code *)this[0x19])(this[0x16]);
  }
  
  // Call global initialization function
  FUN_0046c640();
  
  // If flags bit 0 is set, free memory (likely operator delete with size 0x88)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x88);
  }
  
  return this;
}