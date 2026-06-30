// FUNC_NAME: CallbackManager::flushPendingCallbacks
void CallbackManager::flushPendingCallbacks(int *pQueueHandle)
{
  int iVar3;
  int iVar4;
  
  // Save this pointer for later vtable dispatch
  int thisPtr = (int)this;
  
  // Dereference the queue handle to obtain the queue structure
  int *queueStruct = (int *)*pQueueHandle;
  
  // Likely acquire lock / begin processing (sets up local state)
  FUN_0065dda0(&queueStruct);
  
  // Get pointer to circular buffer structure from queue struct
  // queueStruct layout: [0] base pointer, [1] max size, [2] head index, [3] count
  int *circularBuffer = *(int **)((int)&queueStruct + 4); // offset +4 in local state
  
  iVar3 = circularBuffer[3];  // count of pending items
  
  while (iVar3 != 0) {
    // Compute address of current head item (each item is 2 uint32s = 8 bytes)
    undefined4 *item = (undefined4 *)(circularBuffer[0] + circularBuffer[2] * 8);
    
    // Call the callback function from the owner's vtable at offset 4
    // Owner at thisPtr, vtable pointer at +0x8, function pointer at vtable+4
    int vtable = *(int *)(thisPtr + 8);
    (**(code **)(vtable + 4))(item[0], item[1]);
    
    // Move head pointer forward (circular buffer wrap)
    int newHead = circularBuffer[2] + 1;
    if (newHead >= circularBuffer[1]) {
      newHead = 0;
    }
    circularBuffer[2] = newHead;
    
    // Decrement count
    iVar3 += -1;
    circularBuffer[3] = iVar3;
  }
  
  // Free the data buffer if it exists
  if (circularBuffer[0] != 0) {
    FUN_009c8f10(circularBuffer[0]);  // operator delete[]
  }
  
  // Free the circular buffer structure itself
  FUN_009c8eb0(circularBuffer);  // operator delete
  
  // Clean up the queue handle (likely release lock or nullify)
  undefined4 *handlePtr = (undefined4 *)*pQueueHandle;
  FUN_0065db70(&handlePtr);
  
  return;
}