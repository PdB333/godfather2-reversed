// FUNC_NAME: Player::setIsInCombat
void __thiscall Player::setIsInCombat(int thisPtr, char isInCombat)
{
  if (isInCombat != '\0') {
    // Set bit 1 (0x2) in flags at +0x970
    *(uint *)(thisPtr + 0x970) = *(uint *)(thisPtr + 0x970) | 2;
    return;
  }
  // Clear bit 1 (0x2) in flags at +0x970
  *(uint *)(thisPtr + 0x970) = *(uint *)(thisPtr + 0x970) & 0xfffffffd;
  return;
}