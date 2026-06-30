// FUN_00580640: StreamManager::initializeStreamSystem
// This function appears to be a factory/singleton initializer for a stream manager subsystem.
// It allocates a 20-byte structure, stores a global singleton pointer, and calls a virtual method
// on the current object (provided via ECX) to create a buffer/stream of type 2 with size 0x10.
// Typical EA EARS engine pattern for subsystem creation.

// Forward declare allocation function (from engine core)
void* __cdecl engineAllocate(unsigned int size);

// Structure for the allocated manager data (0x14 = 20 bytes)
struct StreamManagerData {
    void* vtable;                    // +0x00: Virtual table pointer (inherited from base)
    int    flags;                    // +0x04: Initialized to 0
    int    streamHandle;             // +0x08: Result from virtual call
    int    streamHandleCopy;         // +0x0C: Copy of handle (possibly for reference counting)
    int    streamId;                 // +0x10: Parameter passed to function
};

// Global singleton pointer
StreamManagerData* g_StreamManagerSingleton = nullptr;

// Member function of some base manager class (e.g., EARS::Framework::Manager)
void __thiscall StreamManager::initializeStreamSystem(int streamId)
{
    // Allocate manager data block
    StreamManagerData* pData = (StreamManagerData*)engineAllocate(0x14);
    if (pData == nullptr)
    {
        g_StreamManagerSingleton = nullptr;
        return;
    }

    // Initialize fields
    pData->vtable = this;               // Store pointer to the calling object (vtable pointer or base manager)
    pData->flags = 0;                   // Reset flags
    pData->streamId = streamId;         // Save the stream identifier

    // Build a stream descriptor on the stack: type=2, size=0x10, extraFlags=0
    struct StreamDescriptor {
        int type;
        int size;
        int extraFlags;
    };
    StreamDescriptor desc;
    desc.type       = 2;
    desc.size       = 0x10;
    desc.extraFlags = 0;

    // Call virtual method #0 on the base class (index 0 of vtable) to create the actual stream
    // This method takes the streamId and a pointer to the descriptor, returns a handle
    int newHandle = (*(int (__thiscall*)(int, StreamDescriptor*))this->vtable)(streamId, &desc);

    pData->streamHandle     = newHandle;
    pData->streamHandleCopy = newHandle;  // Duplicate for safety (common in EA engine)

    g_StreamManagerSingleton = pData;
}