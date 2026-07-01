// FUNC_NAME: EntityManager::removeMatchingEntities
void __thiscall EntityManager::removeMatchingEntities(undefined4 *this, undefined4 *matchData)
{
  undefined4 *current;
  undefined4 *next;
  char matchResult;
  int entityPtr;
  uint index;
  
  // Iterate through linked list of entities (first pointer at this[0])
  current = (undefined4 *)*this;
  while (next = current, next != (undefined4 *)0x0) {
    current = (undefined4 *)*next;
    // Check if entity has a valid pointer at offset +0x18 (entity data)
    if (((next[6] != 0) && (entityPtr = next[6] + -0x48, entityPtr != 0)) &&
       (matchResult = FUN_0043c6c0(entityPtr,*matchData), matchResult != '\0')) {
      // Remove entity from list
      FUN_00788b40(next);
      // Free entity data at +0x18
      if (next[6] != 0) {
        FUN_004daf90(next + 6);
      }
      // Call destructor via vtable (offset +0x2c40 from global DAT_0112aa1c)
      (**(code **)(*(int *)(DAT_0112aa1c + 0x2c40) + 4))(next,0);
    }
  }
  
  // Check array of entity IDs at this[0x16] (count at this[0x17])
  index = 0;
  if (this[0x17] != 0) {
    do {
      entityPtr = *(int *)(this[0x16] + index * 8);
      if (((entityPtr == 0) || (entityPtr = entityPtr + -0x48, entityPtr == 0)) ||
         (matchResult = FUN_0043c6c0(entityPtr,*matchData), matchResult == '\0')) {
        index = index + 1;
      }
      else {
        // Remove entity by index
        FUN_00783330(index);
      }
    } while (index < (uint)this[0x17]);
  }
  
  // Cleanup/update state
  FUN_00788720();
  return;
}