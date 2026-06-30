// FUNC_NAME: allocatePacketHeader

#include <cstdint>

// Forward declarations for internal engine functions
bool isNetworkInitialized(int param);          // FUN_0059c5c0
void* getNetworkManager();                     // FUN_0059c3b0, returns pointer to a manager struct

// Global allocator function pointer (likely operator new or custom EA allocator)
extern void* (*g_allocFunc)(size_t size, int flags);  // DAT_0119caf0

// Global sentinel pointer returned when network is not initialized
extern uint32_t* g_nullPacketHeader;           // DAT_0119cbbc

// 8-byte packet header structure
struct PacketHeader {
    uint32_t flags;      // +0x00: bitfield (type, version, etc.)
    uint16_t sequence;   // +0x02: sequence number (always 0 in this function)
    uint32_t timestamp;  // +0x04: network timestamp or ID
};

PacketHeader* allocatePacketHeader() {
    if (!isNetworkInitialized(0)) {
        return reinterpret_cast<PacketHeader*>(g_nullPacketHeader);
    }

    PacketHeader* header = reinterpret_cast<PacketHeader*>((*g_allocFunc)(8, 0));
    if (header != nullptr) {
        // Get the network manager and read the timestamp field at offset 0x30
        uint32_t* manager = static_cast<uint32_t*>(getNetworkManager());
        uint32_t timeValue = manager[0x30 / 4]; // offset 0x30

        // Set flags:
        // - Clear bits 3-14 (keep bits 0-2 and 15-31)
        // - Set bits 0-2 to 7 (type indicator)
        // - Set bit 15 (some flag, e.g., "reliable" or "ack required")
        header->flags = (header->flags & 0xFFFF8007) | 0x7;
        header->flags |= 0x8000; // set bit 15

        header->sequence = 0;
        header->timestamp = timeValue;
        return header;
    }
    return nullptr;
}