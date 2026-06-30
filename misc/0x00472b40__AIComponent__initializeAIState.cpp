// FUNC_NAME: AIComponent::initializeAIState
void __thiscall AIComponent::initializeAIState(AIComponent* this)
{
    // Offset 0x110 stores a pointer to an AI state object (or null)
    if (*(void**)((uint8_t*)this + 0x110) == 0)
    {
        // Get global object allocator singleton (FUN_009c8f80)
        Allocator* allocator = GetAllocator();

        // Allocation descriptor: type=2, flags=0x10, unknown=0
        struct AllocDescriptor {
            int type;     // +0x00
            int flags;    // +0x04
            int unknown;  // +0x08
        } desc;
        desc.type = 2;
        desc.flags = 0x10;
        desc.unknown = 0;

        // Call allocator's first virtual method (allocate) with size 0x70 and descriptor
        // The allocator object vtable entry 0 points to the allocate function
        typedef void* (__thiscall *AllocateFunc)(Allocator*, int, AllocDescriptor*);
        AllocateFunc allocateFunc = *(AllocateFunc*) * (void**)allocator;
        void* newBlock = allocateFunc(allocator, 0x70, &desc);

        if (newBlock != 0)
        {
            // Initialize the allocated block: bytes at offsets 0x60..0x64
            // These likely represent flags or initial states of the AI state object
            *(uint8_t*)((uint8_t*)newBlock + 0x60) = 0;
            *(uint8_t*)((uint8_t*)newBlock + 0x61) = 0;
            *(uint8_t*)((uint8_t*)newBlock + 0x62) = 0;
            *(uint8_t*)((uint8_t*)newBlock + 0x63) = 0;
            *(uint8_t*)((uint8_t*)newBlock + 0x64) = 1;

            // Store the newly created state at offset 0x110
            *(void**)((uint8_t*)this + 0x110) = newBlock;
            return;
        }
        // Allocation failed – clear pointer
        *(void**)((uint8_t*)this + 0x110) = 0;
    }
}