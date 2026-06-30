// FUNC_NAME: PacketWindow::addPacket
// Address: 0x00572ac0
// Adds a packet (32 bytes) to either the primary or secondary packet window queue.
// The packet's field at offset 0x0C (uint16_t) determines the queue:
//   - 0 -> primary queue (dynamic max limit at +0xAC)
//   - non-zero -> secondary queue (fixed limit of 69 entries)
// After copying, sets flag at packet+6 (OR with 0x80), increments count, and calls
// FUN_00572a00 to update the window state (likely sequence number / notification).

struct Packet {
    char data[32];           // 0x00
    // uint16_t flags;       // +0x06
    // uint16_t queueType;   // +0x0C (0 for primary)
};

class PacketWindow {
public:
    // Member offsets (relative to this):
    // +0x0C: not used in this function (maybe other state)
    // +0xA0: Packet* primaryBuffer
    // +0xA4: Packet* secondaryBuffer
    // +0xA8: uint16_t primaryCount
    // +0xAA: uint16_t secondaryCount
    // +0xAC: uint16_t primaryMaxCount

    void addPacket(const Packet& packet);
};

void PacketWindow::addPacket(const Packet& packet)
{
    // Determine queue type from packet itself
    uint16_t queueType = *(const uint16_t*)((const char*)&packet + 0x0C);

    if (queueType == 0)
    {
        // Primary queue
        uint16_t& count = *(uint16_t*)((char*)this + 0xA8);
        uint16_t maxCount = *(uint16_t*)((char*)this + 0xAC);
        if (count < maxCount - 1)  // reserve one slot
        {
            // Compute destination slot pointer
            Packet* destSlot = (Packet*)(*(int*)((char*)this + 0xA0) + count * sizeof(Packet));
            // Copy entire packet (32 bytes)
            *destSlot = packet;
            // Set flag at offset +6 (e.g., dirty/pending flag)
            uint16_t& flags = *(uint16_t*)((char*)destSlot + 0x06);
            flags |= 0x80;
            // Increment count
            count++;
            // Notify window with buffer pointer and new count
            FUN_00572a00(*(int*)((char*)this + 0xA0), count);
        }
    }
    else
    {
        // Secondary queue
        uint16_t& count = *(uint16_t*)((char*)this + 0xAA);
        if (count < 0x45)  // fixed max 69
        {
            Packet* destSlot = (Packet*)(*(int*)((char*)this + 0xA4) + count * sizeof(Packet));
            *destSlot = packet;
            uint16_t& flags = *(uint16_t*)((char*)destSlot + 0x06);
            flags |= 0x80;
            count++;
            FUN_00572a00(*(int*)((char*)this + 0xA4), count);
        }
    }
}