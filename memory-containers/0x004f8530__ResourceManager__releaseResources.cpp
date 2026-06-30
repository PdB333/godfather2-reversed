// FUNC_NAME: ResourceManager::releaseResources
void ResourceManager::releaseResources(int *resourceList)
{
  int *currentResource;
  int resourceIndex;
  int resourceCount;
  int *resourceEntry;
  uint index;
  int fsOffset;
  
  index = 0;
  currentResource = resourceList;
  if (resourceList[4] != 0) {
    do {
      resourceIndex = currentResource[2];  // +0x08: resource handle/index
      if (resourceIndex != 0) {
        resourceCount = **(int **)(fsOffset + 0x2c);  // FS segment offset for thread-local storage
        resourceEntry = (int *)(*(int *)(resourceCount + 8) + 0x30 + resourceIndex);  // +0x30: resource reference count array
        *resourceEntry = *resourceEntry + -1;  // decrement reference count
        if (*(int *)(*(int *)(resourceCount + 8) + 0x30 + resourceIndex) == 0) {
          FUN_00519340(resourceIndex, currentResource[3]);  // release resource when ref count reaches 0
        }
      }
      index = index + 1;
      currentResource = currentResource + 2;  // each entry is 8 bytes (2 ints)
    } while (index < (uint)resourceList[4]);  // +0x10: number of resources in list
  }
  return;
}