// FUNC_NAME: NetPacket::NetPacket
// Address: 0x004c4430
// Zero-initializes all fields of a NetPacket structure.
// The structure appears to be a network packet header followed by a data array.
// Offsets are documented relative to start of object.

class NetPacket {
public:
    // Packet header fields
    int packetSequence;          // +0x00
    int packetAck;               // +0x04
    int packetSendTime;          // +0x08
    int field_C;                 // +0x0C (unknown)
    int field_10;                // +0x10 (unknown)
    int field_14;                // +0x14 (unknown)
    byte packetFlags;            // +0x18
    byte packetChecksum;         // +0x19
    short packetHeaderShort;     // +0x1A (e.g., size or type)
    int field_1C;                // +0x1C (unknown)
    int field_20;                // +0x20 (unknown)
    int field_24;                // +0x24 (unknown)
    int field_28;                // +0x28 (unknown)
    int field_2C;                // +0x2C (unknown)
    int field_34;                // +0x34 (unknown, skip 0x30?)
    int field_38;                // +0x38 (unknown)
    byte extraFlag;              // +0x3C
    int field_40;                // +0x40 (unknown)
    // gap from +0x44 to +0x64C (uninitialized here)
    int dataSlots[18];           // +0x650 (indices 0x194-0x1A5)
};

// Static assertion to ensure correct size (optional)
// static_assert(sizeof(NetPacket) == 0x698, "NetPacket size mismatch");

void __fastcall NetPacket::NetPacket(NetPacket* this) {
    // Zero header fields
    this->packetSequence = 0;
    this->packetAck = 0;
    this->packetSendTime = 0;
    this->field_C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    // Zero byte and short fields
    this->packetFlags = 0;
    this->packetChecksum = 0;
    this->packetHeaderShort = 0;
    // Continue with remaining header ints
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;
    this->field_28 = 0;
    this->field_2C = 0;
    this->field_34 = 0;          // +0x34
    this->field_38 = 0;          // +0x38
    this->extraFlag = 0;         // +0x3C
    this->field_40 = 0;          // +0x40
    // Zero the data slot array (18 ints starting at +0x650)
    for (int i = 0; i < 18; i++) {
        this->dataSlots[i] = 0;
    }
}