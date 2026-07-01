// FUNC_NAME: Player::setWeaponType
void __thiscall Player::setWeaponType(int this, char weaponType, char param_3)
{
  int iVar1;
  
  if (*(char *)(this + 0x1c1) != weaponType) {
    iVar1 = FUN_00956910(); // likely getPlayerManager or getGameManager
    if ((iVar1 != 0) && (param_3 != '\0')) {
      // +0x48: some manager pointer, +0x10: offset for weapon data
      FUN_0097b440(*(undefined4 *)(iVar1 + 0x48), iVar1 + 0x10, 0, DAT_00d5e288);
    }
  }
  *(char *)(this + 0x1c1) = weaponType; // +0x1C1: current weapon type
  return;
}