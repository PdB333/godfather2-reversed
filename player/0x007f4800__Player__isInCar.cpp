// FUNC_NAME: Player::isInCar
uint __fastcall Player::isInCar(int thisPtr)
{
  // +0x1b94: bitfield of player state flags; bit 0 = in car
  return *(uint *)(thisPtr + 0x1b94) & 1;
}