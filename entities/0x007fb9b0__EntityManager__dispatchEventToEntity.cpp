// FUNC_NAME: EntityManager::dispatchEventToEntity
void __thiscall EntityManager::dispatchEventToEntity(int thisPtr, char entityIndex, undefined4 eventData)
{
  int entityPtr;
  
  // +0x1100: array of entity pointers, each entry is 0x120 bytes apart
  // entityIndex * 0x120 + thisPtr + 0x1100 gives the entity slot
  entityPtr = *(int *)(entityIndex * 0x120 + thisPtr + 0x1100);
  
  // Check if entity exists and is in active state (state == 2)
  if ((entityPtr != 0) && (*(int *)(entityPtr + 0xc) == 2)) {
    // Dispatch the event to the entity's event handler
    FUN_00549fe0(eventData);  // likely Entity::handleEvent or similar
  }
  return;
}