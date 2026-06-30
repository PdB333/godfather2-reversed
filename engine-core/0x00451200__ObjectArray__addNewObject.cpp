// FUNC_NAME: ObjectArray::addNewObject
// Function at 0x00451200: pushes a newly allocated object into the dynamic array, returns its index and the object pointer.
// The array stores 4-byte handles/pointers. Size and capacity stored at +0x14 and +0x18.
// Uses FUN_009c8e50 (allocator) to create object of size 0xbdc (3036 bytes), then constructs it via FUN_004512c0.
// If array is full, doubles capacity via FUN_00452780.

undefined4 __thiscall ObjectArray::addNewObject(uint this, int *outIndex)
{
  undefined4 newObject; // pointer/handle to the newly created object
  undefined4 *arraySlot; // slot in the internal array
  int currentSize; // number of elements stored (+0x14)
  int capacity;   // capacity of the array (+0x18)

  // Attempt to allocate and construct a new object (size 0xbdc)
  int allocResult = FUN_009c8e50(0xbdc); // allocate memory
  if (allocResult == 0) {
    newObject = 0;
  } else {
    newObject = FUN_004512c0(); // construct object at allocated memory
  }

  // Check if array needs to grow
  currentSize = *(int *)(this + 0x14);
  capacity = *(int *)(this + 0x18);
  if (currentSize == capacity) {
    int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
    FUN_00452780(newCapacity); // resize internal array
  }

  // Store new object in the array at the current end
  arraySlot = (undefined4 *)(*(int *)(this + 0x10) + currentSize * 4);
  *(int *)(this + 0x14) = currentSize + 1; // increment size
  if (arraySlot != (undefined4 *)0x0) {
    *arraySlot = newObject;
  }

  // Output the index of the newly added element
  *outIndex = *(int *)(this + 0x14) - 1;
  return newObject;
}