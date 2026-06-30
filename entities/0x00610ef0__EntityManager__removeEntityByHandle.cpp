// FUNC_NAME: EntityManager::removeEntityByHandle
undefined4 EntityManager::removeEntityByHandle(uint entityHandle)

{
  int iVar1;
  int iVar2;
  
  if (((entityHandle < 0x1000) && (iVar2 = entityHandle * 0x38, iVar2 != -0x11a0f28)) &&
     (iVar1 = *(int *)(&DAT_011a0f38 + iVar2), iVar1 != 0)) {
    // Lock the entity manager (likely mutex or critical section)
    FUN_00616c30();
    if (iVar2 != -0x11a0f28) {
      // Clear the entity slot in the handle table
      *(undefined4 *)(&DAT_011a0f38 + iVar2) = 0;
    }
    // Destroy the entity object
    FUN_00611090(iVar1);
    // Unlock the entity manager
    FUN_00610af0();
    return 1;
  }
  return 0;
}