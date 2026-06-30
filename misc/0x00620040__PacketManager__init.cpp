// FUNC_NAME: PacketManager::init
// Function address: 0x00620040
// Role: Initialize the packet manager with a maximum of 32 packets, each with a fixed data buffer size.
// The function uses a memory allocator (passed via EDI) to allocate a pool of packet entries and their data buffers.

void PacketManager::init(int packetSize, class MemoryAllocator* allocator) // __thiscall, this in ESI, allocator in EDI, packetSize in EBP
{
    uint i;
    int offset;
    uint* packetEntry;   // Pointer to a 16-byte packet entry
    uint* dataBuffer;

    // Sanity check: allocator must be valid (EDI)
    if (allocator == nullptr) {
        return;
    }

    // Set the maximum number of packets to 32 (0x20)
    // Offset +0x00: m_maxPackets (uint)
    *this = 0x20; // unaff_ESI[0] = 0x20

    // Call allocator->allocate(0x200, "PacketManager packets.")
    // The allocator's vtable+0x08 is the allocate() method.
    // Returns a pointer to a pool of 32 packet entries (16 bytes each => 512 bytes total)
    void* pool = allocator->allocate(0x200, "PacketManager packets.");

    // Offset +0x14: m_packetPool (void*)
    this->m_packetPool = pool;

    // Initialize packet size (default 1, but will be multiplied by packetSize*2 later)
    // Offset +0x08: m_packetSizeFactor (uint)
    this->m_packetSizeFactor = 1;

    // If the pool was allocated, initialize each packet entry
    if (this->m_maxPackets != 0) {
        offset = 0;
        i = 0;
        do {
            packetEntry = (uint*)((char*)this->m_packetPool + offset);

            // Clear the 16-byte packet entry
            for (int j = 0; j < 4; ++j) {
                packetEntry[j] = 0;
            }

            // Allocate data buffer for this packet: size = m_packetSizeFactor * packetSize * 2
            // Note: packetSize is passed in EBP (e.g., MTU)
            uint dataSize = this->m_packetSizeFactor * packetSize * 2;
            dataBuffer = (uint*)allocator->allocate(dataSize, "PacketManager packet data", 1);

            // Set packet entry fields:
            // Offset +0x00: m_size (uint) = m_packetSizeFactor (1)
            packetEntry[0] = this->m_packetSizeFactor;
            // Offset +0x04: m_packetData (void*) = dataBuffer
            packetEntry[2] = (uint)dataBuffer;
            // Offset +0x08: m_unknown2 (uint) = 0 (already cleared)
            // packetEntry[1] is m_unknown1 (uint) = 0 (cleared)
            // The fourth dword (+0x0C) remains 0 from clearing

            offset += 16; // 0x10 bytes per entry
            i++;
        } while (i < this->m_maxPackets);
    }
}