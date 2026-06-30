// FUNC_NAME: Player::Player
undefined4 * __thiscall Player_Constructor(undefined4 *this, byte param_2)

{
  // Set vtable pointers: base vtable at +0x00, additional vtable at +0x3C and +0x48
  *this = &PTR_FUN_00d5888c;
  this[0xf] = &PTR_LAB_00d5887c;   // +0x3C (15 * 4)
  this[0x12] = &PTR_LAB_00d58878;  // +0x48 (18 * 4)

  // Call base class constructor (Sentient? or Entity?)
  FUN_0046c640();

  // If the allocation flag (param_2) has bit 0 set, free the memory (constructor failure or placed new)
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this, 0x50); // operator delete with size 0x50 (80 bytes)
  }

  return this;
}