// FUNC_NAME: GunManager::updateWeapons
void __thiscall updateGunWeapons(int this)
{
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  updateWeaponAnimations();  // FUN_008764f0 - likely updates animation state for all weapons
  iVar2 = getPlayerCameraMatrix();  // FUN_00471610 - returns camera matrix/transform
  *(undefined4 *)(this + 0xe08) = *(undefined4 *)(iVar2 + 0x30);  // camera world position X
  *(undefined4 *)(this + 0xe0c) = *(undefined4 *)(iVar2 + 0x34);  // camera world position Y
  *(undefined4 *)(this + 0xe10) = *(undefined4 *)(iVar2 + 0x38);  // camera world position Z
  uVar3 = 0;
  piVar4 = (int *)(this + 0xda4);  // array of 8 weapon active flags (int per weapon)
  puVar5 = (undefined4 *)(this + 0xce8);  // array of weapon data (3 ints per weapon: weaponId, ammo, maxAmmo)
  do {
    if (*piVar4 != 0) {  // weapon slot is active/equipped
      local_c = puVar5[-1];   // weapon ID (previous element in array)
      local_8 = 0;             // padding/zero
      local_4 = *puVar5;      // ammo count
      processWeaponTrajectory(uVar3, &local_c, puVar5[1], puVar5[0x17], puVar5[0x18], puVar5[0x19], *piVar4);
    }
    uVar3 = uVar3 + 1;
    piVar4 = piVar4 + 1;
    puVar5 = puVar5 + 3;  // each weapon data entry is 12 bytes (3 ints)
  } while (uVar3 < 8);
  return;
}