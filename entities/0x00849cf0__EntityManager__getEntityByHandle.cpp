// FUNC_NAME: EntityManager::getEntityByHandle
int __thiscall EntityManager::getEntityByHandle(int thisPtr, int handle)
{
  int index;
  int entityPtr;
  
  if (handle == 0) {
    return 0;
  }
  
  entityPtr = 0;
  index = FUN_00849a70(handle); // likely handleToIndex or similar
  if (index >= 0) {
    // +0x10: pointer to entity array (array of pointers)
    entityPtr = *(int *)(*(int *)(thisPtr + 0x10) + index * 4);
  }
  return entityPtr;
}