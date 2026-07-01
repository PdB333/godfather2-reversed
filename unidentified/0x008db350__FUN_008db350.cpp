// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall FUN_008db350(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
  // Call base class constructor or initializer
  FUN_0064cc90();
  
  // Set vtable pointer
  *this = &PTR_LAB_00d7e0a8;
  
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
  
  // Store this pointer in a global linked list (offset 0x70 from this)
  this[0x1c] = DAT_012059ec;  // +0x70 - previous head
  DAT_012059ec = this;         // Update global head to this
  
  return this;
}