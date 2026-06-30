// FUNC_NAME: EntityManager::findEntityByType
int __fastcall EntityManager::findEntityByType(undefined4 this, int entityList, int entityType)
{
  int entityPtr;
  uint index;
  int *entityArray;
  
  entityPtr = 0;
  index = 0;
  if (*(uint *)(entityList + 0xac) != 0) {
    entityArray = *(int **)(entityList + 0xa8); // +0xA8: pointer to entity pointer array
    while ((*entityArray == 0 || (*(int *)(*entityArray + 0x24) != entityType))) { // +0x24: entity type field
      index = index + 1;
      entityArray = entityArray + 1;
      if (*(uint *)(entityList + 0xac) <= index) { // +0xAC: count of entities in list
        return entityPtr;
      }
    }
    entityPtr = (*(int **)(entityList + 0xa8))[index]; // +0xA8: entity pointer array
  }
  return entityPtr;
}