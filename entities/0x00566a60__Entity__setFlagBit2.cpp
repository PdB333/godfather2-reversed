// FUNC_NAME: Entity::setFlagBit2
void __thiscall Entity::setFlagBit2(int this, char enable)
{
  if (enable != '\0') {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x2c) | 4;  // +0x2c: flags field, set bit 2
    return;
  }
  *(uint *)(this + 0x2c) = *(uint *)(this + 0x2c) & 0xfffffffb;  // clear bit 2
  return;
}