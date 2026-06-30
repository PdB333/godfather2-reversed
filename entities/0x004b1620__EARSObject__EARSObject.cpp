// FUNC_NAME: EARSObject::EARSObject
// Address: 0x004b1620
// Constructor for a 0x60-byte object with optional allocator registration.
void * __thiscall EARSObject::EARSObject(void *this, byte flags) {
    // Call base class constructor (likely eagObject or similar)
    FUN_00473a60();

    // If bit 0 of flags is set, object was allocated via a custom allocator
    // and needs to be registered with that allocator for proper deletion.
    if ((flags & 1) != 0) {
        // Retrieve global allocator vtable pointer
        int *allocatorVtable = (int *)FUN_009c8f80();
        // Call the second entry in the allocator vtable (offset +4)
        // Parameters: this pointer and object size (0x60 = 96 bytes)
        // This function likely stores the allocation info for later deallocation.
        (**(code **)(allocatorVtable + 1))(this, 0x60);
    }
    return this;
}