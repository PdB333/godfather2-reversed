// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  // Set vtable to initial vtable (PTR_FUN_00d588bc)
  *this = &PTR_FUN_00d588bc;
  // Initialize field at +0x3C (index 0xf) to PTR_LAB_00d588ac
  this[0xf] = &PTR_LAB_00d588ac;
  // Initialize field at +0x48 (index 0x12) to PTR_LAB_00d588a8
  this[0x12] = &PTR_LAB_00d588a8;
  
  // Call base class constructor (likely EARS::Framework::Object)
  FUN_0078ecf0();
  
  // Update vtable to final vtable (PTR_FUN_00d5888c)
  *this = &PTR_FUN_00d5888c;
  // Update field at +0x3C to PTR_LAB_00d5887c
  this[0xf] = &PTR_LAB_00d5887c;
  // Update field at +0x48 to PTR_LAB_00d58878
  this[0x12] = &PTR_LAB_00d58878;
  
  // Call another initialization function
  FUN_0046c640();
  
  // If flag bit 0 is set, call operator delete with size 0x94 (148 bytes)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x94);
  }
  
  return this;
}