// FUNC_NAME: SomeClass::findActiveItemById
undefined4 __fastcall SomeClass::findActiveItemById(int thisPtr)
{
  int itemCount;
  int currentIndex;
  undefined4 itemId;
  char isActive;
  
  itemCount = *(int *)(thisPtr + 0x1a8) - 1;  // +0x1a8: number of items in array
  if (itemCount < 0) {
    return 0;
  }
  do {
    itemId = *(undefined4 *)(*(int *)(thisPtr + 0x1a4) + itemCount * 4);  // +0x1a4: pointer to array of item IDs
    isActive = FUN_008c8350();  // Check if item is active/valid
    if (isActive != '\0') {
      return itemId;
    }
    itemCount = itemCount - 1;
  } while (-1 < itemCount);
  return 0;
}