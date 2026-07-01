// FUNC_NAME: Player::updateWeaponAmmoDisplay
void __fastcall Player::updateWeaponAmmoDisplay(int thisPtr)
{
  int *vtablePtr;
  
  vtablePtr = *(int **)(*(int *)(thisPtr + 0xf8) + 0x130); // +0xF8: player->weaponManager, +0x130: weaponManager->hudInterface
  if (vtablePtr != (int *)0x0) {
    // Update ammo count display (first weapon slot)
    (**(code **)(*vtablePtr + 0x44))(0xa57893c3, *(undefined4 *)(thisPtr + 0xcc)); // +0xCC: player->currentWeaponAmmo
    // Update reserve ammo display
    (**(code **)(*vtablePtr + 0x44))(0xfc66fe75, *(undefined4 *)(thisPtr + 0xd0)); // +0xD0: player->currentWeaponReserve
    // Check if ammo is low (less than 8 rounds in current clip)
    if (7 < ((byte)*(undefined4 *)(thisPtr + 0xcc) & 0xf)) {
      (**(code **)(*vtablePtr + 0x48))(0x8276b009, 1); // Show low ammo warning
    }
    // Check if ammo is critical (less than 0x70000000 threshold)
    if (0x70000000 < (*(uint *)(thisPtr + 0xcc) & 0xf0000000)) {
      (**(code **)(*vtablePtr + 0x48))(0xdb4f6cf9, 1); // Show critical ammo warning
    }
  }
}