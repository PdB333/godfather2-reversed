// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte param_2)
{
  // VTable setup (likely for base class)
  *this = &PTR_FUN_00d73594;
  
  // Check if some dynamically allocated member at offset +0x1C (param_1[7]) is non-null
  if (this[7] != 0) {
    // Free or cleanup that member
    FUN_004daf90(this + 7);
  }
  
  // Call some kind of manager or global cleanup function
  FUN_00823760();
  
  // If the object was allocated on the heap (param_2 & 1 set), free it
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  
  return this;
}