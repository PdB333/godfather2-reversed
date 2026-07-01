// FUNC_NAME: Entity::setFlagSomeVisibility
void __thiscall Entity::setFlagSomeVisibility(int this, char enable)
{
  if (enable != '\0') {
    // Set bit 0x400 (bit 10) in flags at +0x4C
    *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) | 0x400;
    return;
  }
  // Clear bit 0x400 (bit 10) in flags at +0x4C
  *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) & 0xfffffbff;
  return;
}