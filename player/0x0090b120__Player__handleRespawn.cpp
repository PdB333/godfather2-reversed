// FUNC_NAME: Player::handleRespawn
void Player::handleRespawn(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0090b0a0(param_1);
  if ((iVar1 != -1) && ((*(byte *)(param_1 + 0x5f) & 1) != 0)) {
    FUN_00791e00(0);
    iVar1 = FUN_00791300();
    if (iVar1 != 0) {
      iVar1 = FUN_0043b870(DAT_01131040);
      if (iVar1 != 0) {
        FUN_009b1970();
        return;
      }
    }
  }
  return;
}