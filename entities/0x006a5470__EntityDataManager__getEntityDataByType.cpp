// FUNC_NAME: EntityDataManager::getEntityDataByType
undefined4 * EntityDataManager::getEntityDataByType(undefined4 *outData, int entityTypeId)

{
  int iVar1;
  
  *outData = *(undefined4 *)(*(int *)(*(int *)(entityTypeId + 4) + 0xc) + 0x2c);
  iVar1 = FUN_0088d5f0(outData);
  if (iVar1 == 0) {
    *outData = 0;
  }
  return outData;
}