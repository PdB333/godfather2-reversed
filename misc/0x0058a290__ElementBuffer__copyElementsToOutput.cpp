// FUNC_NAME: ElementBuffer::copyElementsToOutput
// Function address: 0x0058a290
// Copies a range of 12-byte elements from an internal buffer to an output array.
// The start index is given; the end index is stored in a member (originally passed in ESI).
// The buffer pointer and current index are advanced accordingly.

class ElementBuffer {
public:
    // Offsets:
    // +0x50: m_pBuffer (pointer to array of 12-byte elements)
    // +0x54: m_currentIndex (int)
    // +0x58: m_endIndex (int) — assumed, originally in ESI
    int* m_pBuffer;          // +0x50
    int m_currentIndex;      // +0x54
    int m_endIndex;          // +0x58 (assumed)

    void copyElementsToOutput(int startIndex, int* output) {
        // Advance to the start index
        while (m_currentIndex < startIndex) {
            m_pBuffer += 3;   // each element is 3 ints (12 bytes)
            m_currentIndex++;
        }

        // Copy elements from current index to end index
        while (m_currentIndex < m_endIndex) {
            output[0] = m_pBuffer[0];
            output[1] = m_pBuffer[1];
            output[2] = m_pBuffer[2];
            m_pBuffer += 3;
            m_currentIndex++;
            output += 3;      // advance output pointer for next element
        }
    }
};