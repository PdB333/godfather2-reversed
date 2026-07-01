// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  // Call base class constructor or some initialization function
  FUN_0046c590(param_2);
  
  // Store global value
  uVar1 = _DAT_00d5780c;
  
  // Set vtable pointer (class hierarchy)
  *this = &PTR_FUN_00d81c20;  // Primary vtable
  
  // Initialize member variables
  this[0xf] = &PTR_LAB_00d81c10;  // +0x3C - Secondary vtable or function pointer
  this[0x12] = &PTR_LAB_00d81c0c; // +0x48 - Another function pointer
  
  // Zero out various fields
  this[0x14] = 0;                  // +0x50 - Some integer
  *(undefined2 *)(this + 0x15) = 0; // +0x54 - 2-byte field
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 - Another 2-byte field
  this[0x16] = 0;                  // +0x58 - Integer
  *(undefined2 *)(this + 0x17) = 0; // +0x5C - 2-byte field
  *(undefined2 *)((int)this + 0x5e) = 0; // +0x5E - Another 2-byte field
  this[0x1a] = 0;                  // +0x68 - Integer
  this[0x1b] = 0;                  // +0x6C - Integer
  
  // Set initial values from global
  this[0x18] = uVar1;              // +0x60 - Some value from global
  this[0x19] = 1;                  // +0x64 - Initialize to 1
  
  return this;
}