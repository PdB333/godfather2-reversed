// FUNC_NAME: createObjectWithAllocDescriptor
struct AllocDescriptor {
    unsigned int poolId;       // +0x0: likely pool index
    unsigned int alignment;    // +0x4: alignment requirement (0x10)
    unsigned int flags;        // +0x8: flags (0 = default)
};

// Allocates an object of given size from a specific pool, then calls an initialization function
// param_1: pointer to object data (uninitialized)
// param_2: likely allocator context (e.g., heap tag)
// Returns initialized object pointer on success, 0 on failure
unsigned int createObjectWithAllocDescriptor(unsigned int param_1, unsigned int param_2) {
    AllocDescriptor descriptor;
    descriptor.poolId = 2;          // pool for large objects
    descriptor.alignment = 0x10;    // 16-byte alignment
    descriptor.flags = 0;           // no special flags

    // Custom memory allocator: allocate 0x1D0 bytes using the descriptor
    int result = allocFromPool(0x1D0, &descriptor, param_2);  // FUN_0043b980
    if (result != 0) {
        // Initialize the object (e.g., call constructor, set vtable)
        return objectInit(param_1);  // FUN_00890a80
    }
    return 0;
}