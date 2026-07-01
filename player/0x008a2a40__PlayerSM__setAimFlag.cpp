// FUNC_NAME: PlayerSM::setAimFlag
void __thiscall setAimFlag(int this, char isAiming)
{
  // Offset 0x37c is a bitfield for player state flags
  if (isAiming != '\0') {
    // Set bit 2 (0x4) to indicate aiming
    *(uint *)(this + 0x37c) = *(uint *)(this + 0x37c) | 4;
    return;
  }
  // Clear bit 2 (0x4) when not aiming
  *(uint *)(this + 0x37c) = *(uint *)(this + 0x37c) & 0xfffffffb;
  return;
}