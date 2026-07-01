// FUNC_NAME: EntityManager::findEntityBySomeId
uint __thiscall EntityManager::findEntityBySomeId(int thisPtr, int someId)
{
  uint index;
  int *entityArray;

  index = 0xffffffff;
  if (*(uint *)(thisPtr + 0x14) != 0) {
    entityArray = *(int **)(thisPtr + 0x10); // +0x10: pointer to array of entity pointers
    index = 0;
    while (*(int *)(*entityArray + 0x50) != someId) { // +0x50: entity's someId field
      index = index + 1;
      entityArray = entityArray + 1;
      if (*(uint *)(thisPtr + 0x14) <= index) { // +0x14: count of entities
        return 0xffffffff;
      }
    }
  }
  return index;
}