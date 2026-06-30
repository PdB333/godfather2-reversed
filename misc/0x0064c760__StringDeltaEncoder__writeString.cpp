// FUNC_NAME: StringDeltaEncoder::writeString
// Address: 0x0064c760
// This function encodes a string using delta compression against the previously stored string.
// A bit marker (1 if common prefix > 2, else 0) is written, then the common prefix length (8 bits) and suffix (raw), or the whole string.
// The internal string is updated to the new string for subsequent calls.

class StringDeltaEncoder {
public:
    // +0x0c: pointer to bit buffer for marker bits
    uint8_t* m_pBitBuffer; // offset 0x0C
    // +0x10: capacity of bit buffer in bytes (allocated size)
    uint32_t m_bitBufferCapacityBytes; // offset 0x10
    // +0x14: flag indicating if buffer can be grown (dynamic)
    bool m_bDynamic; // offset 0x14
    // +0x18: current bit position in the bit buffer (for writing markers)
    int32_t m_bitPosition; // offset 0x18
    // +0x1c: flag set when reallocation fails or buffer is full (non-growable)
    uint8_t m_resizeFlag; // offset 0x1C
    // +0x2c: duplicate of m_bitCapacity (used internally)
    uint32_t m_duplicateBitCapacity; // offset 0x2C
    // +0x30: current bit capacity (max bits that can be written without reallocation)
    uint32_t m_bitCapacity; // offset 0x30
    // +0x38: previous string buffer (null-terminated, max length unknown, likely <=255)
    char m_previousString[?]; // offset 0x38 (size unclear, but at least 256)
};

// Default string used when pString is null (points to global DAT_00e2f044, likely an empty string)
extern const char g_defaultString;

// Forward declarations of helpers (from other functions)
void writeBits(int bitCount, const void* data); // FUN_0064b810
void writeRawBytes(const void* data, int length); // FUN_0065afb0

void __thiscall StringDeltaEncoder::writeString(const char* pString, uint32_t stringLen) {
    // Use default empty string if pString is NULL
    if (pString == nullptr) {
        pString = &g_defaultString; // DAT_00e2f044
    }

    uint8_t commonPrefixLen = 0; // bVar4

    // Find common prefix with the previous string (stored at this+0x38)
    if (static_cast<uint8_t>(stringLen) != 0) {
        do {
            // Check if characters match and current character is not null terminator
            if (m_previousString[commonPrefixLen] != pString[commonPrefixLen] ||
                pString[commonPrefixLen] == '\0') {
                break;
            }
            commonPrefixLen++;
        } while (commonPrefixLen < (uint8_t)stringLen);
    }

    // Copy the suffix (non-common part) to previous string
    uint32_t lenLowByte = stringLen & 0xFF; // uVar5
    uint32_t commonLen = commonPrefixLen;    // uVar6
    strncpy(&m_previousString[commonLen], &pString[commonLen], lenLowByte - commonLen);
    m_previousString[lenLowByte] = '\0';

    // Determine marker bit: 1 if common prefix > 2, else 0
    bool markerBit = (commonPrefixLen > 2);
    uint8_t markerByte = markerBit ? 1 : 0;

    // Check if bit buffer needs expansion
    if (m_bitCapacity < (uint32_t)(m_bitPosition + 1)) {
        // Compute new buffer size (in bytes) = ceil(current capacity bits / 8) + 1500
        uint32_t newSizeBytes = ((m_bitCapacity + 8) >> 3) + 0x5DC; // 0x5DC = 1500
        if (m_bitBufferCapacityBytes < newSizeBytes) {
            if (m_bDynamic) {
                // Reallocate buffer
                m_bitBufferCapacityBytes = newSizeBytes;
                m_pBitBuffer = (uint8_t*)realloc(m_pBitBuffer, newSizeBytes);
                m_duplicateBitCapacity = newSizeBytes * 8;
                m_bitCapacity = newSizeBytes * 8;
                markerByte = (uint8_t)markerBit; // reload marker (not really needed)
                goto writeMarker;
            } else {
                // Non-dynamic: just increase capacity (but buffer not reallocated)
                m_bitBufferCapacityBytes = newSizeBytes;
            }
        }
        // Mark that a resize was attempted (even if not needed or not possible)
        m_resizeFlag = 1;
    } else {
writeMarker:
        // Set the bit at current bit position
        if (markerBit) {
            m_pBitBuffer[m_bitPosition >> 3] |= (1 << (m_bitPosition & 7));
        } else {
            m_pBitBuffer[m_bitPosition >> 3] &= ~(1 << (m_bitPosition & 7));
        }
        m_bitPosition++;

        if (markerBit) {
            // Write common prefix length (8 bits)
            uint32_t tempLen = commonLen;
            writeBits(8, &tempLen);
            // Write the suffix (raw bytes)
            writeRawBytes(&pString[commonLen], lenLowByte - commonLen);
            return;
        }
    }

    // If marker bit is false (or we fell through due to capacity issue), write the whole string
    writeRawBytes(pString, lenLowByte);
}