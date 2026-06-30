// FUNC_NAME: EntityDataManager::getEntityDataByHandle
undefined4 __fastcall EntityDataManager::getEntityDataByHandle(undefined4 param_1, undefined4 param_2)
{
  int iVar1;
  undefined1 local_5;
  undefined1 local_4 [4];
  
  iVar1 = FUN_005f0560(param_2, &local_5, local_4); // Lookup entity data by handle
  if (iVar1 != 0) {
    return *(undefined4 *)(iVar1 + 0x18); // Return pointer to entity data at offset +0x18
  }
  return 0;
}