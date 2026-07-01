// FUNC_NAME: Player::handleWeaponFire
void __fastcall Player::handleWeaponFire(int *thisPlayer)
{
  int iVar1;
  
  // Check if weapon type is valid (not null and not 0x48 = 72, likely "none" or "fist")
  if ((thisPlayer[0x17] != 0) && (thisPlayer[0x17] != 0x48)) {
    // Get the weapon instance from the weapon manager
    iVar1 = FUN_00724cc0(); // likely WeaponManager::getCurrentWeapon
    if (iVar1 != 0) {
      // Play weapon fire sound effect (sound ID 8)
      FUN_007757b0(8); // likely AudioManager::playSoundEffect
      
      // Call weapon's fire method via vtable
      // vtable+0x2c = Weapon::fire(bool, bool, bool, float, float)
      (**(code **)(*iVar1 + 0x2c))(iVar1, 1, 1, 0, 0x3f800000, 0x3f800000); // 0x3f800000 = 1.0f
      return;
    }
    // If no weapon instance, set weapon state flag bit 0 (likely "firing" flag)
    thisPlayer[0x19] = thisPlayer[0x19] | 1;
  }
  return;
}