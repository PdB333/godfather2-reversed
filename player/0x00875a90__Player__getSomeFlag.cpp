// FUNC_NAME: Player::getSomeFlag
uint __fastcall Player::getSomeFlag(int thisPtr)
{
  // Reads a 32-bit value at offset 0xA18 from the Player object,
  // shifts right by 7 bits, then masks with 0xFFFFFF01.
  // This extracts a specific flag/bitfield from the Player's state.
  return *(uint *)(thisPtr + 0xa18) >> 7 & 0xffffff01;
}