// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)

{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d72560;
  
  // Initialize member pointers
  this[0xf] = &PTR_LAB_00d72550;  // +0x3C
  this[0x12] = &PTR_LAB_00d7254c; // +0x48
  
  // Initialize member variables
  this[0x14] = 0;                 // +0x50
  *(undefined2 *)(this + 0x15) = 0; // +0x54 (2 bytes)
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 (2 bytes)
  
  // Set magic/sentinel values for debugging
  this[0x16] = 0xbadbadba;        // +0x58 - uninitialized memory marker
  this[0x17] = 0xbeefbeef;        // +0x5C - uninitialized memory marker
  this[0x18] = 0xeac15a55;        // +0x60 - uninitialized memory marker
  this[0x19] = 0x91100911;        // +0x64 - uninitialized memory marker
  
  // Set a boolean flag to true
  *(undefined1 *)(this + 0x1a) = 1; // +0x68 (1 byte)
  
  return this;
}