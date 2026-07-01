// FUNC_NAME: Player::getCurrentWeaponOrVehicle
undefined4 __fastcall Player::getCurrentWeaponOrVehicle(int this)
{
  if (DAT_01223484 == 0) {
    return 0;
  }
  if (*(int *)(DAT_01223484 + 8) != 0) {
    return **(undefined4 **)(this + 0x338); // +0x338: currentWeapon pointer
  }
  return **(undefined4 **)(this + 0x3c4); // +0x3c4: currentVehicle pointer
}