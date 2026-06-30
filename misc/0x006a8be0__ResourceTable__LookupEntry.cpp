// FUNC_NAME: ResourceTable::LookupEntry
uint __thiscall ResourceTable::LookupEntry(int thisPtr, uint key, int *outPtr, uint *outSizeOrFlags)
{
  *outPtr = 0;
  *outSizeOrFlags = 0;
  uint result = key & 0xffffff00; // default: key with low byte cleared
  uint index = 0;
  uint *array = (uint *)(thisPtr + 0x10);
  if (*(uint *)(thisPtr + 0xc) != 0) {
    while (array[0] != key) {
      index++;
      array += 3; // each entry is 12 bytes (3 uint: key, relativeOffset, extra)
      if (*(uint *)(thisPtr + 0xc) <= index) {
        return key & 0xffffff00; // not found, return key with LSB zeroed
      }
    }
    // Found entry at this index
    int relativeOffset = array[1]; // offset from thisPtr
    *outPtr = relativeOffset + thisPtr; // absolute pointer
    *outSizeOrFlags = array[2];
    // Build tagged pointer: high 24 bits are (absPtr >> 8), low byte = 1 (success indicator)
    result = ((uint)((relativeOffset + thisPtr) >> 8) << 8) | 1; // CONCAT31 equivalent
    // Actually CONCAT31((int3)(addr>>8),1) means (addr>>8) << 8 | 1
  }
  return result;
}