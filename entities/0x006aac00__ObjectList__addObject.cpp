// FUNC_NAME: ObjectList::addObject
void __thiscall ObjectList::addObject(int thisPtr, int objectPtr)
{
  uint index;
  int newCapacity;
  int *objectArray;
  
  index = 0;
  if (*(uint *)(thisPtr + 0x14) != 0) {
    objectArray = *(int **)(thisPtr + 0x10);
    do {
      if (*objectArray == objectPtr) {
        if (-1 < (int)index) {
          return;
        }
        break;
      }
      index = index + 1;
      objectArray = objectArray + 1;
    } while (index < *(uint *)(thisPtr + 0x14));
  }
  // Mark object as not active (+0x68)
  *(undefined1 *)(objectPtr + 0x68) = 0;
  newCapacity = *(int *)(thisPtr + 0x18);
  if (*(int *)(thisPtr + 0x14) == newCapacity) {
    if (newCapacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = newCapacity * 2;
    }
    FUN_006aa370(newCapacity); // likely growArray or reallocate
  }
  objectArray = (int *)(*(int *)(thisPtr + 0x10) + *(int *)(thisPtr + 0x14) * 4);
  *(int *)(thisPtr + 0x14) = *(int *)(thisPtr + 0x14) + 1;
  if (objectArray != (int *)0x0) {
    *objectArray = objectPtr;
  }
  FUN_006aa0e0(objectPtr); // likely objectAdded or initObject
  return;
}