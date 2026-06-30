// FUNC_NAME: BaseObject::~BaseObject
undefined4 * __thiscall BaseObject::~BaseObject(BaseObject *this, byte shouldDelete)
{
  int nodePtr;
  int *freeStackCursor;
  
  // Restore base class vtable (required when destructor is called from derived class)
  this->vtablePtr = &gBaseObjectVTable;
  
  nodePtr = this->nodeData; // offset +0x10 (this[4])
  if (nodePtr != 0) {
    // Push the node's data back onto the custom memory allocator's free stack
    freeStackCursor = (int *)(gMemoryPool + 0x14); // offset inside allocator = free stack pointer
    *(*freeStackCursor) = (int *)&gFreeListSentinel; // set sentinel at current stack position
    *freeStackCursor = *freeStackCursor + 4;        // advance stack pointer
    *(*freeStackCursor) = nodePtr;                  // store the node address
    *freeStackCursor = *freeStackCursor + 4;        // advance stack pointer
    this->nodeData = 0;    // clear the stored pointer
    this->extraData = 0;   // clear additional field (offset +0x14, this[5])
  }
  
  // If the destructor was called with the "delete" flag, deallocate the memory
  if ((shouldDelete & 1) != 0) {
    operatorDelete(this);
  }
  
  return this;
}