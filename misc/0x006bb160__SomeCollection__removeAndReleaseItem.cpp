// FUNC_NAME: SomeCollection::removeAndReleaseItem
int __thiscall SomeCollection::removeAndReleaseItem(int thisPtr, int index)
{
  int *itemPtr;
  int result;
  
  itemPtr = (int *)(*(int *)(thisPtr + 0xa0) + index * 0x18);
  if (*itemPtr == 0) {
    result = 0;
  }
  else {
    result = *itemPtr + -0x48; // Adjust pointer to object start (offset of -0x48)
    FUN_004daf90(itemPtr); // Call destructor or release function
    *itemPtr = 0; // Clear pointer in collection
  }
  *(uint *)(result + 0x5c) = *(uint *)(result + 0x5c) & 0xfbffffff; // Clear bit 25 of flags at +0x5c
  return result;
}