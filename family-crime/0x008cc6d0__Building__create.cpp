// FUNC_NAME: Building::create
// Address: 0x008cc6d0
// Creates a Building object of size 0x50 using a pool allocator.
// The parameter objectType is passed to the constructor (0x008cc4c0) as the building type.
// Returns a pointer to the new Building on success, or nullptr on failure.

Building* Building::create(uint32_t objectType) {
    // Get the singleton GameManager (0x004a37d0)
    GameManager* gameManager = GameManager::getInstance();
    if (gameManager == nullptr) return nullptr;
    // Check if a pool manager exists at offset +0x1c
    if (gameManager->poolManager == nullptr) return nullptr; // +0x1c

    // Get the global pool allocator (0x009c8f80)
    PoolAllocator* allocator = PoolAllocator::getInstance();
    if (allocator == nullptr) return nullptr; // not explicitly checked but assumed

    // Prepare allocation parameters (type=2, alignment=0x10, flags=0)
    AllocationParams params;
    params.type      = 2;      // local_c
    params.alignment = 0x10;   // local_8
    params.flags     = 0;      // local_4

    // Call allocator's allocate function (first vtable entry)
    void* memory = allocator->allocate(0x50, &params);
    if (memory == nullptr) {
        return nullptr;
    }

    // Call the constructor (0x008cc4c0) on the allocated memory
    // The constructor receives this=memory, objectType, and possibly hidden stack arguments.
    Building* obj = Building::ctor(memory, objectType);

    // Exception handling: check the high byte of EDI register
    // If it is non-zero, the construction succeeded; return the pointer.
    // Otherwise, call destructor and return nullptr.
    if (ediHighByte != 0) {
        return obj;
    }

    if (obj != nullptr) {
        // Call destructor via vtable[0] with argument 1
        obj->destroy(1); // or obj->vtable[0](1)
    }
    return nullptr;
}