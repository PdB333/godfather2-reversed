// FUNC_NAME: Player::setStealthMode
void __thiscall Player::setStealthMode(int this, char enable)
{
  if (enable != '\0') {
    // Set stealth mode flags: bit 11 (0x800) and bit 12 (0x1000) in +0x118
    *(uint *)(this + 0x118) = *(uint *)(this + 0x118) & 0xffff9fff | 0x1800;
    return;
  }
  // Clear stealth mode flags: bits 11-14 (0x7800 mask)
  *(uint *)(this + 0x118) = *(uint *)(this + 0x118) & 0xffff87ff;
  return;
}