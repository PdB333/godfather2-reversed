// FUNC_NAME: SomeClass::clearWeaponSlots
void __fastcall SomeClass::clearWeaponSlots(int this)
{
  int *weaponSlot; // pointer to weapon slot array at this+0xB0
  int slotCount;   // loop counter for 3 weapon slots
  
  weaponSlot = (int *)(this + 0xb0); // +0xB0: weapon slot array (3 slots)
  slotCount = 3;
  do {
    if (*weaponSlot != 0) {
      FUN_006065a0(*weaponSlot, 0); // likely release/deallocate weapon object
      *weaponSlot = 0;              // clear slot pointer
    }
    weaponSlot = weaponSlot + 1;
    slotCount = slotCount + -1;
  } while (slotCount != 0);
  return;
}