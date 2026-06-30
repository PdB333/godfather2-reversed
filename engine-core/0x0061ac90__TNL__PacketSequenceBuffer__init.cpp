// FUNC_NAME: TNL::PacketSequenceBuffer::init
#include <cstdint>

class TNL::PacketSequenceBuffer {
public:
    // Initialize the sequence buffer with default capacity (0x1000 entries)
    void __thiscall init();
};

void TNL::PacketSequenceBuffer::init()
{
    // Clear base class / object header (first 0x800 bytes)
    memset(this, 0, 0x800);

    // +0x800: flags or status (reset to 0)
    *(uint32_t*)((uint8_t*)this + 0x800) = 0;

    // +0x808: maximum number of entries (capacity)
    *(uint32_t*)((uint8_t*)this + 0x808) = 0x1000; // 4096

    // +0x804: vtable pointer (set to class-specific vtable at 0x0061b1a0)
    *(void**)((uint8_t*)this + 0x804) = (void*)0x0061b1a0;

    // +0x80c: allocate the entry buffer (each entry is 4 bytes)
    void* buffer = AllocateMemory(0x4000); // capacity * 4
    *(void**)((uint8_t*)this + 0x80c) = buffer;

    // +0x810: head index (next write position)
    *(uint32_t*)((uint8_t*)this + 0x810) = 0;
    // +0x814: tail index (next read position)
    *(uint32_t*)((uint8_t*)this + 0x814) = 0;
    // +0x818: number of elements currently in the buffer
    *(uint32_t*)((uint8_t*)this + 0x818) = 0;

    // Zero out the allocated buffer (capacity * 4 bytes)
    memset(buffer, 0, *(uint32_t*)((uint8_t*)this + 0x808) * 4);
}