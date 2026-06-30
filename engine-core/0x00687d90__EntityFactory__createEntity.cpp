// FUNC_NAME: EntityFactory::createEntity
// Function address: 0x00687d90
// Role: Allocates and constructs an entity object with size 0x160 (352 bytes) using a custom allocator.
// The allocation parameters (2, 16, 0) hint at pool ID, alignment, and flags.
// Returns pointer to constructed object on success, or nullptr on allocation failure.

int EntityFactory::createEntity(Entity* thisPtr, int creationParam) // 'this' might be a manager or allocator context
{
    // Allocation parameters: pool index=2, alignment=16, flags=0
    AllocationParams allocParams;
    allocParams.poolIndex = 2;
    allocParams.alignment = 0x10; // 16-byte alignment
    allocParams.flags = 0;

    // Attempt to allocate memory block of size 0x160 from the custom allocator
    int* memoryBlock = FUN_0043b980(0x160, &allocParams, creationParam);
    if (memoryBlock != nullptr) {
        // Construct the object at the allocated memory, using thisPtr as parent/context
        int result = FUN_00846de0(thisPtr);
        return result;
    }
    return 0; // allocation failed
}