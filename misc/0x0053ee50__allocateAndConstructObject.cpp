// FUNC_NAME: allocateAndConstructObject

void __cdecl allocateAndConstructObject(uint32 param1, uint32 param2, uint32 param3) {
    // Allocate a 0x870-byte block for a new object (e.g., a large game entity like Player or NPC)
    void* memBlock = AllocateMemoryForObject(0x870); // Custom EARS allocator
    if (memBlock != nullptr) {
        // Call the constructor on the allocated memory.
        // The this pointer is passed implicitly (likely via ECX in __thiscall).
        // Only param2 and param3 are passed as arguments; param1 is unused.
        InitializeObjectWithArgs(param2, param3);
    }
}