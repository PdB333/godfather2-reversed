// FUNC_NAME: Player::resetPlayerState
void Player::resetPlayerState(void)
{
  char cVar1;
  undefined4 *puVar2;
  
  cVar1 = FUN_00481640(); // likely isPlayerAlive() or similar check
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)FUN_007ab170(); // getPlayerData() - returns player data struct
    FUN_007e0bd0(0); // resetHealth(0)
    FUN_007e0a50(0); // resetArmor(0)
    FUN_007e0a90(0); // resetWeapon(0)
    FUN_007e0ad0(0); // resetAmmo(0)
    FUN_007e0b10(0); // resetGrenades(0)
    FUN_007e0b50(0); // resetSpecialItem(0)
    if (puVar2[0x4d] != 0) { // +0x134 - activeMission pointer
      FUN_004daf90(puVar2 + 0x4d); // releaseMission(puVar2 + 0x4d)
      puVar2[0x4d] = 0;
    }
    if (puVar2[0x4f] != 0) { // +0x13C - pendingMission pointer
      FUN_004daf90(puVar2 + 0x4f); // releaseMission(puVar2 + 0x4f)
      puVar2[0x4f] = 0;
    }
    (**(code **)*puVar2)(0x7fffffff); // vtable call - resetPlayerState(0x7fffffff)
  }
  return;
}