// FUNC_NAME: eastl::shared_ptr::internal_assign
void __thiscall eastl::shared_ptr::internal_assign(eastl::shared_ptr *this, void **outPtr, void *newTarget, void *oldPair, char alreadyMapped)
{
    bool found;
    int idx;

    // Check if we need to look up the new target in an internal table
    if ((alreadyMapped == '\0') && (newTarget != *(void **)((int)this + 4))) {
        idx = findOrReserveIndex((int)newTarget + 0x10);    // offset +0x10 might be a reference counter or hash
        if (-1 < idx) {
            found = true;
            goto LAB_00699e22;
        }
    }
    found = false;
LAB_00699e22:
    // Debug memory allocation (size 0x30) with source location
    void *alloc = debugAllocate(0x30, "EASTL", 0, 0, "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xe9);
    if (alloc != (void *)-0x10) {
        // Release the two parts of the old pair (likely two smart pointers)
        releaseObject(oldPair);
        releaseObject((char *)oldPair + 0x10);
    }
    // Initialize the new allocation with target, current stored pointer, and found flag
    constructInternal(alloc, newTarget, *(void **)((int)this + 4), found);
    // Increment reference count at +0x14
    *(int *)((int)this + 0x14) = *(int *)((int)this + 0x14) + 1;
    *outPtr = alloc;
    return;
}