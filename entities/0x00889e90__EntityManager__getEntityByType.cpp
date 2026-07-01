// FUNC_NAME: EntityManager::getEntityByType
int EntityManager::getEntityByType(int entityType)
{
  int entityArray[2];
  
  FUN_008896d0(entityArray, &entityType);
  if (entityArray[0] != *(int *)(PTR_DAT_00e541fc + DAT_00e54200 * 4)) {
    return entityArray[0] + 4;
  }
  return 0;
}