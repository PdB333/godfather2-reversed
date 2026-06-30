// FUNC_NAME: BufferWriter::writeTaggedData
// Address: 0x00628951
// Writes a 4-byte tag and a 4-byte data value into a growing buffer.
// Uses a context structure (passed via EDI) that contains a buffer descriptor and iteration state.
class BufferWriter {
public:
    // __thiscall
    void writeTaggedData();

private:
    // Offset +0x00: pointer to next data source (updated to point to internal data after write)
    void* m_nextSource;
    // Offset +0x04: counter for number of items written
    int m_itemCount;
    // Offset +0x08: pointer to buffer descriptor
    BufferDescriptor* m_bufferDesc;
    // Offset +0x0C: storage for the 4-byte data value to write
    int m_data;
};

struct BufferDescriptor {
    // Offset +0x08: current write pointer in the buffer
    char* m_writePtr;
    // Offset +0x10: pointer to buffer size/position info
    BufferInfo* m_bufferInfo;
};

struct BufferInfo {
    // Offset +0x20: cursor (number of bytes used)
    uint32_t m_cursor;
    // Offset +0x24: total buffer capacity
    uint32_t m_capacity;
};

// Dummy declarations for called functions
void handleBufferOverflow(); // FUN_00627360 – assertion/reallocation
int copyDataIntoBuffer(BufferDescriptor* desc, int* src, void* returnAddr); // FUN_00638920 – copies 4 bytes and returns written data

void BufferWriter::writeTaggedData() {
    BufferDescriptor* desc = m_bufferDesc;
    BufferInfo* info = desc->m_bufferInfo;

    // Check if there is room for at least 8 bytes (tag + data)
    if (info->m_cursor <= info->m_capacity) {
        handleBufferOverflow();
    }

    // Current write position
    char* writePos = desc->m_writePtr;

    // Write tag value 4 (likely a type identifier)
    *reinterpret_cast<int*>(writePos) = 4;

    // Copy the data stored at m_data into the buffer after the tag
    int result = copyDataIntoBuffer(desc, &m_data, reinterpret_cast<void*>(&returnAddr)); // returnAddr is the saved return address
    *reinterpret_cast<int*>(writePos + 4) = result;

    // Advance write pointer by 8 bytes
    desc->m_writePtr = writePos + 8;

    // Update context state: set first field to point to our internal data (seems like preparing for next call)
    m_nextSource = &m_data; // Equivalent to: *this = reinterpret_cast<int>(this + 3)
    m_itemCount++;
}