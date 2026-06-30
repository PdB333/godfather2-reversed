// FUNC_NAME: allocateObjectFromPool
// Function at 0x006844f0: Allocates a 256-byte block from a memory pool and then initializes an object (pObject). Returns the initialized object or nullptr on failure.
void* allocateObjectFromPool(void* pObject, void* pPool) {
    struct AllocParams {
        int allocType;   // +0x00: allocation type (e.g., 2 = default)
        int alignment;   // +0x04: requested alignment (16 bytes)
        int flags;       // +0x08: additional flags (0)
    } allocInfo = {2, 0x10, 0};

    void* allocResult = engineAllocMemory(0x100, &allocInfo, pPool);
    if (allocResult != nullptr) {
        // Construct/initialize the object using the allocated buffer (pObject)
        return objectInitilize(pObject);
    }
    return nullptr;
}