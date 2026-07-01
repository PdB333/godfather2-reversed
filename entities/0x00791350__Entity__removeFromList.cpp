// FUNC_NAME: Entity::removeFromList
void __thiscall Entity::removeFromList(int this, int entityId)
{
  int *listData;
  uint count;
  uint index;
  uint foundIndex;
  int *listPtr;
  
  listData = *(int **)(this + 0xac); // +0xac: pointer to dynamic array (list of entity IDs)
  count = listData[1]; // +0x04: current count of elements in the array
  index = 0;
  foundIndex = 0xffffffff;
  
  if (count != 0) {
    listPtr = (int *)*listData; // dereference to get the actual array
    do {
      foundIndex = index;
      if (*listPtr == entityId) break;
      index = index + 1;
      listPtr = listPtr + 1;
      foundIndex = 0xffffffff;
    } while (index < count);
  }
  
  // Check if the list is locked (bit 0x19 of flags at +0x5c)
  if ((*(uint *)(this + 0x5c) >> 0x19 & 1) == 0) {
    // Not locked: perform actual removal
    if (-1 < (int)foundIndex) {
      if (foundIndex != count - 1) {
        // Shift last element into the removed slot
        *(undefined4 *)(*listData + foundIndex * 4) = *(undefined4 *)(*listData + -4 + count * 4);
      }
      listData[1] = listData[1] + -1; // decrement count
    }
    
    listData = *(int **)(this + 0xac);
    if (listData[1] == 0) {
      // List is now empty: free the array
      if (listData != (int *)0x0) {
        if (*listData != 0) {
          FUN_009c8f10(*listData); // free the array buffer
        }
        FUN_009c8eb0(listData); // free the list structure
      }
      *(undefined4 *)(this + 0xac) = 0; // clear the pointer
    }
  }
  else if (-1 < (int)foundIndex) {
    // Locked: just null out the slot (deferred removal)
    *(undefined4 *)(*listData + foundIndex * 4) = 0;
    return;
  }
  
  return;
}