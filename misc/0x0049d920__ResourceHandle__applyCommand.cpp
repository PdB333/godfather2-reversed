// FUNC_NAME: ResourceHandle::applyCommand
void __thiscall ResourceHandle::applyCommand(int cmd, int *callbackObj)
{
  int commandType;
  uint handleIndex;
  int *resourceEntry;
  char continueFlag;
  size_t dataSize;
  
  commandType = *(int *)(cmd + 4); // +0x04: command identifier
  if (commandType == 0) {
    // Command 0: Set handle to a new source (direct copy of source index)
    *(undefined4 *)(this + 0x10) = *(undefined4 *)(cmd + 8); // +0x10: resource handle/index
  }
  else if (commandType == 5) {
    // Command 5: Release current handle (decrement ref count)
    handleIndex = *(uint *)(this + 0x10);
    if (handleIndex != 0) {
      if (((handleIndex != 0xffffffff) && (handleIndex < 0x1000)) &&
         ((handleIndex * 0x38 != -0x11a0f28) &&
          (resourceEntry = *(int **)(&gResourceTable + handleIndex * 0x38),
           resourceEntry != (int *)0x0))) {
        if (*resourceEntry == 1) {
          if (resourceEntry[2] == 3) {
            freeResource(resourceEntry[1], 0); // +0x04: data pointer, flags=0
            *(undefined4 *)(this + 0x10) = 0;
            notifyResourceChanged();
          }
          else {
            *resourceEntry = 2; // set refCount to 2? (common pattern: 1->2 for persistent)
            *(undefined4 *)(this + 0x10) = 0;
            notifyResourceChanged();
          }
          goto LAB_0049daa8;
        }
        *resourceEntry = *resourceEntry - 1; // decrement refCount
      }
      *(undefined4 *)(this + 0x10) = 0;
    }
    notifyResourceChanged();
  }
  else if (commandType == 6) {
    // Command 6: Replace handle with new (decrement old, increment new)
    handleIndex = *(uint *)(this + 0x10);
    if (handleIndex != 0) {
      if (((handleIndex != 0xffffffff) && (handleIndex < 0x1000)) &&
         ((handleIndex * 0x38 != -0x11a0f28 &&
          (resourceEntry = *(int **)(&gResourceTable + handleIndex * 0x38),
           resourceEntry != (int *)0x0)))) {
        if (*resourceEntry == 1) {
          if (resourceEntry[2] == 3) {
            freeResource(resourceEntry[1], 0);
          }
          else {
            *resourceEntry = 2;
          }
        }
        else {
          *resourceEntry = *resourceEntry - 1;
        }
      }
      *(undefined4 *)(this + 0x10) = 0;
    }
    handleIndex = *(uint *)(cmd + 8); // +0x08: new handle index
    *(uint *)(this + 0x10) = handleIndex;
    if (((handleIndex != 0xffffffff) && (handleIndex < 0x1000)) &&
       ((handleIndex * 0x38 != -0x11a0f28 &&
        (resourceEntry = *(int **)(&gResourceTable + handleIndex * 0x38),
         resourceEntry != (int *)0x0)))) {
      *resourceEntry = *resourceEntry + 1; // increment new refCount
    }
  }
  else {
    // Other commands: copy raw data from command into handle buffer
    dataSize = getDefaultResourceSize(); // size of resource data block
    memset(*(void **)(this + 0x10), 0, dataSize); // +0x10: pointer to resource data buffer
    dataSize = getResourceSizeForType(*(undefined4 *)(cmd + 4)); // size based on command type
    memcpy(*(void **)(this + 0x10), (void *)(cmd + 8), dataSize); // copy from command payload
  }
LAB_0049daa8:
  if (callbackObj != (int *)0x0) {
    continueFlag = (**(code **)(*callbackObj + 0x2c))(); // +0x2c: virtual callback method
    if (continueFlag != '\0') {
      (**(code **)(*callbackObj + 0x28))(); // +0x28: another virtual callback method
    }
  }
  return;
}