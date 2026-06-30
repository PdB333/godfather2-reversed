// FUNC_NAME: EntityManager::removeAllExceptPlayer
void __thiscall EntityManager::removeAllExceptPlayer(EntityManager *this)
{
  int count;
  int *arrayBase;
  int typeId;
  uint i;
  
  count = *(int *)((char *)this + 0x24);
  if (count != 0) {
    arrayBase = *(int **)((char *)this + 0x20);
    for (i = 0; i < (uint)count; i = i + 1) {
      typeId = arrayBase[i * 2]; // each element is 8 bytes, first int at index*2
      if ((typeId != 0) && (typeId != 0x48)) {
        FUN_0072cf40(); // release/delete the entity
      }
    }
  }
  return;
}