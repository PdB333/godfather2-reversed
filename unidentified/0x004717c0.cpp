// FUN_004717c0: EntityManager::spawnEntity
int __thiscall EntityManager::spawnEntity(EntityManager *this, int entityTypeId, int subTypeId)
{
  int entityHandle;
  int resolvedTypeId;
  float tempFloat;
  float finalValue;

  resolvedTypeId = subTypeId;
  entityHandle = 0;
  if (entityTypeId != 0) {
    if (subTypeId == 0) {
      entityHandle = 0;
      subTypeId = 0;
      resolvedTypeId = resolveEntityType(entityTypeId, &entityTypeId, &subTypeId); // may remap typeID
      if ((resolvedTypeId != 0) && (subTypeId != 0)) {
        entityHandle = createEntityFromSubtype(g_EntityManager, resolvedTypeId);
      }
    }
    else {
      if (this->preCreateCallback != (void(__thiscall *)(EntityManager *, int))0x0) {
        this->preCreateCallback(this, subTypeId);
      }
      entityHandle = createEntityFromType(g_EntityManager, resolvedTypeId);
    }
    if (entityHandle != 0) {
      (**(code **)(*this + 0xb8))(entityHandle); // vfunc: entity->initializeFromData()
      tempFloat = (float10)(**(code **)(*this + 0x110))(); // vfunc: entity->getSpawnRandom()
      finalValue = g_ThresholdLower;
      if (((float10)g_ThresholdLower < tempFloat) &&
         (tempFloat = (float10)(**(code **)(*this + 0x110))(), finalValue = g_ThresholdUpper,
         tempFloat < (float10)1)) {
        tempFloat = (float10)(**(code **)(*this + 0x110))();
        finalValue = (float)tempFloat;
      }
      setEntityProperty(entityHandle, finalValue); // set some scalar property like initial intensity
    }
  }
  return entityHandle;
}