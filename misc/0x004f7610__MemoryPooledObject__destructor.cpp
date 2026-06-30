// FUNC_NAME: MemoryPooledObject::destructor
// Function address: 0x004f7610
// Role: Destructor for a memory-pooled object. Removes a child node from a global pool stack, then optionally deallocates this object.

undefined4 * __thiscall MemoryPooledObject::destructor(MemoryPooledObject *this, byte flags)
{
  int *poolStackPtr;
  int *childNode;

  // Set vtable to a special destructor vtable to prevent virtual calls during destruction
  this->vtable = &s_destructorVtable;

  // Check if there is a child node at offset +0x10
  childNode = this->m_pChildNode; // +0x10
  if (childNode != (int *)0x0) {
    // Get the global pool stack pointer (DAT_01206880 + 0x14)
    poolStackPtr = (int *)(g_poolStackBase + 0x14); // global pool stack pointer

    // Push the child node onto the pool stack
    // The pool stack is a simple stack: *poolStackPtr points to the next free slot
    *(undefined3 **)*poolStackPtr = &s_poolNodeSentinel; // write a sentinel/label
    *poolStackPtr = *poolStackPtr + 4; // advance stack pointer
    *(int *)*poolStackPtr = childNode; // store the child node pointer
    *poolStackPtr = *poolStackPtr + 4; // advance stack pointer again

    // Clear the child node pointers in this object
    this->m_pChildNode = (int *)0x0; // +0x10
    this->m_pChildNodeNext = (int *)0x0; // +0x14 (assumed)
  }

  // If the flags indicate deletion, call the deallocator
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete or custom deallocator
  }

  return this;
}