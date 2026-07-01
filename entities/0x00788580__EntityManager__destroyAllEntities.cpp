// FUNC_NAME: EntityManager::destroyAllEntities
void __thiscall EntityManager::destroyAllEntities(int this, int param_2)
{
  uint entityCount;
  int entityPtr;
  uint i;
  
  entityCount = *(uint *)(this + 0x5c); // +0x5c: number of entities in the list
  if (((entityCount != 0) && (param_2 != 0)) && (entityPtr = FUN_0043b870(DAT_0112af58), entityPtr != 0)) {
    FUN_00783270(this); // likely clearEntityList or similar
    i = 0;
    if (entityCount != 0) {
      do {
        entityPtr = *(int *)(*(int *)(this + 0x58) + i * 8); // +0x58: entity array (8 bytes per entry)
        if ((entityPtr != 0) && (entityPtr = entityPtr + -0x48, entityPtr != 0)) {
          FUN_00784020(entityPtr,0); // likely destroyEntity or releaseEntity
        }
        i = i + 1;
      } while (i < entityCount);
    }
  }
  return;
}