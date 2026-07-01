// FUNC_NAME: Player::constructor

undefined4 * __thiscall Player::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (likely Sentient or Entity)
  FUN_0046c590(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d778f4;
  
  // Initialize member pointers
  this[0xf] = &PTR_LAB_00d778e4;  // +0x3C - likely a function pointer or interface
  this[0x12] = &PTR_LAB_00d778e0; // +0x48 - another function pointer
  
  // Zero out various fields
  *(undefined2 *)(this + 0x16) = 0;  // +0x58 - 2-byte field
  *(undefined2 *)((int)this + 0x5a) = 0; // +0x5A - 2-byte field
  *(undefined2 *)(this + 0x18) = 0;  // +0x60 - 2-byte field
  *(undefined2 *)((int)this + 0x62) = 0; // +0x62 - 2-byte field
  this[0x15] = 0;  // +0x54 - 4-byte pointer
  this[0x17] = 0;  // +0x5C - 4-byte pointer
  
  return this;
}