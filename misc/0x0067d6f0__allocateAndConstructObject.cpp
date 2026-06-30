// FUNC_NAME: allocateAndConstructObject
// Address: 0x0067d6f0
// Description: Allocates memory for an object (size 0xc0 = 192 bytes) using a memory manager
// and if successful, initializes it via a constructor-like call. Returns pointer to object or 0 on failure.
struct MemoryAllocationParams {
    int alignment; // +0x00
    int flags;     // +0x04
    int extra;     // +0x08
};

// External functions (forward declarations)
int __cdecl memoryManagerAllocate(int size, MemoryAllocationParams* params); // FUN_009c8ed0
int __thiscall objectConstructor(void* thisPtr, int param1, int param2);     // FUN_004154c0

int* __cdecl allocateAndConstructObject(int param1, int param2)
{
    MemoryAllocationParams allocParams;
    allocParams.alignment = 2;   // Alignment requirement (e.g., 2-byte aligned)
    allocParams.flags = 0x10;    // Memory pool flags or type indicator
    allocParams.extra = 0;       // Reserved

    // Attempt to allocate 192 bytes from the game's memory manager
    void* obj = (void*)memoryManagerAllocate(0xc0, &allocParams);
    if (obj != 0) {
        // Initialize the object with the provided parameters
        int result = objectConstructor(obj, param1, param2);
        return (int*)result;
    }
    return 0;
}