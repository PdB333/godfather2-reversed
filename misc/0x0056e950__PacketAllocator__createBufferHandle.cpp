// FUNC_NAME: PacketAllocator::createBufferHandle
// Address: 0x0056e950
// Role: Allocates a buffer handle (20 bytes) for packet transmission via a virtual allocator method.
// The handle stores a reference to the allocator, a parameter, and the allocated buffer pointer (twice, likely start and end).

#include <cstdint>

// Forward declaration of the packet spec struct
struct PacketSpec {
    int32_t type;       // +0x00
    int32_t size;       // +0x04
    int32_t flags;      // +0x08
};

// Structure allocated for the packet buffer handle (20 bytes)
struct PacketBufferHandle {
    PacketAllocator* allocator;  // +0x00
    int32_t param;               // +0x04
    void* bufferStart;           // +0x08
    void* bufferEnd;             // +0x0C
    PacketBufferHandle* next;    // +0x10 (initialized to null)
};

// Global pointer to the current packet buffer handle
PacketBufferHandle* g_packetBufferHandle = nullptr;  // DAT_0120555c

// The virtual allocator class (interface)
class PacketAllocator {
public:
    // Virtual method to allocate a buffer given a parameter and a spec structure
    virtual void* allocateBuffer(int32_t param, PacketSpec* spec) = 0;
};

// Function (__thiscall on PacketAllocator)
void PacketAllocator::createBufferHandle(int32_t param) {
    // Allocate memory for the handle
    PacketBufferHandle* handle = new PacketBufferHandle;  // FUN_009c8e50(0x14)
    if (handle != nullptr) {
        // Initialize handle fields
        handle->param = param;                          // puVar1[4] = param_2
        handle->allocator = this;                       // *puVar1 = param_1 (this)

        // Build allocation request: type=2, size=0x10, flags=0
        PacketSpec spec;
        spec.type = 2;
        spec.size = 0x10;
        spec.flags = 0;

        // Ask the allocator for a buffer
        void* buffer = this->allocateBuffer(param, &spec);  // (**(code **)*param_1)(param_2, &local_c)
        handle->bufferStart = buffer;                       // puVar1[2] = uVar2
        handle->bufferEnd = buffer;                         // puVar1[3] = uVar2 (initially the same)
        handle->next = nullptr;                             // puVar1[1] = 0

        // Store the handle globally
        g_packetBufferHandle = handle;                      // DAT_0120555c = puVar1
    } else {
        g_packetBufferHandle = nullptr;
    }
}