// FUNC_NAME: ObjectPool::releaseObject

void __thiscall ObjectPool::releaseObject(int this, void* obj)
{
    // this+0x4c: pointer to head of allocated slot list (doubly linked list of PoolSlot)
    // Each PoolSlot: +0 next, +4 prev, +8 object pointer
    PoolSlot* slot = *(PoolSlot**)(*(int*)(this + 0x4c));
    PoolSlot* listHead = *(PoolSlot**)(this + 0x4c);

    if (obj == nullptr)
        return;

    // Find the slot that contains this object
    while (slot != listHead)
    {
        if (slot == listHead)
        {
            assertFail(); // circular list or invalid state
        }
        if (slot->objectPtr == obj)
        {
            // Remove the slot from the allocated list (this+0x34 is some list head?)
            removeSlotFromList(localBuffer, this + 0x34, slot);
            break;
        }
        if (slot == listHead)
        {
            assertFail();
        }
        slot = slot->next;
    }

    // Call the object's destructor (first virtual function)
    (*(void(**)(int))obj)(0);

    // Global memory manager at EBX (unaff_EBX)
    // unaff_EBX+0x2c: pointer to free list header (FreeListHeader)
    FreeListHeader* freeListHeader = *(FreeListHeader**)(gMemoryManager + 0x2c);
    void* firstFree = freeListHeader->firstFree;

    if (firstFree != nullptr)
    {
        // Check if obj is within the memory block managed by this free list
        // freeListHeader->allocator (offset 0x1c) is a pointer to a memory allocator
        if (freeListHeader->allocator != nullptr &&
            (obj < firstFree || (void*)((uint8_t*)firstFree + freeListHeader->blockSize) <= obj))
        {
            // obj is outside the block, use the allocator's deallocate function (vtable+8)
            (*(void(**)(void*))freeListHeader->allocator->vtable[2])(obj);
            return;
        }
        // Insert obj into the free list (singly linked)
        *(void**)obj = freeListHeader->nextFree; // obj->next = old next
        freeListHeader->freeCount++;
        freeListHeader->nextFree = obj;
    }
}