// FUNC_NAME: NetSession::clearPendingAckFlags
class NetSession {
public:
    int m_packetCount;      // +0x14
    PacketEntry* m_packets; // +0x10

    void clearPendingAckFlags();
};

struct PacketEntry {
    uint8_t data[0x2c];     // unknown fields
    uint32_t flags;         // +0x2c
    // total size 0x30 (48 bytes)
};

void NetSession::clearPendingAckFlags() {
    int count = m_packetCount;
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            uint32_t* flags = &m_packets[i].flags;
            *flags &= 0x3FFFFFFF; // clear top 2 bits (ack/resend flags)
        }
    }
}