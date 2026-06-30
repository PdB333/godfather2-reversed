// FUNC_NAME: Entity::setEnabled
void __thiscall Entity::setEnabled(int this, char enabled)
{
  if (enabled != '\0') {
    *(uint *)(this + 0x14) = *(uint *)(this + 0x14) | 4;  // +0x14: flags, set bit 2 (enabled flag)
    return;
  }
  *(uint *)(this + 0x14) = *(uint *)(this + 0x14) & 0xfffffffb;  // +0x14: flags, clear bit 2
  return;
}