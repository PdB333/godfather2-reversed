// FUNC_NAME: Player::updateCurrentWeaponAmmo
void __fastcall Player::updateCurrentWeaponAmmo(int *this)
{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = FUN_00471610(); // likely getGameManager or getSimManager
  iVar1 = FUN_006b0ce0(iVar1 + 0x30); // likely getPlayerComponent or getPlayerData
  if (iVar1 != 0) {
    iVar2 = *(int *)(iVar1 + 0x184); // +0x184: currentWeaponAmmo or ammoCount
  }
  iVar1 = (**(code **)(*this + 0x2c8))(); // virtual call: getCurrentWeaponAmmo or getWeaponAmmo
  if (iVar2 != iVar1) {
    this[0x7bb] = iVar2; // +0x1EEC (0x7bb * 4): storedAmmo or cachedAmmo
  }
  return;
}