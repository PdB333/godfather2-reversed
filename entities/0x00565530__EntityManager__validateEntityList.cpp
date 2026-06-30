// FUNC_NAME: EntityManager::validateEntityList
undefined4 __thiscall EntityManager::validateEntityList(int this, uint *entityIdList)
{
  uint listCount;
  uint validatedCount;
  uint index;
  int *entityArray;
  
  listCount = *entityIdList;
  validatedCount = 0;
  if (listCount != 0) {
    do {
      entityIdList = entityIdList + 1;
      index = 0;
      if (*(uint *)(this + 0x124) == 0) { // +0x124: entityCount
        return 0;
      }
      entityArray = (int *)(this + 0x24); // +0x24: entityArray pointer
      while (*(uint *)(*entityArray + 0x3c) != *entityIdList) { // +0x3c: entityId field
        index = index + 1;
        entityArray = entityArray + 1;
        if (*(uint *)(this + 0x124) <= index) { // +0x124: entityCount
          return 0;
        }
      }
      validatedCount = validatedCount + 1;
    } while (validatedCount < listCount);
  }
  return 1;
}