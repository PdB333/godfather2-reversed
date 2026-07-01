// FUNC_NAME: Player::setVisibility
void __thiscall Player::setVisibility(int this, char visible)
{
  if (visible == '\0') {
    // Hide: check and clear visibility flags
    if ((*(uint *)(this + 0x2c6c) >> 2 & 1) != 0) {
      FUN_0083c9b0(this + 0x10);  // remove from render list
      *(uint *)(this + 0x2c6c) = *(uint *)(this + 0x2c6c) & 0xfffffffb;  // clear bit 2
    }
    if ((*(uint *)(this + 0x2c6c) >> 3 & 1) != 0) {
      FUN_0083c9b0(this + 0x10);  // remove from render list
      *(uint *)(this + 0x2c6c) = *(uint *)(this + 0x2c6c) & 0xfffffff7;  // clear bit 3
    }
  }
  else {
    // Show: check and set visibility flags
    if ((*(uint *)(this + 0x2c6c) >> 2 & 1) == 0) {
      FUN_0083c930(this + 0x10, 100);  // add to render list with priority 100
      *(uint *)(this + 0x2c6c) = *(uint *)(this + 0x2c6c) | 4;  // set bit 2
    }
    if ((*(uint *)(this + 0x2c6c) >> 3 & 1) == 0) {
      FUN_0083c930(this + 0x10, 100);  // add to render list with priority 100
      *(uint *)(this + 0x2c6c) = *(uint *)(this + 0x2c6c) | 8;  // set bit 3
      return;
    }
  }
  return;
}