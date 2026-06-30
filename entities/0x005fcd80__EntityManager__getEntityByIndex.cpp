// FUNC_NAME: EntityManager::getEntityByIndex
int __thiscall EntityManager::getEntityByIndex(int thisPtr, int index)
{
  ushort entityId;
  int entityPtr;
  
  entityId = *(ushort *)(*(int *)(thisPtr + 0x34) + index * 2); // +0x34: entityIdArray (array of ushort)
  entityPtr = 0;
  if ((entityId != 0xffff) && (entityPtr = *(int *)(index * 8 + *(int *)(thisPtr + 0x38)), entityPtr == 0)) { // +0x38: entityPtrArray (array of pointers, 8 bytes each)
    entityPtr = FUN_005faf10((uint)entityId * 0x10 + *(int *)(thisPtr + 0x28)); // +0x28: entityDataBase
    if (entityPtr != 0) {
      FUN_005fa490(entityPtr); // likely entity constructor/init
    }
  }
  return entityPtr;
}