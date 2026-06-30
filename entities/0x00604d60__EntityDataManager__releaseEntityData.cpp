// FUNC_NAME: EntityDataManager::releaseEntityData
void EntityDataManager::releaseEntityData(void)

{
  undefined4 in_EAX;
  int entityData;
  
  entityData = EntityDataManager::findEntityData(in_EAX);
  if (entityData != 0) {
    EntityDataManager::deallocateEntityData(entityData); // +0x4300 - deallocates the entity data block
  }
  return;
}