// FUNC_NAME: MemoryBlock::~MemoryBlock

// Destructor for a memory block allocated from a global fixed-size pool.
// Frees internal buffer and optionally deletes the object itself.
MemoryBlock * __thiscall MemoryBlock::~MemoryBlock(MemoryBlock *this, byte flags)
{
  // Set vtable pointer (likely to base class or sentinel)
  this->vtable = &VTABLE_MemoryBlock; // +0x0

  // Check if buffer (offset +0x10) is allocated
  if (this->buffer != 0) // +0x10
  {
    // Get pointer to free list insertion point in global pool manager
    // g_pMemoryPool is a global byte array (e.g., pooled heap)
    int *pInsertSlot = (int *)(g_pMemoryPool + 0x14);

    // Write sentinel marker (PTR_LAB_01123be8) to current slot
    *(void **)*pInsertSlot = &FREE_LIST_SENTINEL;

    // Advance insertion pointer by 4 bytes
    *pInsertSlot = *pInsertSlot + 4;

    // Write the freed buffer address to next slot
    *(int *)*pInsertSlot = this->buffer; // +0x10

    // Advance insertion pointer again
    *pInsertSlot = *pInsertSlot + 4;

    // Clear buffer and size fields
    this->buffer = 0; // +0x10
    this->bufferSize = 0; // +0x14
  }

  // If flags & 1 (normal destructor call with delete), free the object itself
  if ((flags & 1) != 0) {
    operator delete(this);
  }

  return this;
}