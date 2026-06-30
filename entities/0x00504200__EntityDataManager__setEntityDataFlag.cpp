// FUNC_NAME: EntityDataManager::setEntityDataFlag
void EntityDataManager::setEntityDataFlag(undefined4 param_1, undefined4 param_2)
{
  undefined4 flagValue;
  
  flagValue = 0x50; // +0x50: Entity flag for "isActive" or similar
  FUN_004eba90(param_1, param_2, &flagValue, 1); // Set flag at offset 0x50 to 1 (true)
  return;
}