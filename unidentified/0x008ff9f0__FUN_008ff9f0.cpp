// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, int *someParam)
{
  // Global pointer to this instance (likely singleton or manager)
  _DAT_0112ff10 = this;
  
  // Set vtable pointer
  *this = &PTR_FUN_00d81700;
  
  // Store the parameter at offset +0x4
  this[1] = someParam;  // +0x04: someParam pointer
  
  // Initialize fields at +0x08, +0x0C, +0x10 to zero
  this[2] = 0;  // +0x08: some counter/pointer
  this[3] = 0;  // +0x0C: some counter/pointer
  this[4] = 0;  // +0x10: some counter/pointer
  
  // Call a virtual function on the parameter object (offset +0x8 in vtable)
  (**(code **)(*someParam + 8))();
  
  return this;
}