// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x008ce0f0
  FUN_008ce0f0(param_2);
  
  // Set vtable pointer (virtual function table)
  *this = &PTR_FUN_00d7cb48;
  
  // Initialize additional virtual function table pointers at offsets +0x3C (0xF * 4) and +0x48 (0x12 * 4)
  this[0xf] = &PTR_LAB_00d7cb38;  // +0x3C - secondary vtable
  this[0x12] = &PTR_LAB_00d7cb34; // +0x48 - tertiary vtable
  
  return this;
}