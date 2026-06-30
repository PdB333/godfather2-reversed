// FUNC_NAME: PacketBuilder::buildPacket
// Address: 0x00597730
// Role: Constructs a 0x4C-byte packet structure with header and payload copy.
// The function writes a 16-bit flag, a 32-bit message ID, another 16-bit value,
// then copies the header area into the payload area. Returns total packet size.
// The global vtable at DAT_01205590 points to a stream writer interface.

#include <cstdint>

// struct representing the packet layout
struct Packet {
    uint8_t unknown_00[2];   // +0x00
    uint16_t flag;            // +0x02
    uint32_t messageId;       // +0x04
    uint16_t extra;           // +0x08
    uint8_t payload[0x40];    // +0x0C to +0x4B
};

// Global stream writer vtable (offset 0x10 is write/append function)
extern void** gStreamWriterVtable;

uint32_t __thiscall PacketBuilder::buildPacket(Packet* thisPacket, uint32_t param_2, uint16_t param_3) {
    // param_3 is used to compute a masked value (not stored in this function)
    uint32_t masked = (param_3 * 0x10 + 0x0C) & 0xFFFF;
    // Local variables for temporary storage
    uint32_t local_val0 = 0x201;      // Message ID constant
    uint16_t local_val1 = 2;          // Some flag/length
    uint16_t local_val2 = 2;          // Another flag

    // First call to stream writer (maybe initializes or writes something)
    // Arguments are unclear, might rely on ECX (thisPacket) or global state
    ((void (*)())(gStreamWriterVtable[4]))();   // offset 0x10

    // Write 2-byte flag at offset +0x02
    ((void (*)(void*, void*, int))(gStreamWriterVtable[4]))(&thisPacket->flag, &local_val1, 2);

    // Write 4-byte message ID at offset +0x04 (contents of local_val0)
    ((void (*)(void*, void*, int))(gStreamWriterVtable[4]))(&thisPacket->messageId, &local_val0, 4);

    // Write 2-byte extra at offset +0x08
    ((void (*)(void*, void*, int))(gStreamWriterVtable[4]))(&thisPacket->extra, &local_val2, 2);

    // Copy 0x40 bytes from the header area (starting at +0x02) into payload area (+0x0C)
    ((void (*)(void*, void*, int))(gStreamWriterVtable[4]))(&thisPacket->payload[0], &thisPacket->flag, 0x40);

    // Return total packet size (0x4C = 76 bytes)
    return 0x4C;
}