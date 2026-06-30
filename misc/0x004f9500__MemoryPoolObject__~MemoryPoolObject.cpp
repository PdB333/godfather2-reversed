// FUNC_NAME: MemoryPoolObject::~MemoryPoolObject
// Function: 0x004f9500 - Destructor for objects managed by a global free list
// Releases the object's memory block (if allocated) back to the free list,
// then optionally deallocates the object itself.
undefined4 * __thiscall MemoryPoolObject::~MemoryPoolObject(undefined4 *this, byte isDeleting)
{
  int allocatedBlock;
  int *freeListStackPtr;
  
  // Set vtable to base class (likely to prevent further virtual calls during destruction)
  *this = &PTR_FUN_00e37110;
  
  // Retrieve the allocated memory block pointer at offset +0x10
  allocatedBlock = this[4];
  if (allocatedBlock != 0) {
    // Access the free list stack pointer stored in a global structure at +0x14
    freeListStackPtr = (int *)(DAT_01206880 + 0x14);
    
    // Push a sentinel value (PTR_LAB_01123be8) onto the free list stack
    *(undefined ***)*freeListStackPtr = &PTR_LAB_01123be8;
    *freeListStackPtr = *freeListStackPtr + 4;
    
    // Push the actual block pointer onto the stack
    *(int *)*freeListStackPtr = allocatedBlock;
    *freeListStackPtr = *freeListStackPtr + 4;
    
    // Clear the block pointers in the object
    this[4] = 0;
    this[5] = 0;
  }
  
  // If the deleting flag is set (param_2 & 1), call operator delete
  if ((isDeleting & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}