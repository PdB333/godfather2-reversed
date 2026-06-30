// FUNC_NAME: GenericMap::findValueByKey
undefined4 __thiscall GenericMap::findValueByKey(int thisPtr, int key)
{
  undefined4 value;
  uint index;
  int *keyPtr;
  
  value = 0;
  index = 0;
  if (*(uint *)(thisPtr + 0x88) != 0) {
    keyPtr = (int *)(thisPtr + 8);
    while (*keyPtr != key) {
      index = index + 1;
      keyPtr = keyPtr + 2;
      if (*(uint *)(thisPtr + 0x88) <= index) {
        return value;
      }
    }
    // +0x88: count of entries
    // +0x8: array of key-value pairs (key at +0, value at +4)
    // Each entry is 8 bytes: 4 for key, 4 for value
    value = *(undefined4 *)(thisPtr + 0xc + index * 8);
  }
  return value;
}