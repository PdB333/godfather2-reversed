// FUNC_NAME: Entity::create
void* Entity::create(void* initData, void* allocatorContext)
{
    // Memory allocation descriptor: type=2 (pool?), alignment=0x10, flags=0
    struct AllocDescriptor {
        int type;       // +0x00
        int alignment;  // +0x04
        int flags;      // +0x08
    } desc = {2, 0x10, 0};

    // Allocate 0x1f0 bytes (496 bytes) with given alignment and context
    void* mem = EARS::Memory::allocateAligned(0x1f0, &desc, allocatorContext);
    if (mem != nullptr) {
        // Initialize the object using the provided data
        return EARS::Memory::initialize(initData);
    }
    return nullptr;
}