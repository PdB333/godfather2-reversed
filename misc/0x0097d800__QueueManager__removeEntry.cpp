// FUNC_NAME: QueueManager::removeEntry
void __thiscall QueueManager::removeEntry(int this, int entryPtr)
{
  int iVar1;
  int *currentEntry;
  int iVar3;
  undefined8 *destPtr;
  uint index;
  
  index = 0;
  if (*(uint *)(this + 0xd0) != 0) { // +0xD0: entryCount
    currentEntry = (int *)(*(int *)(this + 0xcc) + 0xc); // +0xCC: entryDataBase, skip 3 ints to data field
    while (*currentEntry != entryPtr) { // compare data pointer
      index = index + 1;
      currentEntry = currentEntry + 4; // each entry is 0x10 bytes, 4 ints
      if (*(uint *)(this + 0xd0) <= index) {
        return;
      }
    }
    if (-1 < (int)index) {
      // Remove entry at index, call destructor
      FUN_0097c1e0(*(int *)(this + 0xcc) + index * 0x10);
      if (index != *(int *)(this + 0xd0) - 1U) {
        // Shift last entry into the empty slot
        iVar1 = *(int *)(this + 0xcc);
        iVar3 = *(int *)(this + 0xd0) * 0x10;
        destPtr = (undefined8 *)(iVar1 + index * 0x10);
        *destPtr = *(undefined8 *)(iVar3 + -0x10 + iVar1); // copy 16 bytes
        destPtr[1] = *(undefined8 *)(iVar3 + iVar1 + -8);
      }
      *(int *)(this + 0xd0) = *(int *)(this + 0xd0) + -1; // decrement count
    }
  }
  return;
}