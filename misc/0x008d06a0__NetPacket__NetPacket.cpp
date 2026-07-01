// FUNC_NAME: NetPacket::NetPacket
// Constructor for network packet class. Sets up vtable, debug markers, initial flags.
// offset 0x1c/0x70: packet header size?
// offset 0x1d/0x74: payload size?
// magic numbers: debug sentinels (badbadba, beefbeef, eac15a55, 91100911)
// offset 0x27/0x9C: short version/count set to 2
// offset 0x9E: byte set to 0
// Bit 0x20000000 at offset 0x18/0x60 indicates a flag (maybe "isAllocated").
// If global packet table exists (gPacketTable), copy into object at +0x3C (size 0x8000).

#include <cstdint>
#include <cstring>

// Forward declarations
extern uint32_t gDefaultHeaderSize;   // DAT_00d5ddec
extern uint32_t gDefaultPayloadSize;  // DAT_00d5d934
extern void* gPacketTable;           // DAT_0120e93c
extern void* PacketTableConstructor(void* dst, void* src, uint32_t size); // FUN_00408900

class NetPacket {
public:
    // Vtable pointer (PTR_FUN_00d7ceec)
    void* vtable;

    // +0x04 to +0x38: other members, not touched in this constructor
    // Sizes assume 4-byte alignment throughout.

    // +0x3C (offset 0xf): pointer to another vtable or inner structure
    void* innerVtable1;

    // +0x48 (offset 0x12): pointer to another vtable
    void* innerVtable2;

    // Flags at offset 0x18 includes bit 0x20000000
    uint32_t flags;

    // Various fields at +0x19..0x1b cleared later
    uint32_t field_0x64; // +0x19*4
    uint32_t field_0x68; // +0x1a*4
    uint32_t field_0x6c; // +0x1b*4

    // +0x1c (28): header size
    uint32_t headerSize;

    // +0x1d (29): payload size
    uint32_t payloadSize;

    // Magic debug sentinels (initialized to debug values, then cleared)
    uint32_t magic1; // +0x1e: 0xbadbadba
    uint32_t magic2; // +0x1f: 0xbeefbeef
    uint32_t magic3; // +0x20: 0xeac15a55
    uint32_t magic4; // +0x21: 0x91100911

    // +0x22..0x26: zeros
    uint32_t pad88;   // +0x22
    uint32_t pad8c;   // +0x23
    uint32_t pad90;   // +0x24
    uint32_t pad94;   // +0x25
    uint32_t pad98;   // +0x26

    // +0x27 (at byte offset 0x9C): short version
    uint16_t version; // set to 2

    // +0x9E: byte flag
    uint8_t byte9E;   // set to 0

    // +0x9F: padding omitted

    // Constructor
    NetPacket(void* allocatorOrParent) {
        // Call base class constructor
        // FUN_008cfb70(allocatorOrParent);
        // Assume it initializes some base structure
        BaseConstructor(allocatorOrParent);

        // Set initial parameters from globals
        headerSize  = gDefaultHeaderSize;   // DAT_00d5ddec
        payloadSize = gDefaultPayloadSize;  // DAT_00d5d934

        // Set vtable and inner vtables
        vtable        = (void*)0x00d7ceec; // PTR_FUN_00d7ceec
        innerVtable1  = (void*)0x00d7cedc; // PTR_LAB_00d7cedc
        innerVtable2  = (void*)0x00d7ced8; // PTR_LAB_00d7ced8

        // Set debug sentinels
        magic1 = 0xbadbadba;
        magic2 = 0xbeefbeef;
        magic3 = 0xeac15a55;
        magic4 = 0x91100911;

        // Clear future fields
        pad88 = 0;
        pad8c = 0;
        pad90 = 0;
        pad94 = 0;
        pad98 = 0;

        // Set version and byte
        version = 2;
        byte9E  = 0;

        // Re-clear magic fields (debug markers become zero)
        magic4 = 0;
        magic3 = 0;
        magic2 = 0;
        magic1 = 0;

        // Clear fields at 0x19..0x1b
        field_0x64 = 0;
        field_0x68 = 0;
        field_0x6c = 0;

        // Set flag: bit 0x20000000
        flags |= 0x20000000;

        // If a global packet table exists, copy it into the inner buffer
        if (gPacketTable != nullptr) {
            // FUN_00408900 copies 0x8000 bytes from gPacketTable to this+0x3C
            PacketTableConstructor(&innerVtable1, gPacketTable, 0x8000);
        }
    }

private:
    void BaseConstructor(void* allocatorOrParent);
};