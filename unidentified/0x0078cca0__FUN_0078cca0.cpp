// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Set vtable pointer (virtual function table)
  *this = &PTR_FUN_00d69b04;
  
  // Initialize member fields at various offsets
  this[0xf] = &PTR_LAB_00d69af4;  // +0x3C - pointer to some data
  this[0x12] = &PTR_LAB_00d69af0; // +0x48 - pointer to some data
  this[0x14] = 0;                 // +0x50 - some integer
  *(undefined2 *)(this + 0x15) = 0; // +0x54 - 2-byte field
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 - 2-byte field
  this[0x19] = 0;                 // +0x64 - some integer
  this[0x18] = 0;                 // +0x60 - some integer
  this[0x17] = 0;                 // +0x5C - some integer
  this[0x16] = 0;                 // +0x58 - some integer
  this[0x1d] = 0;                 // +0x74 - some integer
  this[0x1c] = 0;                 // +0x70 - some integer
  this[0x1b] = 0;                 // +0x6C - some integer
  this[0x1a] = 0;                 // +0x68 - some integer
  
  return this;
}