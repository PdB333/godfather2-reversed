// FUNC_NAME: Player::Player
undefined4 * __thiscall Player::Player(undefined4 *this, byte param_2)
{
  *this = &PTR_FUN_00d82630; // vtable pointer
  this[0x82] = &PTR_LAB_00d8262c; // +0x208: some member pointer
  FUN_00905600(); // likely base class constructor (Sentient or similar)
  FUN_00412230(); // likely another base class or member initialization
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this); // placement delete if allocation failed
  }
  return this;
}