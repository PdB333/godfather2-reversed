// FUNC_NAME: PacketManager::initialize
// Function address: 0x00620040
// Initializes PacketManager structure with allocator and packet data size.
// Parameters: this (esi), allocator (edi), packetDataSize (ebp)
void PacketManager::initialize(Allocator* allocator, uint packetDataSize)
{
    // Ensure allocator is valid
    if (allocator == nullptr) {
        return;
    }

    // Set number of packets (32 slots, typical for TNL packet window)
    mNumPackets = 0x20;

    // Allocate memory for packet entries (32 * 16 bytes each)
    mPacketArray = (PacketEntry*)allocator->allocate(0x200, "PacketManager packets.");

    // Set default packet size multiplier (used for data allocation)
    mPacketSize = 1;

    // Initialize each packet entry
    if (mNumPackets != 0) {
        for (uint i = 0; i < mNumPackets; i++) {
            PacketEntry* entry = &mPacketArray[i];

            // Clear entry (16 bytes)
            entry->field0 = 0;
            entry->field4 = 0;
            entry->field8 = 0;
            entry->fieldC = 0;

            // Calculate data buffer size: packetSize * packetDataSize * 2
            uint dataSize = mPacketSize * packetDataSize * 2;

            // Allocate data buffer for this packet
            void* data = allocator->allocate(dataSize, "PacketManager packet data", 1);

            // Store packet size and data pointer
            entry->size = mPacketSize;   // +0x00
            entry->field4 = 0;           // +0x04
            entry->data = data;          // +0x08
            // +0x0C remains 0 (cleared above)
        }
    }
}