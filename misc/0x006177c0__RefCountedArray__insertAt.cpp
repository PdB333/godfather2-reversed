// FUNC_NAME: RefCountedArray::insertAt
int RefCountedArray::insertAt(int *this, uint index)
{
  int oldCount = this[1]; // count
  int capacity = this[2]; // capacity
  
  // Grow if needed
  if (oldCount == capacity) {
    if (capacity == 0) {
      capacity = 1;
    } else {
      capacity *= 2;
    }
    resizeArray(this, capacity); // FUN_00617ba0
  }
  
  // Calculate pointer to the end (new slot if appending)
  uint *endSlot = (uint *)(this[0] + oldCount * 8);
  
  if (index != oldCount) {
    // Inserting not at end: shift elements right and clear old slot
    if (endSlot != (uint *)0x0) {
      // Copy the last element to the new end position (preserve it during shift)
      *endSlot = *(endSlot - 2); // copy first word from last element
      endSlot[1] = 0;            // clear second word (ref count will be handled later)
      initObject(endSlot + 1);   // FUN_006164e0 (construct or zero-initialize?)
    }
    
    // Shift elements from the insertion point to the right, one by one
    uint srcIndex = oldCount;
    while (srcIndex = srcIndex - 1, index < srcIndex) {
      uint *destSlot = (uint *)(this[0] + srcIndex * 8);
      // Copy the first word from the left neighbor
      *destSlot = *(destSlot - 2);
      
      // Update reference counting on the second word (object pointer)
      int newRefObj = *(destSlot - 1); // second word of left neighbor
      int oldRefObj = destSlot[1];      // current second word
      
      if (oldRefObj != newRefObj) {
        // Release old reference
        if (oldRefObj != 0) {
          *(short *)(oldRefObj + 8) -= 1;
          if (*(short *)(oldRefObj + 8) == 0) {
            releaseObject(oldRefObj); // FUN_00616dc0
            (**(code **)(*g_vtablePtr + 4))(oldRefObj, 0); // destructor call
          }
          destSlot[1] = 0;
        }
        // Acquire new reference
        if (newRefObj != 0) {
          *(short *)(newRefObj + 8) += 1;
          destSlot[1] = newRefObj;
        }
      }
    }
    
    // Clear the insertion slot (decrement ref count on the object that was there)
    int base = this[0];
    this[1] = oldCount + 1; // increment count
    uint *insertSlot = (uint *)(base + index * 8);
    int oldObj = insertSlot[1]; // second word (object pointer)
    if (oldObj != 0) {
      *(short *)(oldObj + 8) -= 1;
      if (*(short *)(oldObj + 8) == 0) {
        releaseObject(oldObj);
        (**(code **)(*g_vtablePtr + 4))(oldObj, 0);
      }
      insertSlot[1] = 0;
    }
    // Ensure second word is zero (safety)
    if (base + index * 8 != 0) {
      insertSlot[1] = 0;
    }
    return insertSlot; // return pointer to the first word of the new slot
  } else {
    // Appending at end: just clear the second word and return the slot
    if (endSlot != (uint *)0x0) {
      endSlot[1] = 0;
    }
    this[1] = oldCount + 1;
    return (uint *)(this[0] + oldCount * 8);
  }
}