// FUNC_NAME: MemoryPool::recycleObject
void __thiscall MemoryPool::recycleObject(void* this, SharedObject** objectPtr)
{
    int* refCountBlock; // +0x0C from object
    int* refCount;      // +0x04 within refCountBlock
    int otherPointer;   // +0x08 from object (possibly a list link)

    // Set vtable to a pooled/reset state
    *objectPtr = (SharedObject*)&PTR_FUN_00d8b42c;
    // Pre-cleanup static/global function
    FUN_004df600();

    // Decrease reference count in shared block (if present)
    refCountBlock = (int*)(*objectPtr)[3]; // object+0x0C is pointer to ref block
    refCount = refCountBlock + 1;          // ref count at block+0x04
    *refCount = *refCount - 1;
    if (*refCount == 0)
    {
        // Call destructor via vtable at block+0x00 (allocator? custom dealloc?)
        (**(code**)(*refCountBlock + 4))();
    }

    // Clear any secondary pointer (e.g., a linked list link)
    otherPointer = (int)(*objectPtr)[2]; // object+0x08
    if (otherPointer != 0)
    {
        *(undefined4*)(otherPointer + 8) = 0;
        (*objectPtr)[2] = 0;
    }

    // Remove from current list and insert into free list
    // Current head of free list is at this+0x34
    *objectPtr = *(SharedObject**)((char*)this + 0x34);
    *(int*)((char*)this + 0x10) = *(int*)((char*)this + 0x10) - 1; // decrease used count
    *(int*)((char*)this + 0x0C) = *(int*)((char*)this + 0x0C) + 1; // increase free count
    *(SharedObject***)((char*)this + 0x34) = objectPtr;             // new head
}