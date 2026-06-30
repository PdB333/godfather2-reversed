// FUNC_NAME: BufferWriter::appendString
// Function address: 0x0068e0e0
// Role: Append a fixed-length string to a character buffer, advancing the write offset.
// Class layout:
//   +0x00: char* buffer      // base address of the buffer
//   +0x04: int   offset       // current write position (bytes from buffer start)
//   +0x08: int   capacity     // total size of the buffer

struct StringRef {
    const char* str;   // +0x00
    size_t     length; // +0x04 (4 bytes on x86)
};

void __thiscall BufferWriter::appendString(const StringRef* src) {
    size_t count = src->length;                   // param_2[1]
    // Safe copy: destination = buffer + offset, destination size = capacity - offset
    strncpy_s(buffer + offset, capacity - offset, src->str, count);
    offset += count;
}