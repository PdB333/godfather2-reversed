// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __thiscall PlayerActionableInfo::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x00473f10
  FUN_00473f10(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d5d980;
  
  // Initialize member pointers (likely function pointers or interface pointers)
  this[0xf] = &PTR_LAB_00d5d970;  // +0x3C
  this[0x12] = &PTR_LAB_00d5d96c; // +0x48
  this[0x14] = &PTR_LAB_00d5d968; // +0x50
  
  // Zero out state variables
  this[0x50] = 0; // +0x140
  this[0x51] = 0; // +0x144
  this[0x52] = 0; // +0x148
  this[0x52] = 0; // +0x148 (duplicate, likely intentional or compiler artifact)
  
  return this;
}