// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x0046c590
  FUN_0046c590(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d725b0;
  
  // Initialize member pointers
  this[0xf] = &PTR_LAB_00d725a0;  // +0x3C
  this[0x12] = &PTR_LAB_00d7259c; // +0x48
  
  // Initialize magic/sentinel values (likely debug markers or state flags)
  this[0x15] = 0xbadbadba;  // +0x54 - sentinel value
  this[0x16] = 0xbeefbeef;  // +0x58 - sentinel value
  this[0x17] = 0xeac15a55;  // +0x5C - sentinel value
  this[0x18] = 0x91100911;  // +0x60 - sentinel value
  
  // Initialize counters/flags to zero
  this[0x19] = 0;           // +0x64
  *(undefined2 *)(this + 0x1a) = 0;  // +0x68 (2 bytes)
  *(undefined2 *)((int)this + 0x6a) = 0;  // +0x6A (2 bytes)
  this[0x1b] = 0;           // +0x6C
  *(undefined2 *)(this + 0x1c) = 0;  // +0x70 (2 bytes)
  *(undefined2 *)((int)this + 0x72) = 0;  // +0x72 (2 bytes)
  this[0x1d] = 0;           // +0x74
  *(undefined2 *)(this + 0x1e) = 0;  // +0x78 (2 bytes)
  *(undefined2 *)((int)this + 0x7a) = 0;  // +0x7A (2 bytes)
  
  // Re-zero sentinel values (redundant initialization)
  this[0x14] = 0;           // +0x50
  this[0x18] = 0;           // +0x60
  this[0x17] = 0;           // +0x5C
  this[0x16] = 0;           // +0x58
  this[0x15] = 0;           // +0x54
  
  return this;
}