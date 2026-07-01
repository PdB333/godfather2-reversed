// FUNC_NAME: EntityManager::addEntity
void __thiscall EntityManager::addEntity(int this, undefined4 entityData)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  iVar1 = FUN_009c8e50(0x2c); // allocate memory for entity (0x2c = 44 bytes)
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_008c82f0(entityData, this); // construct entity from data
  }
  iVar1 = FUN_008bf190(entityData); // get entity type/hash
  if (iVar1 < 0) {
    iVar1 = *(int *)(this + 0x1ac); // +0x1ac: entity array capacity
    if (*(int *)(this + 0x1a8) == iVar1) { // +0x1a8: entity count
      if (iVar1 == 0) {
        iVar1 = 1;
      }
      else {
        iVar1 = iVar1 * 2; // double capacity
      }
      FUN_008be0b0(iVar1); // resize entity array
    }
    puVar3 = (undefined4 *)(*(int *)(this + 0x1a4) + *(int *)(this + 0x1a8) * 4); // +0x1a4: entity array pointer
    *(int *)(this + 0x1a8) = *(int *)(this + 0x1a8) + 1; // increment count
    if (puVar3 != (undefined4 *)0x0) {
      *puVar3 = uVar2; // store entity pointer
    }
  }
  else {
    puVar3 = (undefined4 *)FUN_008c2340(iVar1); // get entity slot by type
    *puVar3 = uVar2; // store entity pointer
  }
  FUN_00790110(1); // mark dirty
  FUN_00408680(&DAT_012069c4); // notify observers
  return;
}