// FUNC_NAME: StreamWriter::writeHeaderWithParam

// Function at 0x0046e3a0: Writes a header marker (global type descriptor), an integer,
// and a boolean into the stream buffer, then aligns the write position to the next 4-byte boundary.
// This is part of the EARS serialization layer.

// Buffer structure (simplified): contains current write position at offset +0x14
struct StreamBuffer {
    // ... other fields
    char* writePos;  // +0x14: pointer to current write location
};

// Stream writer object: first field is pointer to StreamBuffer
struct StreamWriter {
    StreamBuffer* m_buffer; // +0x00
};

// Global type marker written as first piece of data
extern void* g_TypeDescriptor;  // PTR_LAB_0110bad0

void __thiscall StreamWriter::writeHeaderWithParam(int value, bool flag) {
    StreamBuffer* buf = this->m_buffer;
    
    // Write the type marker pointer
    *(void**)(buf->writePos) = &g_TypeDescriptor;
    buf->writePos += 4;
    
    // Write the integer parameter
    *(int*)(buf->writePos) = value;
    buf->writePos += 4;
    
    // Write the boolean flag (as single byte)
    *(bool*)(buf->writePos) = flag;
    
    // Align write position to next 4-byte boundary (padding after bool)
    buf->writePos = (char*)(((uint)(buf->writePos + 4)) & 0xfffffffc);
}