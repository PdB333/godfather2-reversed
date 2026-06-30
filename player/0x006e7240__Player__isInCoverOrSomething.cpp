// FUNC_NAME: Player::isInCoverOrSomething
byte __fastcall Player::isInCoverOrSomething(int thisPtr)
{
  if ((*(byte *)(thisPtr + 0x8a) & 0x20) == 0) {
    FUN_006e6700(); // likely Player::updateCoverState or similar
  }
  return *(byte *)(thisPtr + 0x89) >> 4 & 1; // +0x89: cover flags, bit 4 = in cover
}