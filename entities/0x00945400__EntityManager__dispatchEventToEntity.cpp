// FUNC_NAME: EntityManager::dispatchEventToEntity
void EntityManager::dispatchEventToEntity(uint entityId, undefined4 param2, undefined4 param3, undefined4 *eventData, undefined4 param5, undefined4 param6, undefined4 param7, undefined4 param8, undefined4 param9)
{
  int iVar1;
  uint *puVar2;
  undefined4 *puVar3;
  undefined4 local_50 [19];
  
  FUN_00608e60(); // lock mutex
  puVar2 = *(uint **)(*(int *)(*(int *)(DAT_01223398 + 8) + 4) +
                     (entityId % *(uint *)(*(int *)(DAT_01223398 + 8) + 8)) * 4);
  if (puVar2 != (uint *)0x0) {
    while (*puVar2 != entityId) {
      puVar2 = (uint *)puVar2[2];
      if (puVar2 == (uint *)0x0) {
        FUN_00608e70(); // unlock mutex
        return;
      }
    }
    if (((puVar2 != (uint *)0x0) && (puVar2 + 1 != (uint *)0x0)) && (puVar2[1] != 0)) {
      puVar3 = local_50;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *eventData;
        eventData = eventData + 1;
        puVar3 = puVar3 + 1;
      }
      FUN_00944450(param2,param3,local_50,param5,param6,param7,param8,param9);
    }
  }
  FUN_00608e70(); // unlock mutex
  return;
}