// FUNC_NAME: MemoryManager::AllocateObject
// Function at 0x0067d910: Allocates an object of size 0x70 using a vtabled allocator.
// Returns a pointer to the allocated object with its vtable set, or nullptr on failure.
// Based on Ghidra decompiled output from The Godfather 2 (2009, EARS engine).

// Hypothetical allocation descriptor structure
struct AllocDescriptor {
    uint32_t field0;  // 0x00: observed value 2 (flags?)
    uint32_t field4;  // 0x04: observed value 0x10 (alignment?)
    uint32_t field8;  // 0x08: observed value 0 (reserved)
};

void* MemoryManager::AllocateObject() {
    // Get the memory allocator vtable (FUN_009c8f80)
    void* allocVtable = GetMemoryAllocator();

    // Prepare allocation parameters
    AllocDescriptor desc;
    desc.field0 = 2;
    desc.field4 = 0x10;
    desc.field8 = 0;

    // Call first vtable entry: allocate(size, &desc)
    // The allocator returns a pointer to the new object
    void* newObject = reinterpret_cast<void* (
        __stdcall*)(uint32_t, AllocDescriptor*)>(*(void**)allocVtable)
        (0x70, &desc);

    if (newObject != nullptr) {
        // Initialize the object (FUN_00416a70) – likely a debug trace or memset
        // The first argument is 0, second seems to be the return address (unaff_retaddr)
        FUN_00416a70(0, /* return address */ );

        // Set the vtable pointer to the object's class vtable
        *(void**)newObject = &PTR_FUN_00d58020;

        return newObject;
    }
    return nullptr;
}