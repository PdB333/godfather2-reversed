// FUNC_NAME: MemoryTracker::allocateBlock
void __thiscall MemoryTracker::allocateBlock(uint32_t blockSize)
{
    AllocationNode *newNode;
    uint32_t allocResult[3] = {0, 0, 0}; // local_c, local_8, local_4
    if (blockSize == 0) {
        return;
    }
    // Call internal allocator (first vtable function) to get a 0x10-byte node
    newNode = (AllocationNode *)(this->vtable->allocate)(0x10, &allocResult);
    newNode->field0 = allocResult[0];        // +0x00: some flag (0)
    newNode->blockSize = blockSize;          // +0x04: size of original allocation
    *(uint8_t *)(&newNode->byteField) = 0;   // +0x08: byte field set to 0
    newNode->prevNode = this->head;          // +0x0C: link to previous head
    this->totalAllocatedSize += blockSize;   // +0x0C: increment total size
    this->head = newNode;                    // +0x14: update head to new node
    this->initializedFlag = 1;               // +0x04: mark as initialized
    return;
}