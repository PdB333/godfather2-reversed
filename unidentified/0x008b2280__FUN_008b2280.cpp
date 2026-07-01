// FUNC_NAME: SomeManager::createOrAddItem
undefined4 * SomeManager::createOrAddItem(void)

{
  undefined4 *newItem;
  int managerPtr;
  int currentCount;
  int *listPtr;
  int newCapacity;
  
  newItem = (undefined4 *)FUN_009c8e50(0x20);
  if (newItem == (undefined4 *)0x0) {
    newItem = (undefined4 *)0x0;
  }
  else {
    FUN_004814b0(); // constructor call
    *newItem = &PTR_FUN_00d7ab88; // vtable pointer
    newItem[4] = 0; // +0x10
    newItem[5] = 0; // +0x14
    newItem[6] = 0; // +0x18
    newItem[7] = 0; // +0x1c
    FUN_00481530(); // post-constructor
  }
  managerPtr = DAT_0112988c; // global manager pointer
  currentCount = *(int *)(managerPtr + 0x18); // +0x18 = current count
  listPtr = (int *)(managerPtr + 0x10); // +0x10 = list pointer
  if (*(int *)(managerPtr + 0x14) == currentCount) { // +0x14 = capacity
    if (currentCount == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = currentCount * 2;
    }
    FUN_008b1a50(newCapacity); // resize list
  }
  currentCount = *(int *)(managerPtr + 0x14); // get updated count
  newItem = (undefined4 *)(*listPtr + currentCount * 4);
  *(int *)(managerPtr + 0x14) = currentCount + 1; // increment count
  if (newItem != (undefined4 *)0x0) {
    *newItem = newItem; // store pointer in list
  }
  return newItem;
}