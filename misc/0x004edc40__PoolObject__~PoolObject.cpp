// FUNC_NAME: PoolObject::~PoolObject
void* __thiscall PoolObject::~PoolObject(void* this, byte freeMemoryFlag)
{
    // Set vtable to destructor vtable
    *(void**)this = (void*)&PTR_FUN_00e37110;

    // Retrieve pointer stored at +0x10 (e.g., a node handle or buffer pointer)
    int* nodePointer = *(int**)((char*)this + 0x10);
    if (nodePointer != 0) {
        // Global memory manager at DAT_01206880; offset +0x14 is a free-list cursor
        int* freeListCursor = (int*)(DAT_01206880 + 0x14);   // points to the next free slot

        // Write a sentinel tag into the first 4 bytes of the slot
        *(void**)(*freeListCursor) = (void*)&PTR_LAB_01123be8;
        // Advance cursor by one slot (4 bytes for the tag)
        *freeListCursor += 4;
        // Write the node pointer into the data portion of the slot
        *(int*)(*freeListCursor) = (int)nodePointer;
        // Advance cursor past the data
        *freeListCursor += 4;

        // Clear the node pointer and adjacent field (+0x14)
        *(int**)((char*)this + 0x10) = 0;
        *(int**)((char*)this + 0x14) = 0;
    }

    // If bit 0 of freeMemoryFlag is set, actually deallocate the object
    if ((freeMemoryFlag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}