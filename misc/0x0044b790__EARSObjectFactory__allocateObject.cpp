// FUNC_NAME: EARSObjectFactory::allocateObject

typedef struct {
    uint16_t type;        // +0x00
    uint16_t subtype;     // +0x02 (alignment)
    uint32_t flags;       // +0x04
} AllocationConfig;

typedef struct {
    int (**vtable)(void); // +0x00
    // ... other allocator fields
} GameAllocator;

GameAllocator* __fastcall getGameAllocator(); // 0x009c8f80

EARSObject* __thiscall EARSObject::constructor(void* mem, uint32_t param); // 0x0044b610

// Allocates a new EARSObject of size 0xA0 (160 bytes)
// Returns null on allocation failure.
EARSObject* EARSObjectFactory::allocateObject()
{
    GameAllocator* allocator = getGameAllocator();
    AllocationConfig config;
    config.type = 2;         // Object type ID (e.g., EARSObject)
    config.subtype = 0x10;   // Subtype or pool index
    config.flags = 0;        // Additional allocation flags

    // Call the allocator's allocate method (first vtable entry)
    void* mem = allocator->vtable[0](0xA0, &config);
    if (mem != nullptr) {
        // Construct the object from allocated memory
        // Passing the return address (hidden parameter) for debugging/tracking
        return EARSObject::constructor(mem, 0);
    }
    return nullptr;
}