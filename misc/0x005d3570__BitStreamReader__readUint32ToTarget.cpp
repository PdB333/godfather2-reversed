// FUNC_NAME: BitStreamReader::readUint32ToTarget
// Function address: 0x005d3570
// Reads a 32-bit little-endian integer from an internal buffer, stores it at a target object's offset +0xCC,
// and returns a packed value: high 24 bits = original value >> 8, low 8 bits = (value > 0x18) ? 1 : 0.
// This is likely part of a packet deserializer, reading a sequence number or timestamp.

class BitStreamReader {
public:
    // +0x00: pointer to data buffer
    char *m_pBuffer;
    // +0x04: current read offset (byte offset)
    int m_offset;
    // +0x1C: pointer to target object (e.g., connection/session) that receives the value
    void *m_pTarget; // offset 7*4=28=0x1C

    // Reads 4 bytes from m_pBuffer at m_offset, advances m_offset by 4,
    // stores the value at (m_pTarget + 0xCC), and returns the packed result.
    int readUint32ToTarget() {
        // Read 4 bytes (little-endian) from m_pBuffer + m_offset
        m_offset += 4;
        int oldOffset = m_offset;
        char byte0 = *(m_pBuffer + oldOffset);
        char byte1 = *(m_pBuffer + oldOffset + 1);
        char byte2 = *(m_pBuffer + oldOffset + 2);
        char byte3 = *(m_pBuffer + oldOffset + 3);
        m_offset = oldOffset + 4; // equivalent to +=4 already done

        int value = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;

        // Store at target + 0xCC
        *(int*)((char*)m_pTarget + 0xCC) = value;

        // Return (value & 0xFFFFFF00) | (value > 0x18 ? 1 : 0)
        int flag = (value > 0x18) ? 1 : 0;
        return (value & 0xFFFFFF00) | flag;
    }
};