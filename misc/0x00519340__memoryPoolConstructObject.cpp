// FUNC_NAME: memoryPoolConstructObject
// Constructs an object at the given memory location using a global bump allocator pool.
// The pool is referenced via gMemoryPoolBase + 0x14 (a pointer to the current allocation cursor).
// After placement, the object's vtable is set to a global table (kObjectVtable) and two parameters
// (object pointer and userData) are stored as a 64-bit payload after the vtable.
void memoryPoolConstructObject(void* objectMemory, uint32 userData) {
    // Validate the object memory pointer
    if (objectMemory != NULL) {
        // Call the object's initializer (likely sets up vtable and base fields)
        ObjectInit(objectMemory, userData);

        // Retrieve the current allocation cursor from the global pool
        uint8_t** currentPtrSlot = reinterpret_cast<uint8_t**>(gMemoryPoolBase + 0x14); // +0x14: pool cursor pointer
        uint8_t* currentPtr = *currentPtrSlot;

        // Write the vtable pointer at the current position
        *reinterpret_cast<void**>(currentPtr) = reinterpret_cast<void*>(&kObjectVtable); // Global function table

        // Advance past the vtable (4 bytes)
        currentPtr += 4;

        // Align the pointer to a 4-byte boundary (round up)
        currentPtr = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(currentPtr) + 3) & ~static_cast<uintptr_t>(3));

        // Store the object memory and userData as a 64-bit value (low 32 = objectMemory, high 32 = userData)
        *reinterpret_cast<uint64_t*>(currentPtr) = (static_cast<uint64_t>(userData) << 32) | reinterpret_cast<uintptr_t>(objectMemory);

        // Advance the cursor by 8 bytes (size of payload)
        currentPtr += 8;

        // Update the pool cursor to the new position
        *currentPtrSlot = currentPtr;
    }
}