// FUNC_NAME: EntityManager::findEntityByTypeInList
undefined1 EntityManager::findEntityByTypeInList(int entityList, int maxCount, undefined4 entityType)
{
  char found;
  
  if (maxCount != 0) {
    do {
      maxCount = maxCount + -1;
      found = EntityManager::isEntityOfType(entityList, entityType, 0);
      if (found != '\0') {
        return 1;
      }
      entityList = entityList + 0x10;  // +0x10: next entity in list (16-byte stride)
    } while (maxCount != 0);
  }
  return 0;
}