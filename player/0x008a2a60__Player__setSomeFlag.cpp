// FUNC_NAME: Player::setSomeFlag
void __thiscall Player::setSomeFlag(int this, char enable)
{
  if (enable != '\0') {
    *(uint *)(this + 0x37c) = *(uint *)(this + 0x37c) | 0x10;
    return;
  }
  *(uint *)(this + 0x37c) = *(uint *)(this + 0x37c) & 0xffffffef;
  return;
}