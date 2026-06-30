// FUNC_NAME: Entity::release
// Function address: 0x005a8620
// Role: Releases the entity, calling base cleanup and deleting if reference count is zero.
// The object layout appears to have a reference count (short) at offset +2.
// If the count is zero, the object's memory is deallocated via a global function pointer.

void Entity::release() {
    // Call base class cleanup (likely a virtual destructor or release chain)
    baseRelease(); // FUN_005a72f0

    // Check reference count at offset +2 (short)
    if (*(short*)(this + 2) == 0) {
        // Obtain pointer to the memory block to deallocate
        void* mem = getDeallocationPointer(); // FUN_005a3900
        // Call global deallocation function with size 8 (e.g., operator delete or custom allocator)
        // DAT_0119caf8 is a function pointer stored in the global data section
        ((void (*)(void*, int))DAT_0119caf8)(mem, 8);
    }
}