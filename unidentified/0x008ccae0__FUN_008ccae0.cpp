// FUNC_NAME: SomeClass::initFromDataList
undefined4 * __thiscall SomeClass::initFromDataList(undefined4 *this, int dataList, undefined4 extraParam)
{
  uint index;
  int singletonResult;
  undefined4 foundData;
  int *currentPtr;
  
  // Call base class initializer
  FUN_00416a70(dataList, extraParam);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d7c610;
  
  // Initialize member at offset +0x70 (this[0x1c]) to 7
  this[0x1c] = 7;
  
  index = 0;
  
  // Check if dataList has any entries (count at +0x20)
  if (*(ushort *)(dataList + 0x20) != 0) {
    currentPtr = *(int **)(dataList + 0x1c); // pointer to array of pointers
    
    // Search for an entry with a specific hash (0x9DB0F806)
    while (((undefined4 *)*currentPtr)[4] != -0x624f07fa) {
      index = index + 1;
      currentPtr = currentPtr + 1;
      
      // If we've exhausted the list, return early
      if (*(ushort *)(dataList + 0x20) <= index) {
        return this;
      }
    }
    
    // Found the entry, store its pointer at offset +0x70 (this[0x1c])
    this[0x1c] = *(undefined4 *)*currentPtr;
    
    // Attempt to get a singleton/manager object by hash 0xb6495298
    singletonResult = FUN_004a3790(0xb6495298);
    if (singletonResult == 0) {
      // Get something from the found entry and register it
      foundData = thunk_FUN_0042a990(this[0x1c]);
      FUN_00417280(foundData);
    }
  }
  
  return this;
}