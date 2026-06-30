// FUNC_NAME: FreeListedObject::~FreeListedObject
// Destructor that removes the object from a global free list and optionally deallocates memory.
// The object stores a linked-list node pointer at offset 0x10 and a secondary pointer at 0x14.
// Global pool buffer write pointer is at (DAT_01206880 + 0x14).
// Sentinel value PTR_LAB_01123be8 marks the end of the free list.
undefined4* __thiscall FreeListedObject::~FreeListedObject(FreeListedObject* this, byte deallocateFlag)
{
    // Safeguard: set vtable to base class vtable during destruction
    this->vtable = &VTable_BaseClass_00e37110;

    // Retrieve the internal node pointer (offset +0x10)
    void* listNode = this->nodePointer;
    if (listNode != nullptr) {
        // Global free-list write pointer (pointer to current insertion point in buffer)
        int** writePtr = (int**)(DAT_01206880 + 0x14);

        // Write sentinel as the "next" of the new entry
        *(*writePtr) = (int)&PTR_LAB_01123be8;
        // Advance to the object pointer slot
        (*writePtr)++;
        // Store the node pointer
        *(*writePtr) = (int)listNode;
        // Advance to the next slot
        (*writePtr)++;

        // Clear internal pointers (offsets +0x10 and +0x14)
        this->nodePointer = nullptr;
        this->overflowPointer = nullptr;
    }

    // If requested, deallocate the object itself (likely operator delete)
    if ((deallocateFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}