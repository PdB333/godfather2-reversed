// FUNC_NAME: Player::handleWeaponSwitch
void Player::handleWeaponSwitch(int param_1)
{
  int iVar1;
  
  param_1 = *(undefined4 *)(param_1 + 0x184);
  iVar1 = FUN_006afa90(&param_1);
  if (-1 < iVar1) {
    FUN_006afa40(iVar1);
  }
  return;
}