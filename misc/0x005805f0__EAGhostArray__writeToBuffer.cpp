// FUNC_NAME: EAGhostArray::writeToBuffer
// Address: 0x005805f0
// __thiscall

#include <cstring>

class EAGhostArray {
    unsigned short m_count;   // +0x0A: number of valid items
    int m_size;               // +0x0C: total items (capacity)
    char m_items[0];          // +0x10: array of 16-byte items (actual size = m_size * 16)

public:
    // Serializes the array into the provided output buffer.
    // maxItems: maximum number of items the output buffer can hold.
    // outputBuffer: pointer to a flat buffer (must be at least 16 + m_size*16 bytes).
    // Returns 1 on success, 0 if maxItems < m_count.
    int writeToBuffer(unsigned int maxItems, void* outputBuffer) {
        // Check if the output buffer is large enough
        if (maxItems < this->m_count) {
            return 0;
        }

        // Write header: first 8 bytes zero
        *(unsigned int*)outputBuffer = 0;
        *((unsigned int*)outputBuffer + 1) = 0;

        // Header flags: byte at offset 8 = 1, byte at offset 9 = 0
        *((unsigned char*)outputBuffer + 8) = 1;
        *((unsigned char*)outputBuffer + 9) = 0;

        // Header: word at offset 10 = m_count, dword at offset 12 = m_size
        *((unsigned short*)((char*)outputBuffer + 10)) = this->m_count;
        *((unsigned int*)((char*)outputBuffer + 12)) = this->m_size;

        // Copy the array data (16 bytes per item) to offset 16
        memcpy((char*)outputBuffer + 16, this->m_items, this->m_size * 16);

        return 1;
    }
};