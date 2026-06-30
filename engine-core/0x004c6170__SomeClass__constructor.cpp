// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00e363a0;
  // Initialize member at offset +0x3C (0xF * 4)
  this[0xf] = &PTR_LAB_00e363bc;
  // Initialize member at offset +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00e363cc;
  
  // Call base class constructor or initialization function
  FUN_0046c640();
  
  // If bit 0 of flags is set, call a function from a global table
  // This appears to be a placement new or allocation pattern
  if ((flags & 1) != 0) {
    // Call through global function table at DAT_01223410 + 0x2d4
    // The function at offset +4 is likely operator delete or a cleanup function
    (**(code **)(**(int **)(DAT_01223410 + 0x2d4) + 4))(this, 0);
  }
  
  return this;
}