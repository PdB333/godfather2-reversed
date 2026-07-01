// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0077e970
  FUN_0077e970(param_2);
  
  // Initialize member variables
  this[0x21] = 0;  // +0x84: some member
  this[0x22] = 0;  // +0x88: some member
  this[0x23] = 0;  // +0x8C: some member
  
  // Set vtable pointer
  *this = &PTR_FUN_00d695fc;  // vtable for this class
  
  // Set additional function pointers
  this[0xf] = &PTR_LAB_00d695ec;   // +0x3C: function pointer
  this[0x12] = &PTR_LAB_00d695e8;  // +0x48: function pointer
  
  return this;
}