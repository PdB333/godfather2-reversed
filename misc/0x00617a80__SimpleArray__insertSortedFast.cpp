// FUNC_NAME: SimpleArray::insertSortedFast
// This appears to be a helper function that inserts an 8-byte element into a sorted array (likely a simple map/array of key-value pairs or pointers).
// The array is stored as: [0] = pointer to data buffer, [1] = current count, [2] = capacity.
// The element at +0x-8 is the last element before insertion point, and at +0x0 is the first element after insertion point (shift).
int FUN_00617a80(void)
{
  undefined4 *puVar1;
  uint uVar2;
  int *thisIdx; // in EAX -> this, assuming __thiscall with this as array descriptor
  int iVar3;
  uint insertPos; // unaff_EDI

  iVar3 = thisIdx[2]; // +0x08: capacity
  
  // Check if we need to grow the array
  if (thisIdx[1] == iVar3) { // +0x04: current size == capacity
    // If size is 0, set new capacity to 1, else double it
    if (iVar3 == 0) {
      iVar3 = 1;
    }
    else {
      iVar3 = iVar3 * 2;
    }
    // Reallocate the buffer to new capacity (each element is 8 bytes)
    FUN_00617d50(iVar3); // likely resizeBuffer(newCapacity)
  }
  
  uVar2 = thisIdx[1]; // +0x04: current size
  
  // Check if insert position (unaff_EDI) is not at the end
  if (insertPos != uVar2) {
    // Move elements one slot to the right starting from the end
    puVar1 = (undefined4 *)(*thisIdx + uVar2 * 8); // point to last element in buffer
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = puVar1[-2]; // copy key part (first 4 bytes)
      puVar1[1] = puVar1[-1]; // copy value part (next 4 bytes)
    }
    uVar2 = thisIdx[1]; // size
    // Shift elements from one before the last back to insertPos
    while (uVar2 = uVar2 - 1, insertPos < uVar2) {
      puVar1 = (undefined4 *)(*thisIdx + uVar2 * 8);
      *puVar1 = *(undefined4 *)(*thisIdx + -8 + uVar2 * 8); // copy from (index - 1)
      puVar1[1] = puVar1[-1];
    }
    // Update size and return pointer to the insertion slot
    thisIdx[1] = thisIdx[1] + 1; // size++
    return *thisIdx + insertPos * 8; // pointer to empty slot at insertPos
  }
  
  // Inserting at the end (simple append)
  thisIdx[1] = uVar2 + 1; // size++
  return *thisIdx + uVar2 * 8; // pointer to new last slot
}