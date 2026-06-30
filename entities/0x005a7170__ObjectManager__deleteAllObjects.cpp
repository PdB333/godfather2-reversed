// FUNC_NAME: ObjectManager::deleteAllObjects
void ObjectManager::deleteAllObjects(void)
{
  int *pObjectCount; // in_EAX - pointer to object count
  int iObjectCount;
  int *ppObjectArray;
  int iIndex;
  
  iObjectCount = *pObjectCount; // +0x00: number of objects
  iIndex = 0;
  ppObjectArray = pObjectCount + 1; // +0x04: array of object pointers (0x40 slots)
  do {
    if (*ppObjectArray != 0) {
      // Call virtual destructor via vtable at DAT_0103aee0
      // The vtable index is derived from the object's type ID (lower 15 bits)
      (**(code **)(&gObjectVtableTable + (*(uint *)*ppObjectArray & 0x7fff) * 4))((uint *)*ppObjectArray);
      iObjectCount = iObjectCount + -1;
      if (iObjectCount == 0) {
        return;
      }
    }
    iIndex = iIndex + 1;
    ppObjectArray = ppObjectArray + 1;
  } while (iIndex < 0x40); // 64 slots max
  return;
}