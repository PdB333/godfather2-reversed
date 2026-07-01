// FUNC_NAME: Player::clearActiveContractor
void __thiscall Player::clearActiveContractor(int this, int contractor)
{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  if ((contractor != 0) && ((*(uint *)(contractor + 0x1f5c) >> 3 & 1) != 0)) {
    uVar3 = 0;
    piVar4 = (int *)(this + 0xa4c); // +0xa4c: activeContractors array (4 slots)
    while ((*piVar4 == 0 || (iVar2 = FUN_00791300(), iVar2 != contractor))) {
      uVar3 = uVar3 + 1;
      piVar4 = piVar4 + 1;
      if (3 < uVar3) {
        // Not found in active contractors list, clear the flag
        *(uint *)(contractor + 0x1f5c) = *(uint *)(contractor + 0x1f5c) & 0xfffffff7;
        return;
      }
    }
    // Found the contractor slot - clear it
    FUN_00790110(0); // Likely some cleanup/notification
    puVar1 = (uint *)(*(int *)(this + 0xa4c + uVar3 * 4) + 0x5c); // +0x5c: contractor flags
    *puVar1 = *puVar1 & 0xffefffff; // Clear bit 20 (0x100000)
    *(undefined4 *)(this + 0xa4c + uVar3 * 4) = 0; // Clear the slot
    *(uint *)(contractor + 0x1f5c) = *(uint *)(contractor + 0x1f5c) & 0xfffffff7; // Clear bit 3
    return;
  }
  return;
}