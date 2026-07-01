// FUNC_NAME: SomeLinkedListOrResourceManager::setActiveItem
undefined4 __thiscall FUN_008cff70(int *this, int item, undefined4 *outParam)
{
  int *ppCurrentItem;
  undefined4 result;
  
  ppCurrentItem = this + 0x16; // +0x58: pointer to current active item (linked list node pointer)
  if (item == 0) {
    item = 0;
  }
  else {
    item = item + 0x48; // item + 0x48: offsets to get some internal structure field
  }
  if (*ppCurrentItem != item) {
    if (*ppCurrentItem != 0) {
      FUN_004daf90(ppCurrentItem); // likely removeFromList or decrementRefCount
    }
    *ppCurrentItem = item;
    if (item != 0) {
      this[0x17] = *(int *)(item + 4); // +0x5C: store next pointer from the node
      *(int **)(item + 4) = ppCurrentItem; // fix doubly linked list back pointer
    }
  }
  if (outParam != (undefined4 *)0x0) {
    *outParam = 0;
  }
  if (((uint)this[0x18] >> 0x1c & 1) == 0) { // test bit 28 of flags at +0x60
    result = (**(code **)(*this + 0x1c))(outParam); // virtual call at vtable+0x1c
    return result;
  }
  return 0x10; // return error code 0x10 if bit set
}