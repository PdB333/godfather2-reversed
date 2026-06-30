// FUNC_NAME: allocateAndConstructObject

// This function attempts to allocate memory for an object of size 0xF0 (240 bytes)
// and then initializes an existing object if allocation succeeds.
// It uses a custom memory allocator that takes a parameter struct with alignment and flags.

struct AllocationParams {
    int field_0; // +0x00: flags or pool id
    int field_4; // +0x04: alignment (here 0x10 = 16)
    int field_8; // +0x08: additional flags (here 0)
};

// Forward declarations of called functions (external, not defined here)
extern int AllocateMemory(uint size, AllocationParams* params, uint allocParam);
extern int InitializeObject(uint obj);

uint allocateAndConstructObject(uint obj, uint allocParam)
{
    AllocationParams allocParams;
    allocParams.field_0 = 2;
    allocParams.field_4 = 0x10;
    allocParams.field_8 = 0;

    // Attempt to allocate 0xF0 bytes using the custom allocator
    int allocResult = AllocateMemory(0xF0, &allocParams, allocParam);
    
    if (allocResult != 0) {
        // Allocation succeeded – initialize the provided object and return its result
        uint result = InitializeObject(obj);
        return result;
    }
    
    // Allocation failed – return 0
    return 0;
}