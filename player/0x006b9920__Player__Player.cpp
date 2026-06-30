// FUNC_NAME: Player::Player
undefined4 * __thiscall Player::Player(undefined4 *this, undefined4 initData)
{
  Sentient::Sentient(initData);  // base constructor at 0x006bd1d0
  // vtable setup
  *this = &PTR_FUN_00d5e668;                // +0x00: vtable pointer
  this[0xf] = &PTR_LAB_00d5e658;            // +0x3C: interface vtable 1
  this[0x12] = &PTR_LAB_00d5e654;           // +0x48: interface vtable 2

  // Initialize member fields
  this[0x20] = 0;                            // +0x80: unknown field
  this[0x22] = 0;                            // +0x88
  this[0x23] = 0;                            // +0x8C
  this[0x24] = 0;                            // +0x90
  this[0x25] = 0;                            // +0x94
  this[0x21] = 100;                          // +0x84: initial value 100 (e.g., health or max resource)
  this[0x26] = 0;                            // +0x98
  *(undefined2 *)(this + 0x27) = 0;          // +0x9C: 16-bit field
  *(undefined2 *)((int)this + 0x9e) = 0;     // +0x9E: 16-bit field
  this[0x2b] = 0;                            // +0xAC
  this[0x2a] = 0;                            // +0xA8
  this[0x29] = 0;                            // +0xA4
  this[0x28] = 0;                            // +0xA0
  this[0x2f] = 0;                            // +0xBC
  this[0x2e] = 0;                            // +0xB8
  this[0x2d] = 0;                            // +0xB4
  this[0x2c] = 0;                            // +0xB0

  return this;
}