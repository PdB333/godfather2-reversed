// Xbox PDB: AptAnimationPoolData::addActionBack
// FUNC_NAME: pushSendPacket
// Function at 0x005a64e0: Adds a packet to the send queue (ring buffer) and optionally processes it.
// Global g_packetManager points to a structure with a ring buffer at offsets +0x1400 (head) and +0x1404 (tail).
// Each slot is 0x14 bytes: +0x00: flags (set to 0), +0x04: param3 (e.g., sequence), +0x08: connectionId, +0x0C: packetData pointer.

extern uint32_t* g_packetManager; // DAT_0119a9cc
extern uint32_t* g_nullPacketSentinel; // DAT_0119cbbc (likely 0 or special value)

void pushSendPacket(uint32_t connectionId, uint32_t* packetData, uint32_t param3)
{
    uint32_t* base = g_packetManager;
    uint32_t tail = *(uint32_t*)(base + 0x1404 / 4); // offset 0x1404
    uint32_t nextSlot = tail + 0x14;
    uint32_t* headPtr = (uint32_t*)(base + 0x1400 / 4); // offset 0x1400

    // Wrap around if next slot equals head
    if ((uint32_t*)nextSlot == headPtr) {
        nextSlot = (uint32_t)base; // wrap to start of buffer
    }

    // If the next slot is not the head (i.e., buffer not full)
    if (nextSlot != *headPtr) {
        // Assertions: tail must be within valid range
        if (tail < (uint32_t)base) {
            FUN_0059bf00(); // likely assertion failure
        }
        if (headPtr <= (uint32_t*)tail) {
            FUN_0059bf00(); // likely assertion failure
        }

        bool isNotSentinel = (packetData != g_nullPacketSentinel);

        // Write packet entry at current tail slot
        *(uint32_t*)(tail + 0x00) = 0; // flags
        *(uint32_t*)(tail + 0x08) = connectionId;
        *(uint32_t*)(tail + 0x0C) = (uint32_t)packetData;

        // Process packet if not sentinel and not a special type
        if (isNotSentinel) {
            uint32_t packetType = *packetData & 0x7FFF;
            if (packetType != 0x19) {
                // Check if bit 15 is clear OR type is not 0xB, 0x18, 0x17
                if (((*packetData >> 0xF) & 1) == 0 ||
                    (packetType != 0xB && packetType != 0x18 && packetType != 0x17)) {
                    FUN_0059c230(packetData); // process packet (e.g., encrypt/compress)
                }
            }
        }

        // Write param3 at offset +0x04
        *(uint32_t*)(tail + 0x04) = param3;

        // Advance tail to next slot
        *(uint32_t*)(base + 0x1404 / 4) = nextSlot;
    }
}