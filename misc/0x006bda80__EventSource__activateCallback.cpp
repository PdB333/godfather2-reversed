// FUNC_NAME: EventSource::activateCallback
void __thiscall EventSource::activateCallback(int thisPtr, int listenerObj)
{
  undefined4 newHandle;
  undefined **callbackListEntryPtr;
  int nodePtr;
  undefined4 nextPtr;
  undefined4 local_c;
  undefined ***local_8;
  undefined1 local_4;

  // If an existing handle is present, release it
  if (*(int *)(thisPtr + 0xd0) != 0) {
    FUN_00791350(thisPtr + 0x50);  // Release/reference decrement
    *(undefined4 *)(thisPtr + 0xd0) = 0;
  }
  
  // Create a new event source handle
  newHandle = FUN_007351c0();  // Create new event source object
  *(undefined4 *)(thisPtr + 0xd0) = newHandle;
  
  // Acquire reference to the event source
  FUN_00791e70(thisPtr + 0x50);  // Acquire/reference increment
  *(uint *)(thisPtr + 0x54) |= 0x10000;  // Set "active" flag
  
  // If there is a callback list head, update it
  if (*(int *)(thisPtr + 0x80) != 0) {
    callbackListEntryPtr = &PTR_FUN_00e31e2c;  // vtable or static function pointer
    
    if (listenerObj == 0) {
      nodePtr = 0;
    }
    else {
      nodePtr = listenerObj + 0x48;  // Offset to node inside listener object
    }
    
    nextPtr = 0;
    if (nodePtr != 0) {
      nextPtr = *(undefined4 *)(nodePtr + 4);  // Save original next pointer
      *(int **)(nodePtr + 4) = &nodePtr;  // Link node to itself (circular insertion)
    }
    
    local_c = *(undefined4 *)(thisPtr + 0x80);  // List head
    local_8 = &callbackListEntryPtr;
    local_4 = 0;
    FUN_00408a00(&local_c, 0);  // Add to callback list (likely iterates and registers)
    
    if (nodePtr != 0) {
      FUN_004daf90(&nodePtr);  // Cleanup node if added
    }
  }
  
  return;
}