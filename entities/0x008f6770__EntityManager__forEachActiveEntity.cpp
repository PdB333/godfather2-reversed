// FUNC_NAME: EntityManager::forEachActiveEntity
void __thiscall EntityManager::forEachActiveEntity(int *this, code *callback)
{
  int entityPtr;
  uint index;
  
  index = 0;
  if (this[1] != 0) {
    do {
      entityPtr = *(int *)(*this + index * 4);
      if ((entityPtr != 0) && ((*(byte *)(entityPtr + 0x40) & 1) != 0)) {
        (*callback)(entityPtr);
      }
      index = index + 1;
    } while (index < (uint)this[1]);
  }
  // +0x00: pointer to entity array
  // +0x04: count of entities
  // +0x40: entity flags (bit 0 = active flag)
  FUN_008f66c0(); // likely some cleanup or post-iteration hook
  return;
}