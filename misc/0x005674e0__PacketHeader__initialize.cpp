// FUNC_NAME: PacketHeader::initialize
// Address: 0x005674e0
// Role: Initializes a packet header with default values for type, flags, and sequence number.

class PacketHeader {
public:
    uint32_t mPacketType;  // +0x10
    uint8_t  mFlags;       // +0x14
    int32_t  mSequence;    // +0x18
};

void PacketHeader::initialize() {
    mPacketType = 9;                              // +0x10
    mFlags = 2;                                   // +0x14
    mSequence = 0xFFFFFF23;                        // +0x18 ( -221 )
}