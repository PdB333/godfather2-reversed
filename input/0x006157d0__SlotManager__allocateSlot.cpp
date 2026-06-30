// FUNC_NAME: SlotManager::allocateSlot
undefined4 * SlotManager::allocateSlot(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  
  FUN_00ab4db0(&DAT_00e2ac20);  // lock mutex
  iVar3 = 0;
  piVar2 = &DAT_01222574;  // slot array base
  do {
    if (*piVar2 == 0) {  // slot is free
      puVar1 = &DAT_01222574 + iVar3 * 6;  // slot entry (6 dwords per slot)
      if (puVar1 == (undefined4 *)0x0) {
        FUN_00ab4e70();  // unlock mutex
        return (undefined4 *)0x0;
      }
      *puVar1 = 1;  // mark slot as allocated
      FUN_00ab4e70();  // unlock mutex
      return puVar1;
    }
    piVar2 = piVar2 + 6;  // advance to next slot
    iVar3 = iVar3 + 1;
  } while ((int)piVar2 < 0x122312c);  // end of slot array
  FUN_00ab4e70();  // unlock mutex
  return (undefined4 *)0x0;  // no free slot found
}