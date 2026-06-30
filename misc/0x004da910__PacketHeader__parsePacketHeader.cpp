// FUNC_NAME: PacketHeader::parsePacketHeader

#include <cstdint>

// Forward declarations for helper functions used in error handling
extern void errorHandler(int code);
extern void freePacketHeader(PacketHeader* header);

// Packet header structure: 0x00: type, 0x01: 8-byte data, 0x0C: field1, 0x10: field2, 0x14: next pointer
class PacketHeader {
public:
    uint8_t m_type;          // +0x00
    uint8_t m_data[8];       // +0x01
    uint32_t m_field1;       // +0x0C
    uint32_t m_field2;       // +0x10
    PacketHeader* m_next;    // +0x14

    // Magic packet constants
    static const uint32_t MAGIC_0 = 0xbadbadba;
    static const uint32_t MAGIC_1 = 0xbeefbeef;
    static const uint32_t MAGIC_2 = 0xeac15a55;
    static const uint32_t MAGIC_3 = 0x91100911;

    void parsePacketHeader(uint32_t* pBuffer); // __thiscall: this in ESI, pBuffer in EAX
};

void PacketHeader::parsePacketHeader(uint32_t* pBuffer)
{
    // Clear the next pointer
    this->m_next = nullptr;

    // Check if the input buffer matches the magic header pattern
    if (pBuffer[0] == MAGIC_0 && pBuffer[1] == MAGIC_1 && pBuffer[2] == MAGIC_2 && pBuffer[3] == MAGIC_3) {
        // Magic packet: set type to 1 and return
        this->m_type = 1;
        return;
    }

    // Regular packet: set type to 0x58 (packet type identifier)
    this->m_type = 0x58;

    // Copy 8 bytes from offset 8 of the input buffer into m_data (starting at offset 1)
    // During copy, check that each source byte is not above 0x7f (signed negative check)
    for (int i = 0; i < 8; i++) {
        uint8_t srcByte = reinterpret_cast<uint8_t*>(pBuffer)[8 + i];
        if (srcByte > 0x7f) {
            goto error;
        }
        this->m_data[i] = srcByte;
    }

    // After copying the 8-byte block, check the high byte of the first dword
    if ((pBuffer[0] & 0xFF000000) < 0x7F000001) {
        // Extract additional fields from the first 8 bytes of input
        // Set m_data[1] (byte at offset 2) to the 4th byte of the input
        this->m_data[1] = reinterpret_cast<uint8_t*>(pBuffer)[3];
        // Clear m_data[2] (byte at offset 3)
        this->m_data[2] = 0;
        // Extract 28-bit value from the second dword (low 28 bits)
        this->m_field2 = pBuffer[1] & 0xFFFFFFF;
        // Combine low 24 bits of first dword shifted left 4 with high 4 bits of second dword
        this->m_field1 = (pBuffer[0] & 0xFFFFFF) << 4 | (pBuffer[1] >> 0x1C);
        return;
    }

error:
    // Error: set type to 1 (error indicator)
    this->m_type = 1;
    // If there is a chained packet header, process it
    if (this->m_next != nullptr) {
        // Check if the chained header also has a next pointer (linked list)
        if (this->m_next->m_next != nullptr) {
            errorHandler(1);
        }
        freePacketHeader(this->m_next);
        this->m_next = nullptr;
    }
}