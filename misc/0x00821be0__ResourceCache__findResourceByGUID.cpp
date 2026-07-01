// FUNC_NAME: ResourceCache::findResourceByGUID
int __thiscall ResourceCache::findResourceByGUID(int thisPtr, int *guidPtr)
{
  uint index;
  int *resourcePtr;
  int resource;
  
  index = 0;
  // +0xC: count of resources in cache
  if (*(uint *)(thisPtr + 0xc) != 0) {
    // +0x8: pointer to array of resource pointers
    resourcePtr = *(int **)(thisPtr + 8);
    do {
      resource = *resourcePtr;
      // Compare the 128-bit GUID (4 ints at +0x1C, +0x20, +0x24, +0x28)
      if ((((*(int *)(resource + 0x1c) == *guidPtr) && 
            (*(int *)(resource + 0x20) == guidPtr[1])) &&
           (*(int *)(resource + 0x24) == guidPtr[2])) && 
          (*(int *)(resource + 0x28) == guidPtr[3])) {
        return resource;
      }
      index = index + 1;
      resourcePtr = resourcePtr + 1;
    } while (index < *(uint *)(thisPtr + 0xc));
  }
  return 0;
}