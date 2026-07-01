// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
  // Call base class constructor
  FUN_0064cc90();
  
  // Set vtable pointer
  *this = &PTR_LAB_00d79c18;
  
  // Copy name string (max 63 characters + null terminator)
  _strncpy((char *)(this + 8), name, 0x3f);
  
  // Store parameters
  this[1] = param3;  // +0x04
  this[3] = param4;  // +0x0C
  this[2] = param5;  // +0x08
  
  // Initialize fields to zero
  this[4] = 0;  // +0x10
  this[5] = 0;  // +0x14
  this[6] = 0;  // +0x18
  this[7] = 0;  // +0x1C
  
  // Store previous head of linked list, then set this as new head
  this[0x1c] = DAT_012059ec;  // +0x70 - previous node in linked list
  DAT_012059ec = this;  // Update global head pointer
  
  return this;
}