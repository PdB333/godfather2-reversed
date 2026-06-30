// FUNC_NAME: PooledObject::~PooledObject
// Address: 0x0055acc0
// Destructor for a pooled object. Deallocates the memory slot if the handle is valid,
// then sets the vtable pointer to a sentinel value to prevent further virtual calls.

void __thiscall PooledObject::~PooledObject(PooledObject* this)
{
    // Offset +0x10: handle/flags for the allocated slot
    uint handle = *(uint*)((uint8_t*)this + 0x10);

    // If the handle is non-negative (i.e., not marked as invalid), release the slot
    if ((int)handle >= 0)
    {
        // Offset +0x8: pointer to the pool manager (thread-local or generic)
        void* poolManager = *(void**)((uint8_t*)this + 0x8);

        // Extract the slot index from the lower 30 bits (mask 0x3FFFFFFF)
        uint slotIndex = handle & 0x3FFFFFFF;

        // Retrieve thread-local storage (unused here; possibly a validity check)
        TlsGetValue(DAT_01139810);

        // Deallocate the slot: pool manager, offset = slotIndex * 0x30 (48 bytes per slot),
        // and a constant 0x17 (23) likely representing block size or a magic identifier.
        FUN_00aa26e0(poolManager, slotIndex * 0x30, 0x17);
    }

    // Set the vtable pointer to a global sentinel to mark the object as destroyed
    *(void**)((uint8_t*)this + 0x0) = (void*)&PTR_LAB_00d96914;

    return;
}