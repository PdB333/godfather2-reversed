// FUNC_NAME: SomeNetworkObject::constructor
// This function is the constructor for a class derived from a base class (FUN_008d3ec0).
// It sets up two vtable pointers (likely for multiple inheritance or interface implementation)
// and initializes member fields at offsets 0x48 and 0x1C.
undefined4 * __thiscall SomeNetworkObject::constructor(undefined4 *this, undefined4 param_A, undefined4 param_B)
{
  // Call base class constructor (likely at 0x008d3ec0)
  FUN_008d3ec0();
  
  // Set the primary vtable pointer (first word of object)
  *this = &PTR_FUN_00d7d60c;
  
  // Set a secondary vtable pointer at offset 0x4C (param_1[0x13])
  this[0x13] = &PTR_LAB_00d7d5fc;
  
  // Store parameter at offset 0x48 (param_1[0x12])
  this[0x12] = param_A;
  
  // Store parameter at offset 0x1C (param_1[7])
  this[7] = param_B;
  
  return this;
}