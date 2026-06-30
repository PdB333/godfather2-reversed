// FUNC_NAME: MapGeneric::findValueByKey
undefined4 __thiscall MapGeneric::findValueByKey(int this, int key)
{
  undefined4 value;
  uint index;
  int *keyPtr;
  
  value = 0;
  index = 0;
  // +0x88: count of entries in the map
  if (*(uint *)(this + 0x88) != 0) {
    // +0x0c: pointer to array of {key, value} pairs (each pair is 8 bytes: key at offset 0, value at offset 4)
    keyPtr = (int *)(this + 0xc);
    while (*keyPtr != key) {
      index = index + 1;
      keyPtr = keyPtr + 2;
      // +0x88: count of entries in the map
      if (*(uint *)(this + 0x88) <= index) {
        return value; // key not found, return default 0
      }
    }
    // Found key at index, return the value at offset +0x08 + (index * 8)
    value = *(undefined4 *)(this + 8 + index * 8);
  }
  return value;
}