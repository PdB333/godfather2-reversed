// Xbox PDB: EARS_Apt_UIHud_SetHollowpointBullet
// FUNC_NAME: Gun::setHollowpointBulletVisible
void __thiscall Gun::setHollowpointBulletVisible(bool visible)
{
  // Update flag at +0x5c (bit 24) to control hollowpoint bullet visibility
  if (visible) {
    *(uint *)(this + 0x5c) |= 0x1000000;
  } else {
    *(uint *)(this + 0x5c) &= 0xfeffffff;
  }

  // Check if the gun is active (+0x48) and not in a special state (+0x49 bits 1 and 3)
  if ((*(char *)(this + 0x48) != '\0') && ((*(byte *)(this + 0x49) & 0x0A) == 0)) {
    if (visible && ((*(uint *)(this + 0x5c) >> 0x1b & 1) != 0)) {
      // If visible and some other condition (bit 27 of +0x5c) is set, show the bullet
      FUN_005a04a0("ShowHollowpointBullet", 0, &DAT_00d8a64c, 0);
      return;
    }
    // Otherwise hide the bullet
    FUN_005a04a0("HideHollowpointBullet", 0, &DAT_00d8a64c, 0);
  }
}