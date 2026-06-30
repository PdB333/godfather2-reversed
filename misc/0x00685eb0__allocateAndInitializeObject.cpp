// FUNC_NAME: allocateAndInitializeObject
// Function at 0x00685eb0: Allocates a block of memory (size 0x230) and initializes an object via a separate init function.
// Used by FUN_00688af0 (likely a manager or factory method).
// Parameters: param_1 – pointer to allocated memory (output from allocation), param_2 – context/extra data passed to allocator.
// Returns pointer to initialized object, or NULL on allocation failure.

// Memory allocation descriptor – typical for EARS engine allocation functions.
struct EARSAllocationDescriptor {
    int type;       // +0x00: allocation type (e.g., pool identifier)
    int alignment;  // +0x04: memory alignment (often 0x10)
    int flags;      // +0x08: allocation flags (zero = default)
};

// Forward declarations of called functions (guessed names)
void* __cdecl earMAlloc(int size, EARSAllocationDescriptor* desc, int context);  // FUN_0043b980
void* __cdecl objectInit(void* obj);  // FUN_00905110 – initializes the object, returns same pointer

void* __cdecl allocateAndInitializeObject(void* param_1, int param_2) {
    EARSAllocationDescriptor desc;
    desc.type = 2;
    desc.alignment = 0x10;
    desc.flags = 0;
    
    // Allocate 0x230 (560) bytes with given descriptor.
    void* allocated = earMAlloc(0x230, &desc, param_2);
    if (allocated != NULL) {
        // Initialize the newly allocated object.
        // param_1 is assumed to be the same as allocated (common pattern in Ghidra output).
        return objectInit(param_1);
    }
    return NULL;
}