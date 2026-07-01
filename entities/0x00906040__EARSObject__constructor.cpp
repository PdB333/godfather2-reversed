// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Initialize vtable pointer (offset +0x50)
  this[0x14] = &PTR_LAB_00e32854;
  
  // Initialize some member to 0 (offset +0x54)
  this[0x15] = 0;
  
  // Set vtable pointer (offset +0x00)
  *this = &PTR_FUN_00d826c8;
  
  // Set additional vtable-like pointers
  // +0x3C
  this[0xf] = &PTR_LAB_00d826b8;
  // +0x48
  this[0x12] = &PTR_LAB_00d826b4;
  // +0x50 (overwrites previous)
  this[0x14] = &PTR_LAB_00d826b0;
  
  // Initialize flags/counters to 0
  // +0x58
  this[0x16] = 0;
  
  // Initialize short values to 0
  // +0x5C
  *(undefined2 *)(this + 0x17) = 0;
  // +0x5E
  *(undefined2 *)((int)this + 0x5e) = 0;
  
  return this;
}