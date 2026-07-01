// FUNC_NAME: EntityManager::findEntityByAABB
int __thiscall EntityManager::findEntityByAABB(int thisPtr, int *aabb)
{
  int entityPtr;
  int *currentEntityPtr;
  uint index;
  
  index = 0;
  if (*(uint *)(thisPtr + 0xc) != 0) {
    currentEntityPtr = *(int **)(thisPtr + 8); // +0x8: entity array pointer
    do {
      entityPtr = *currentEntityPtr;
      // Compare AABB min/max coordinates (4 ints: minX, minY, maxX, maxY)
      if ((((*(int *)(entityPtr + 0x1c) == *aabb) &&          // +0x1c: AABB minX
           (*(int *)(entityPtr + 0x20) == aabb[1])) &&        // +0x20: AABB minY
          (*(int *)(entityPtr + 0x24) == aabb[2])) &&         // +0x24: AABB maxX
         (*(int *)(entityPtr + 0x28) == aabb[3])) {           // +0x28: AABB maxY
        return entityPtr;
      }
      index = index + 1;
      currentEntityPtr = currentEntityPtr + 1;
    } while (index < *(uint *)(thisPtr + 0xc)); // +0xC: entity count
  }
  return 0; // Not found
}