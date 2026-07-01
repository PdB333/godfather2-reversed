// FUNC_NAME: EntityListManager::getNextEntity
undefined4 * __thiscall EntityListManager__getNextEntity(int this,undefined4 *outEntity,undefined4 param_3)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined **local_60 [19];
  undefined4 local_14;
  
  if (*(int *)(this + 0xc) == 0) { // +0xC: entity count
    FUN_008334a0(); // resetEntityList
  }
  else {
    if (*(int *)(this + 0xc) == 1) { // Only one entity
      iVar4 = **(int **)(this + 8); // +0x8: entity array
      FUN_0081f9f0(iVar4); // copyEntityData
      *outEntity = &PTR_LAB_00d73738; // vtable pointer
      outEntity[0x13] = *(undefined4 *)(iVar4 + 0x4c); // +0x4C: entity ID
      return outEntity;
    }
    uVar3 = FUN_0082c770(param_3); // findIndexInList
    if (uVar3 != 0xffffffff) {
      *(uint *)(this + 4) = uVar3; // +0x4: current index
      if (uVar3 < *(int *)(this + 0xc) - 1U) {
        iVar4 = uVar3 + 1;
      }
      else {
        iVar4 = 0;
      }
      iVar1 = *(int *)(*(int *)(this + 8) + uVar3 * 4); // current entity
      iVar4 = *(int *)(*(int *)(this + 8) + iVar4 * 4); // next entity (wrap)
      cVar2 = FUN_00835a00(param_3,iVar4 + 4); // compareEntityIDs
      if (cVar2 != '\0') {
        iVar4 = iVar1;
      }
      FUN_0082bc80(iVar4); // copyEntityToOutput
      return outEntity;
    }
    FUN_008334a0(); // resetEntityList
  }
  local_14 = _DAT_00d5780c;
  local_60[0] = &PTR_LAB_00d73738;
  FUN_0081f9f0(local_60); // copyDefaultEntity
  *outEntity = &PTR_LAB_00d73738;
  outEntity[0x13] = local_14;
  return outEntity;
}