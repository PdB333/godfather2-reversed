// FUNC_NAME: ObjectListManager::initializeList
void __thiscall ObjectListManager::initializeList(int *listData)
{
  int *arrayBase;
  int itemIndex;
  int itemOffset;
  int *counterPtr;

  // Initialize various fields of the list data structure
  // Offsets are in int units (4 bytes each)
  FUN_004a9c90(this, listData + 5);   // +20 bytes
  FUN_004a9c90(this, listData + 8);   // +32 bytes
  FUN_004a9c90(this, listData + 0xe); // +56 bytes
  FUN_004a9c90(this, listData + 0xb); // +44 bytes
  FUN_004a9360(this, listData + 3);   // +12 bytes

  // Allocate a block of 0x20 bytes and store pointer via listData
  FUN_0064b9e0(0x20, &listData);

  // Initialize the allocated block (likely a sub-structure)
  counterPtr = listData;
  FUN_00856270(listData);

  if (counterPtr != (int *)0x0) {
    itemOffset = 0;
    do {
      // Process each item in the array (size 0x2c = 44 bytes)
      // *listData is the base pointer to the array
      FUN_008545b0(this, *listData + itemOffset);
      itemIndex = *listData + itemOffset;
      if (*(char *)(itemIndex + 0xd) != '\0') {
        // If byte at offset 0xd is set, call setup function
        FUN_00851dd0(itemIndex + 0x10, listData + 5, itemIndex);
      }
      itemOffset += 0x2c;
      counterPtr = (int *)((int)counterPtr - 1);
    } while (counterPtr != (int *)0x0);
  }
}