// FUNC_NAME: EntityManager::getEntityByIndex
undefined4 __thiscall EntityManager::getEntityByIndex(int this, uint index)
{
  int entityPtr;
  
  if ((index < *(uint *)(this + 8)) &&
     (entityPtr = *(int *)(*(int *)(this + 4) + index * 4), entityPtr != 0)) {
    return *(undefined4 *)(entityPtr + 8); // +0x8: entity ID
  }
  return 0;
}