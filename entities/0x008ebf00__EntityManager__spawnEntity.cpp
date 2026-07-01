// FUNC_NAME: EntityManager::spawnEntity
int __thiscall EntityManager::spawnEntity(int this, undefined4 entityType, undefined4 param3, int parentEntity, int spawnFlags)
{
  char cVar1;
  int entityHandle;
  int iVar3;
  undefined4 local_c;
  int local_8;
  undefined1 local_4;
  
  entityHandle = FUN_00483410(entityType, param3); // likely EntityDataManager::createEntity
  if (entityHandle != 0) {
    *(int *)(this + 0x44) = *(int *)(this + 0x44) + 1; // entityCount++ (+0x44)
    if (spawnFlags != 0) {
      local_c = DAT_0112fddc; // some global string/identifier
      local_4 = 0;
      local_8 = entityHandle;
      FUN_00408bf0(&local_c, spawnFlags + 0x3c, 0); // likely setEntityProperty or similar
    }
    if (((parentEntity == 0) || (iVar3 = FUN_004025a0(parentEntity), iVar3 == 0)) ||
       (cVar1 = FUN_00402c80(), cVar1 != '\0')) {
      FUN_00446470(entityHandle, 1); // likely activateEntity or addToWorld
    }
    if (spawnFlags != 0) {
      local_c = DAT_0112fdf8; // another global string/identifier
      local_4 = 0;
      local_8 = entityHandle;
      FUN_00408bf0(&local_c, spawnFlags + 0x3c, 0); // likely setEntityProperty
    }
  }
  return entityHandle;
}