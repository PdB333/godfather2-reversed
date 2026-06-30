// FUNC_NAME: PacketParser::parsePacketType
// Function address: 0x005d3660
// Parses a packet buffer to identify a known packet type by searching for a magic number (0x9876543)
// and extracting two 32-bit values that are compared against a global table of known types.
// If a match is found, stores the type index in the connection structure at offset 0xB8.

#include <cstdint>

// Global table of known packet type pairs (two 32-bit values per type)
extern const uint32_t g_knownPacketTypes[2][2]; // e.g., { {0x..., 0x...}, {0x..., 0x...} }

// Structure representing the connection state (pointed to by this->m_pConnection)
struct ConnectionInfo {
    uint8_t pad8[8];          // +0x00
    uint32_t* pCurrentPos;    // +0x08 (pointer to current position in buffer)
    uint8_t padB0[0xB8-0x0C]; // +0x0C to +0xB7
    int32_t packetType;       // +0xB8 (0 or 1 for known types, -1 if unknown)
};

// Class representing a packet buffer parser
class PacketParser {
public:
    uint32_t* m_pBuffer;      // +0x00 (base pointer to buffer)
    uint32_t m_size;          // +0x0C (size of buffer in bytes)
    uint32_t m_offset;        // +0x10 (current read offset)
    ConnectionInfo* m_pConnection; // +0x1C (pointer to connection state)

    int32_t parsePacketType();
};

int32_t PacketParser::parsePacketType() {
    // Save original offset
    uint32_t originalOffset = m_offset;

    // Skip first 4 bytes (possibly a header length or padding)
    m_offset += 4;

    // Set current position pointer in connection info
    m_pConnection->pCurrentPos = m_pBuffer + m_offset;

    // Initialize packet type to unknown
    m_pConnection->packetType = 0;

    // Search for magic number 0x9876543 in the buffer
    uint32_t magic = 0x9876543;
    while (m_offset < m_size) {
        if (m_pBuffer[m_offset] == magic) {
            // Found magic; skip the magic itself (4 bytes) and read the next 24 bytes? Actually skip 0x18 (24) bytes total?
            // The code adds 0x18 to offset after checking magic, then reads two 4-byte values at offset+0 and offset+4.
            m_offset += 0x18; // Skip magic + 20 bytes? Actually magic is 4 bytes, then 20 bytes padding? Not sure.
            uint32_t value1 = *(uint32_t*)((uint8_t*)m_pBuffer + m_offset);
            uint32_t value2 = *(uint32_t*)((uint8_t*)m_pBuffer + m_offset + 4);
            m_offset += 8; // Advance past the two values

            // Compare against known types
            for (int32_t i = 0; i < 2; i++) {
                if (value1 == g_knownPacketTypes[i][0] && value2 == g_knownPacketTypes[i][1]) {
                    m_pConnection->packetType = i;
                    break;
                }
            }
            break;
        }
        m_offset += 4; // Move to next 4-byte word
    }

    // Restore original offset (the caller will continue parsing from the original position)
    m_offset = originalOffset;
    return 1;
}