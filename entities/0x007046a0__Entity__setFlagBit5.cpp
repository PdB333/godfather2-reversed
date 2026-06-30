// FUNC_NAME: Entity::setFlagBit5
void __thiscall Entity::setFlagBit5(int this, char enable)
{
  if (enable != 0) {
    *(uint *)(this + 0x2d8) = *(uint *)(this + 0x2d8) | 0x20;  // set bit 5 (0x20)
    return;
  }
  *(uint *)(this + 0x2d8) = *(uint *)(this + 0x2d8) & 0xffffffdf;  // clear bit 5
  return;
}