// FUNC_NAME: EntityManager::removeEntityByHandle
void __thiscall EntityManager::removeEntityByHandle(int this, int entityHandle)
{
  int index;
  
  if (entityHandle != 0) {
    index = FUN_00849a70(entityHandle); // likely getIndexFromHandle(entityHandle)
    if ((-1 < index) && (*(int *)(*(int *)(this + 0x10) + index * 4) != 0)) {
      FUN_008490a0(); // likely removeEntityAtIndex(index)
    }
  }
  return;
}