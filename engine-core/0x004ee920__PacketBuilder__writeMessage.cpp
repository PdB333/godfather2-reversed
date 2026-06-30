// FUNC_NAME: PacketBuilder::writeMessage

class PacketBuilder {
public:
    char* m_writePtr; // +0x14: current write position in the buffer

    void writeMessage(
        uint32_t messageType,        // param_1
        const void* data,            // param_2
        size_t dataSize,             // param_3
        uint32_t alignment,          // param_4 (used as both value and padding offset)
        const uint64_t* hash,        // param_5: pointer to 16-byte hash (two 64-bit values)
        uint32_t field6,             // param_6
        uint32_t field7,             // param_7
        uint32_t field8,             // param_8
        uint32_t field9,             // param_9
        bool flag                    // param_10
    );
};

void PacketBuilder::writeMessage(
    uint32_t messageType,
    const void* data,
    size_t dataSize,
    uint32_t alignment,
    const uint64_t* hash,
    uint32_t field6,
    uint32_t field7,
    uint32_t field8,
    uint32_t field9,
    bool flag
)
{
    // --- Packet header (12 bytes) ---
    *(uint32_t*)m_writePtr = messageType;
    m_writePtr += 4;

    *(size_t*)m_writePtr = dataSize;
    m_writePtr += sizeof(size_t); // 4 bytes on x86

    *(uint32_t*)m_writePtr = alignment;
    m_writePtr += 4;

    // --- Align to next 'alignment'-byte boundary (rounds up, adds extra alignment bytes) ---
    // Formula: (~(alignment - 1)) & (m_writePtr + alignment + 3)
    m_writePtr = (char*)( (uint32_t)(~(alignment - 1)) & ( (uint32_t)m_writePtr + alignment + 3) );

    // --- Copy the payload data ---
    memcpy(m_writePtr, data, dataSize);
    m_writePtr += dataSize;

    // --- Align to 16-byte boundary after the data ---
    // Pad dataSize to next 4-byte boundary, then add 0xf and mask off lower 4 bits
    uint32_t paddedSize = (dataSize + 3) & ~3;
    m_writePtr = (char*)( ((uint32_t)m_writePtr + paddedSize + 0xf) & ~0xf );

    // --- Write 16-byte hash (GUID / sequence ID) ---
    *(uint64_t*)m_writePtr = hash[0];
    *(uint64_t*)(m_writePtr + 8) = hash[1];

    // --- Write additional fields after the hash at fixed offsets ---
    // field6 at offset 0x10 from start of hash
    *(uint32_t*)(m_writePtr + 0x10) = field6;

    // Move write pointer to offset 0x14, write field7
    m_writePtr += 0x14;
    *(uint32_t*)m_writePtr = field7;
    m_writePtr += 4;

    // Write field8 at current position, then field9 at +4, advance by 8
    *(uint32_t*)m_writePtr = field8;
    *(uint32_t*)(m_writePtr + 4) = field9;
    m_writePtr += 8;

    // Write boolean flag
    *(bool*)m_writePtr = flag;

    // Align to 4-byte boundary
    m_writePtr = (char*)( ((uint32_t)m_writePtr + 3) & ~3 );
}