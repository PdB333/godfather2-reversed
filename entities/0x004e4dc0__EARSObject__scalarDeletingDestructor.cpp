// FUNC_NAME: EARSObject::scalarDeletingDestructor

// Destructor for EARS base object. Manages a free list stored in global memory.
// field_0x10 (offset +0x10): pointer to next free node in linked list.
// field_0x14 (offset +0x14): unused pointer (cleared after removal).
// Global list head is at DAT_01206880 + 0x14 (globalFreeListHead).

void * __thiscall EARSObject::scalarDeletingDestructor(byte flags)
{
    // Set vtable pointer (usually base class vtable)
    this->vtable = (void **)&PTR_FUN_00e37110;

    int *nextFreeNode = this->field_0x10;
    if (nextFreeNode != 0)
    {
        // Access global free list header pointer
        int *freeListHead = (int *)(DAT_01206880 + 0x14);
        
        // Insert this object's free node link back into the global list.
        // The list is structured as: [sentinel pointer, next pointer] pairs.
        // We write a sentinel and then the old next pointer back.
        *(int **)freeListHead = (int *)&PTR_LAB_01123be8;  // +0x14: sentinel
        freeListHead++;                                      // +0x18: next slot
        *(int *)freeListHead = (int)nextFreeNode;           // +0x18: store old next pointer
        freeListHead++;                                      // advance beyond this pair
        
        // Clear the object's link fields
        this->field_0x10 = 0;
        this->field_0x14 = 0;
    }

    // If the scalar deletion flag (bit 0) is set, free the memory
    if ((flags & 1) != 0)
    {
        operatorDelete(this);
    }

    return this;
}