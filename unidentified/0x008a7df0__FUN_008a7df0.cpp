// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
  // Call base class constructor
  FUN_0064cc90();
  
  // Set vtable pointer
  *this = &PTR_LAB_00d79c08;
  
  // Copy name string (max 63 chars) into offset +0x20 (this+8)
  _strncpy((char *)(this + 8), name, 0x3f);
  
  // Store parameters at various offsets
  this[1] = param3;  // +0x04
  this[3] = param4;  // +0x0C
  this[2] = param5;  // +0x08
  
  // Initialize fields to zero
  this[4] = 0;  // +0x10
  this[5] = 0;  // +0x14
  this[6] = 0;  // +0x18
  this[7] = 0;  // +0x1C
  
  // Store previous head of linked list at +0x70 (this+0x1C)
  this[0x1c] = DAT_012059ec;  // +0x70
  
  // Update global linked list head to this object
  DAT_012059ec = this;
  
  return this;
}