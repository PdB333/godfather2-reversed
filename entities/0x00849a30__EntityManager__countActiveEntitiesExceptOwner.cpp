// FUNC_NAME: EntityManager::countActiveEntitiesExceptOwner
int __fastcall EntityManager::countActiveEntitiesExceptOwner(int this)
{
  int count = 0;
  int numEntities = *(int *)(this + 0x14);
  if (numEntities != 0) {
    int **entityList = *(int ***)(this + 0x10);
    do {
      int *entity = *entityList;
      // Check if entity is active (bit 0 of +0x58 is not set)
      if (((~*(byte *)(entity + 0x58) & 1) != 0) &&
         // Exclude entities with the same owner (+0x50) as this manager's owner (+0x8)
         (*(int *)(entity + 0x50) != *(int *)(this + 8))) {
        count = count + 1;
      }
      entityList = entityList + 1;
      numEntities = numEntities + -1;
    } while (numEntities != 0);
  }
  return count;
}