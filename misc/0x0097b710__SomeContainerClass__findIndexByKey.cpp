// FUNC_NAME: SomeContainerClass::findIndexByKey
uint __thiscall findIndexByKey(int param_1, int param_2)
{
  int *currentPointer;
  uint elementCount;
  uint index;

  // Get the count of elements stored at offset +0x30
  elementCount = *(uint *)(param_1 + 0x30);
  if (elementCount != 0) {
    // Start at offset +0x10 (likely an array of ptr-sized entries)
    currentPointer = (int *)(param_1 + 0x10);
    index = 0;
    // Linear scan through array
    while (*currentPointer != param_2) {
      index = index + 1;
      currentPointer = currentPointer + 1;
      // If we've exhausted all elements, return -1 (not found)
      if (elementCount <= index) {
        return 0xffffffff; // -1
      }
    }
    return index;
  }
  // Return -1 if container is empty
  return 0xffffffff;
}