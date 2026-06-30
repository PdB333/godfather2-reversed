// FUNC_NAME: GameObjectFactory::createObject

#include <cstdint>

// Forward declarations for functions called.
// These are engine-level functions, actual signatures may vary.
int32_t allocateMemoryPool(int32_t size, void* allocInfo, int32_t classId);
int32_t initializeGameObject(void* parentObject);

// Structure passed to the memory allocator, containing pool and flags.
struct MemoryAllocationInfo {
    int32_t type;      // +0x00
    int32_t poolIndex; // +0x04 - likely index into memory pool (here 0x10)
    int32_t flags;     // +0x08
};

/**
 * Creates a game object of the given classId.
 * Returns a pointer to the created object (or 0 on failure).
 * param_1: parent object (used for initialization)
 * param_2: class identifier
 */
int32_t __thiscall GameObjectFactory::createObject(void* parentObject, int32_t classId) {
    // Set up allocation parameters: pool type 2, pool index 0x10, no flags.
    MemoryAllocationInfo allocInfo;
    allocInfo.type = 2;
    allocInfo.poolIndex = 0x10;
    allocInfo.flags = 0;

    // Attempt to allocate the object's internal data (size 0x18c = 396 bytes)
    // The allocator may also internally register the object.
    int32_t allocResult = allocateMemoryPool(0x18c, &allocInfo, classId);
    if (allocResult != 0) {
        // Allocation succeeded; call initializer on the parent object.
        // The parent could be the containing scene or manager.
        return initializeGameObject(parentObject);
    }
    // Allocation failed, return null.
    return 0;
}