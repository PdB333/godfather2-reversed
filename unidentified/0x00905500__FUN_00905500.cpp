// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  // Call base class constructor
  FUN_004c26c0();
  
  // Initialize member variables
  this[0x82] = 0;  // +0x208 - some flag/counter
  this[0x83] = 0;  // +0x20C - some flag/counter
  this[0x84] = 0;  // +0x210 - some flag/counter
  this[0x87] = 0;  // +0x21C - some flag/counter
  
  // Set vtable pointer
  this[0x85] = &PTR_FUN_00e2f19c;  // +0x214 - vtable or function pointer
  this[0x86] = 1;                  // +0x218 - some flag (enabled/true)
  
  // Set base class vtable
  *this = &PTR_FUN_00d825c0;       // +0x000 - base vtable
  
  // Override vtable entry
  this[0x85] = &PTR_LAB_00d825b0;  // +0x214 - override vtable/function pointer
  
  return this;
}