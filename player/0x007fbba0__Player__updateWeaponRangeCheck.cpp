// FUNC_NAME: Player::updateWeaponRangeCheck
void __fastcall Player::updateWeaponRangeCheck(int thisPtr)
{
  int *pWeaponSlot; // pointer to weapon slot at +0x1e90
  int *pWeaponData; // pointer to weapon data (offset -0x48 from slot)
  int local_8[2];   // unused local
  char result;      // result from virtual call
  int someValue;    // value from FUN_00471610
  int distanceSq;   // squared distance

  pWeaponSlot = (int *)(thisPtr + 0x1e90); // +0x1e90: current weapon slot index/pointer
  if ((*(int *)(thisPtr + 0x1e90) != 0) && (*(int *)(thisPtr + 0x1e90) != 0x48)) {
    // Get weapon data pointer (offset -0x48 from slot)
    if (*pWeaponSlot == 0) {
      pWeaponData = (int *)0x0;
    }
    else {
      pWeaponData = (int *)(*pWeaponSlot + -0x48);
    }
    local_8[0] = 0;
    // Virtual call to check if weapon can fire (hash: 0xa5975eb2)
    result = (**(code **)(*pWeaponData + 0x10))(0xa5975eb2, local_8);
    if ((result != '\0') && (unaff_ESI != 0)) {
      someValue = FUN_00471610(); // Get some game object/entity
      someValue = FUN_00874ce0(someValue + 0x30, 0, &stack0xfffffff4); // Get distance to target
      // Check if squared distance is less than threshold (unaff_EBX)
      if ((*(float *)(someValue + 0x18) * *(float *)(someValue + 0x18) < unaff_EBX) && (*pWeaponSlot != 0)) {
        FUN_004daf90(pWeaponSlot); // Stop firing / release weapon
        *pWeaponSlot = 0;          // Clear weapon slot
      }
    }
  }
  return;
}