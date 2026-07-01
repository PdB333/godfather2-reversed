// FUNC_NAME: GenericObjectPool::addReference
void __thiscall GenericObjectPool::addReference(int thisPtr, int objPtr)
{
  undefined4 *slot;
  int *pSlotData;
  int newCapacity;
  
  // Check if we need to grow the pool (current count >= capacity)
  if (*(uint *)(thisPtr + 0x60) < *(uint *)(thisPtr + 0x58)) {
    // Call to expand the pool storage
    GenericObjectPool::grow();
  }
  
  newCapacity = *(int *)(thisPtr + 0x5c);
  
  // If current size == capacity, double the capacity
  if (*(int *)(thisPtr + 0x58) == newCapacity) {
    if (newCapacity == 0) {
      newCapacity = 1;
    }
    else {
      newCapacity = newCapacity * 2;
    }
    GenericObjectPool::reserve(newCapacity);
  }
  
  // Get pointer to the next slot (each slot is 8 bytes: pointer + next link)
  slot = (undefined4 *)(*(int *)(thisPtr + 0x54) + *(int *)(thisPtr + 0x58) * 8);
  
  if (slot != (undefined4 *)0x0) {
    *slot = 0;
    slot[1] = 0;
  }
  
  // Get pointer to the slot data again
  pSlotData = (int *)(*(int *)(thisPtr + 0x54) + *(int *)(thisPtr + 0x58) * 8);
  
  // Increment current size
  *(int *)(thisPtr + 0x58) = *(int *)(thisPtr + 0x58) + 1;
  
  // Offset the object pointer by 0x48 if non-null (this is the linked list node offset within the object)
  if (objPtr == 0) {
    objPtr = 0;
  }
  else {
    objPtr = objPtr + 0x48;
  }
  
  // If slot's object reference doesn't match, update it
  if (*pSlotData != objPtr) {
    if (*pSlotData != 0) {
      // Remove old reference from linked list
      GenericObjectPool::removeNode(pSlotData);
    }
    *pSlotData = objPtr;
    
    if (objPtr != 0) {
      // Insert into linked list: slot->next = objPtr->next; objPtr->next = slot
      pSlotData[1] = *(int *)(objPtr + 4);
      *(int **)(objPtr + 4) = pSlotData;
    }
  }
  
  // Increment total reference count
  *(int *)(thisPtr + 0x60) = *(int *)(thisPtr + 0x60) + 1;
  
  return;
}