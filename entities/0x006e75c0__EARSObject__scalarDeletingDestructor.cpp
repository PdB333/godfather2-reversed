// FUNC_NAME: EARSObject::scalarDeletingDestructor
// Function at 0x006e75c0: Custom scalar deleting destructor with EARS memory management.
// Calls destructor (0x006e6cf0), then a memory block operation on the first word of the object,
// and optionally frees the memory if `flags & 1` is set.
void* __thiscall EARSObject::scalarDeletingDestructor(void* this, byte flags) {
    // Step 1: Call the class destructor (handles virtual destructor chain)
    this->~EARSObject(); // FUN_006e6cf0

    // Step 2: Process the first word (likely a memory block header or alignment info)
    EARS::MemoryManager::adjustBlock(*(uint32_t*)this); // FUN_009c8f10

    // Step 3: If the object was allocated on the heap (flag bit 0), free the memory
    if ((flags & 1) != 0) {
        EARS::MemoryManager::deallocate(this); // FUN_009c8eb0
    }

    return this;
}