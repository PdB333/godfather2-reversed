// FUNC_NAME: Player::updateWeaponAmmoDisplay
void __fastcall Player::updateWeaponAmmoDisplay(int this)
{
  int weaponData;
  
  // Check if current weapon slot is valid and not the "unarmed" slot (0x48 = 72)
  if ((*(int *)(this + 0x1b4) != 0) && (*(int *)(this + 0x1b4) != 0x48)) {
    // Get weapon data pointer - offset 0x48 is the weapon data array entry size
    if (*(int *)(this + 0x1b4) == 0) {
      weaponData = 0;
    }
    else {
      weaponData = *(int *)(this + 0x1b4) + -0x48;
    }
    // Compare weapon's ammo count (+0x1ed4) with the player's ammo pool (+0x58 -> +0x1ed4)
    if (*(int *)(weaponData + 0x1ed4) == *(int *)(*(int *)(this + 0x58) + 0x1ed4)) {
      // Ammo matches - show full ammo indicator (0x3c = 60, likely a UI icon ID)
      FUN_007f6420(0x3c);
      return;
    }
    // Ammo doesn't match - show low ammo indicator
    FUN_007f63e0(0x3c);
  }
  return;
}