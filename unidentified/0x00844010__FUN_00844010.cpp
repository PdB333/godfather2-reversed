// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  // Set vtable pointer to first vtable (likely base class)
  *this = &PTR_LAB_00d74620;
  
  // Call base class constructor
  FUN_00598e10();
  
  // Set vtable pointer to second vtable (derived class override)
  this[1] = &PTR_LAB_00d74a38;
  
  // Override first vtable pointer with function pointer table
  *this = &PTR_FUN_00d74a34;
  
  // Initialize field at offset +0x18 (6 * 4 bytes) to 0
  this[6] = 0;
  
  return this;
}