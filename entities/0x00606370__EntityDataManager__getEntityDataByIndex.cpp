// FUNC_NAME: EntityDataManager::getEntityDataByIndex
undefined1 * EntityDataManager::getEntityDataByIndex(uint entityIndex)
{
  // Check if the index is within the valid range (max 4096 entities)
  if (entityIndex < 0x1000) {
    // Return pointer to the entity data in the global array
    // Each entity data entry is 0x38 bytes (56 bytes)
    // DAT_011a0f28 is the base address of the entity data array
    return &DAT_011a0f28 + entityIndex * 0x38;
  }
  // Invalid index, return null
  return (undefined1 *)0x0;
}