// FUNC_NAME: EntityDataManager::findByID
int __thiscall EntityDataManager::findByID(int thisPtr, int entityID)
{
  int result = 0;
  uint index = 0;
  
  if (*(uint *)(thisPtr + 0xd0) != 0) { // count of entities
    int *arrayPtr = (int *)(*(int *)(thisPtr + 0xcc) + 8); // start of ID fields (offset +8 in each 0x10-byte entry)
    while (*arrayPtr != entityID) {
      index = index + 1;
      arrayPtr = arrayPtr + 4; // advance to next entry's ID (4 ints per entry, each 4 bytes)
      if (*(uint *)(thisPtr + 0xd0) <= index) {
        return result; // not found
      }
    }
    result = index * 0x10 + *(int *)(thisPtr + 0xcc); // base + index * entrySize
  }
  return result;
}