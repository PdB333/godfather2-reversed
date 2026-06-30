// FUNC_NAME: EntityManager::removeEntry
// Address: 0x005f72f0
// Removes a pointer from a dynamic array, shifting remaining elements left,
// then calls virtual destructor (via vtable) with delete flag 1.
// Used by entity/object manager containers to release references.

// Structure at param_1 (likely EntityManager or similar container):
// +0x04: pointer to array of void* elements
// +0x08: current count of elements

// Returns 1 on success, undefined on failure (function always returns 1)
undefined4 __thiscall EntityManager::removeEntry(int thisPtr, undefined4 *elementToRemove)
{
  uint currentCount;
  uint index;
  int *arrayPtr;
  
  currentCount = *(uint *)(thisPtr + 8);
  index = 0;
  if (currentCount != 0) {
    arrayPtr = *(int **)(thisPtr + 4);
    // Linear search for matching pointer
    do {
      if ((undefined4 *)*arrayPtr == elementToRemove) {
        // Shift remaining elements left if not last element
        if (index < currentCount - 1) {
          do {
            *(undefined4 *)(*(int *)(thisPtr + 4) + index * 4) =
                 *(undefined4 *)(*(int *)(thisPtr + 4) + 4 + index * 4);
            index = index + 1;
          } while (index < *(int *)(thisPtr + 8) - 1U);
        }
        // Decrement count after removal
        *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + -1;
        break;
      }
      index = index + 1;
      arrayPtr = arrayPtr + 1;
    } while (index < currentCount);
  }
  // Release the element if valid - calls virtual destructor with delete flag = 1
  if (elementToRemove != (undefined4 *)0x0) {
    (**(code **)*elementToRemove)(1);
  }
  return 1;
}