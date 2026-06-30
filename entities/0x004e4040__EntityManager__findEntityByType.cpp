// FUNC_NAME: EntityManager::findEntityByType
int EntityManager::findEntityByType(int entityType)
{
  int i = 0;
  if (0 < g_entityCount) {
    do {
      // g_entityArray is an array of entity pointers at 0x11946b8
      // Each entity has a type field at offset +0x8
      if (*(int *)(g_entityArray[i] + 8) == entityType) {
        return g_entityArray[i];
      }
      i = i + 1;
    } while (i < g_entityCount);
  }
  return 0;
}