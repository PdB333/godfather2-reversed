// FUNC_NAME: EntityManager::markDirty
void EntityManager::markDirty(void)
{
  byte *pbVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  // Mark this entity as dirty (bit 0 of flags at +0x20+5)
  pbVar1 = (byte *)(*(int *)(this + 0x20) + 5);
  *pbVar1 = *pbVar1 | 1;
  
  // Mark all child entities (at +0x08) with type 4 as dirty
  iVar3 = 0;
  if (0 < *(int *)(this + 0x28)) {
    do {
      if (*(int *)(*(int *)(this + 8) + iVar3 * 8) == 4) {
        pbVar1 = (byte *)(*(int *)(*(int *)(this + 8) + 4 + iVar3 * 8) + 5);
        *pbVar1 = *pbVar1 | 1;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(this + 0x28));
  }
  
  // Mark all entities in list at +0x1c as dirty
  iVar3 = 0;
  if (0 < *(int *)(this + 0x24)) {
    do {
      pbVar1 = (byte *)(*(int *)(*(int *)(this + 0x1c) + iVar3 * 4) + 5);
      *pbVar1 = *pbVar1 | 1;
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(this + 0x24));
  }
  
  // Check entities at +0x10 for pending dirty state
  iVar3 = 0;
  if (0 < *(int *)(this + 0x34)) {
    do {
      if ((*(byte *)(*(int *)(*(int *)(this + 0x10) + iVar3 * 4) + 5) & 0x11) == 0) {
        FUN_00626640();
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(this + 0x34));
  }
  
  // Mark all entities in list at +0x18 as dirty (each entry is 0xc bytes)
  iVar3 = 0;
  if (0 < *(int *)(this + 0x38)) {
    iVar4 = 0;
    do {
      piVar2 = (int *)(iVar4 + *(int *)(this + 0x18));
      iVar3 = iVar3 + 1;
      *(byte *)(*piVar2 + 5) = *(byte *)(*piVar2 + 5) | 1;
      iVar4 = iVar4 + 0xc;
    } while (iVar3 < *(int *)(this + 0x38));
  }
  return;
}