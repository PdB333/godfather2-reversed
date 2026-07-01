// FUNC_NAME: Player::isInStealthMode
undefined4 __fastcall Player::isInStealthMode(int this)
{
  if ((DAT_00e44720 < (float)(*(uint *)(this + 0x7c) & DAT_00e44680)) &&
     ((*(uint *)(*(int *)(this + 0x58) + 0x8e0) >> 1 & 1) == 0)) {
    return 1;
  }
  return 0;
}