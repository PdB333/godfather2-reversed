// FUNC_NAME: SomeContainer::updateWritePointer

class SomeContainer {
public:
    // +0x14: m_dataStart (int*) - pointer to start of data buffer
    // +0x18: m_writePointer (int*) - current write position
    // +0x1c: m_bufferEnd (int*) - pointer to end of buffer
    // +0x20: m_writeIndex (int) - index for writing (element count)
    // +0x28: m_readPointer (int*) - current read position
    // +0x2c: m_capacity (unsigned short) - maximum number of elements

    void updateWritePointer() {
        // Compute new write pointer: bufferEnd - 8 + writeIndex * 8
        // This suggests each element is 8 bytes, and the write pointer points to the element at (writeIndex - 1) from the end?
        m_writePointer = m_bufferEnd - 8 + m_writeIndex * 8;

        // Check if capacity exceeds 4096 and the number of used elements (based on 24-byte elements) is less than 4096
        // The expression (m_dataStart - m_readPointer) / 0x18 + 1 likely calculates the count of elements between read and start
        // If both conditions hold, trigger a resize/reallocation
        if ((m_capacity > 0x1000) && ((m_dataStart - m_readPointer) / 0x18 + 1 < 0x1000)) {
            resizeBuffer(); // FUN_00635c10 - likely reallocates or adjusts buffer
        }
    }

private:
    void resizeBuffer(); // defined elsewhere
};