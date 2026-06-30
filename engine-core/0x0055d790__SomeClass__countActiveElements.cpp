// FUNC_NAME: SomeClass::countActiveElements
int __fastcall countActiveElements(void* thisPtr)
{
  int elementCount = *(int*)((char*)thisPtr + 0x4c); // element count
  int activeCount = 0;
  if (0 < elementCount) {
    int* elementArray = (int*)(*(int*)((char*)thisPtr + 0x48) + 0x24); // first element's state field
    do {
      if (*elementArray != 0) {
        activeCount = activeCount + 1;
      }
      elementArray = elementArray + 0x30; // step to next element (0x30 bytes per element)
      elementCount = elementCount + -1;
    } while (elementCount != 0);
  }
  return activeCount;
}