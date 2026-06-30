// FUNC_NAME: MemoryPool::allocateObject
// Function at 0x004c5760: Allocates an object from a memory pool, sets its vtable, and optionally calls destructor on failure.
// Uses a global memory pool at DAT_01206880 with offset 0x14 as a bump allocation pointer.

struct MemoryPoolHeader {
    // +0x14: bumpAllocPtr - pointer to next free memory block
    int* bumpAllocPtr;
};

// External global pointer to the memory pool base
extern MemoryPoolHeader* gMemoryPool;  // Actually DAT_01206880

void* __thiscall MemoryPool::allocateObject(void* thisPtr, byte flags) {
    // Set the object's vtable pointer (first field)
    *(void**)thisPtr = &PTR_FUN_00e362f4;  // vtable address

    // Get the bump allocator pointer from the pool
    int** bumpAllocPtrPtr = (int**)((char*)gMemoryPool + 0x14);
    *bumpAllocPtrPtr = &PTR_LAB_01124770;  // initialize? This seems odd, perhaps setting a sentinel?

    // Current bump pointer value
    int* currentBump = *bumpAllocPtrPtr;

    // Advance pointer by 4 bytes (allocate 4 bytes?)
    currentBump = (int*)((int)currentBump + 4);

    // Align to 4 bytes
    int* alignedBump = (int*)((int)currentBump & 0xFFFFFFFC);

    // Store the aligned pointer back
    *bumpAllocPtrPtr = alignedBump;

    // Store the object's data (thisPtr + 4) at the allocated location
    *alignedBump = (int)((char*)thisPtr + 4);

    // Advance again by 4 bytes
    *bumpAllocPtrPtr = (int*)((int)*bumpAllocPtrPtr + 4);

    // If flag bit 0 is set, call destructor (likely freeing memory)
    if ((flags & 1) != 0) {
        FUN_009c8eb0(thisPtr);  // pointer destructor
    }

    return thisPtr;
}