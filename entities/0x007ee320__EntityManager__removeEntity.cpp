// FUNC_NAME: EntityManager::removeEntity
int __thiscall EntityManager::removeEntity(int param_1, int param_2)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  // +0x8: entityIndex/slot (or -1 if not in use)
  iVar3 = *(int *)(param_2 + 8);
  if (iVar3 != -1) {
    // Call something before removing (likely cleanup or destructor-like)
    FUN_007ee0e0(param_2);
    // Mark as not in use
    *(undefined4 *)(param_2 + 8) = 0xffffffff;
    // +0x1c: pointer to an array of per-slot reference counts (each slot 0xc bytes)
    iVar2 = *(int *)(param_1 + 0x1c);
    // Decrement reference count for this entity's slot
    piVar1 = (int *)(iVar2 + iVar3 * 0xc);
    *piVar1 = *piVar1 + -1;
    // +0x10: total entity count in manager
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    iVar3 = iVar2 + iVar3 * 0xc;
  }
  // If no more entities, call a global function (likely destruction/cleanup of manager)
  if (*(int *)(param_1 + 0x10) == 0) {
    iVar3 = FUN_004086d0(&DAT_012069c4);
  }
  return iVar3;
}