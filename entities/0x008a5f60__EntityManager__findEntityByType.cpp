// FUNC_NAME: EntityManager::findEntityByType
undefined4 FUN_008a5f60(int entityType)
{
  int iVar1;
  uint entityCount;
  uint index;
  int *entityList;
  
  entityCount = FUN_0043ff40(); // GetEntityCount or similar
  index = 0;
  if (entityCount != 0) {
    entityList = *(int **)(DAT_012233a0 + 4); // +0x4: entity list pointer
    do {
      iVar1 = *entityList;
      if (((iVar1 != 0) && (iVar1 != 0x1f30)) && (*(int *)(iVar1 + -0x38) == entityType)) {
        return *(undefined4 *)(iVar1 + -0x50); // Return entity ID or handle at offset -0x50
      }
      index = index + 1;
      entityList = entityList + 1;
    } while (index < entityCount);
  }
  return 0;
}