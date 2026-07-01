// FUNC_NAME: GenericList::addItem
void __thiscall GenericList::addItem(int this, int item)
{
  int *listData;
  int currentSize;
  int *targetList;
  
  // Select which list array to use based on item type at offset +0x58
  switch(*(undefined4 *)(item + 0x58)) {
  default:
    targetList = (int *)(this + 4);    // +0x04: default list
    break;
  case 2:
    targetList = (int *)(this + 0x10); // +0x10: type 2 list
    break;
  case 3:
    targetList = (int *)(this + 0x1c); // +0x1c: type 3 list
    break;
  case 4:
    targetList = (int *)(this + 0x28); // +0x28: type 4 list
  }
  
  // targetList layout: [0] = data pointer, [1] = count, [2] = capacity
  currentSize = targetList[2]; // capacity
  if (targetList[1] == currentSize) {
    // Need to grow the list
    if (currentSize == 0) {
      currentSize = 1;
    }
    else {
      currentSize = currentSize * 2; // Double capacity
    }
    FUN_0077b420(currentSize); // resizeList(currentSize)
  }
  
  // Add item to end of list
  listData = (int *)(*targetList + targetList[1] * 4);
  targetList[1] = targetList[1] + 1; // increment count
  if (listData != (int *)0x0) {
    *listData = item;
  }
  return;
}