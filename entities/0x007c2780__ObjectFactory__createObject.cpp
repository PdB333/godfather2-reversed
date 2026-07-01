// FUNC_NAME: ObjectFactory::createObject
// Function at 0x007c2780: factory that allocates and constructs an object of size 0x98.
// The allocator (0x009c8ed0) uses a parameter struct with type=2, alignment=16, flags=0.
// If allocation succeeds, the constructor (0x007c2570) is called with the provided arguments.
// The return value is the result of the constructor (likely the object pointer).
void* __cdecl createObject(void* arg1, void* arg2)
{
    // Allocation parameter block: type, alignment, flags
    struct AllocParams {
        int type;       // +0x00
        int alignment;  // +0x04
        int flags;      // +0x08
    } params = {2, 0x10, 0};

    void* mem; // not used in the original code – possibly a decompilation artifact
    int success = allocator(0x98, &params); // EARS allocator (returns non-zero on success)

    if (success != 0) {
        // Call constructor with (arg1, arg2) – arg1 might be the allocated memory or a parent object
        return constructor(arg1, arg2);
    }
    return 0;
}