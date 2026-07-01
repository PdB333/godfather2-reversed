// FUNC_NAME: Player::updateWeaponOrAbilityVisual
void __fastcall Player::updateWeaponOrAbilityVisual(int *thisPtr)
{
  // Check if the player is currently in a specific state (bit 27 of a flag at offset +0x24a0 from a member at +0x58)
  if ((*(uint *)(thisPtr[0x16] + 0x24a0) >> 0x1b & 1) != 0) {
    // If in that state, call a virtual function (likely setWeaponVisual or similar) with a specific weapon/ability ID
    (**(code **)(*thisPtr + 0x2c))(0xe01f278d, 1, 1, 1, 0x3f800000, 0x3f800000);
    return;
  }
  // Otherwise, call the same virtual function with a different weapon/ability ID
  (**(code **)(*thisPtr + 0x2c))(0xe587b22b, 1, 1, 1, 0x3f800000, 0x3f800000);
  return;
}