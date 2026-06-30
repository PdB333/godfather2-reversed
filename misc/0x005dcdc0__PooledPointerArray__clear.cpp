// FUNC_NAME: PooledPointerArray::clear
// Function at 0x005dcdc0: Releases all objects stored in an array back to a global pool, then frees the array and releases a sub-object.
// Offsets: +0x270 = pointer array, +0x274 = count, +0x278 = capacity (unused in this function?), +0x2a0 = sub-object pointer, +0x2ac = sub-object release function pointer.
// The global DAT_01223508 is a pool allocator with layout: +0x1c = freeCount, +0x20 = allocatedCount, +0x44 = freeListHead.

void __thiscall PooledPointerArray::clear(void) {
    uint count;
    void **objPtr;
    PoolAllocator *pool;
    uint i;

    pool = (PoolAllocator *)DAT_01223508; // global pool instance
    count = *(uint *)(this + 0x274); // number of objects in array

    // Return each object to the pool's free list
    i = 0;
    if (count != 0) {
        do {
            objPtr = *(void ***)(*(int *)(this + 0x270) + i * 4); // pointer from array
            if (objPtr != (void **)0x0) {
                // Insert object at head of free list (classic free list technique)
                *objPtr = *(void **)(pool + 0x44); // store old head in first 4 bytes of object
                // Update pool counters
                pool->allocatedCount--; // +0x20
                pool->freeCount++;      // +0x1c
                // Set new head of free list
                *(void ***)(pool + 0x44) = objPtr;
            }
            i++;
        } while (i < count);
    }

    // Clear the count
    *(uint *)(this + 0x274) = 0;

    // Deallocate the array itself using a known memory function
    FUN_009c8f10(*(void *)(this + 0x270)); // likely operator delete[] or pool dealloc
    *(int *)(this + 0x270) = 0;

    // Also clear capacity field (or another pointer)
    *(int *)(this + 0x278) = 0;

    // If a sub-object exists, release it via stored function pointer
    if (*(int *)(this + 0x2a0) != 0) {
        (**(code **)(this + 0x2ac))(*(int *)(this + 0x2a0));
    }

    // Redundant null check (likely dead code or leftover)
    if (*(int *)(this + 0x270) != 0) {
        FUN_009c8f10(*(int *)(this + 0x270));
    }
}