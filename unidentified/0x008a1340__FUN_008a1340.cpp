// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d78bc4;
  
  // Initialize member fields
  this[0xf] = &PTR_LAB_00d78bb4;  // +0x3C
  this[0x12] = &PTR_LAB_00d78bb0; // +0x48
  this[0x14] = 0;                 // +0x50
  *(undefined2 *)(this + 0x15) = 0; // +0x54 (2 bytes)
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 (2 bytes)
  
  return this;
}