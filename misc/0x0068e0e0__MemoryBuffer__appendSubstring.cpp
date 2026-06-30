// FUNC_NAME: MemoryBuffer::appendSubstring
// Address: 0x0068e0e0
// Role: Appends a fixed-length substring to a memory buffer with bounds checking.
// The buffer is represented by a structure containing:
//   +0x00: char* buffer (pointer to start of buffer)
//   +0x04: int writePos (current write offset)
//   +0x08: int bufferSize (total allocated size)
// The source is a substring descriptor:
//   +0x00: const char* source
//   +0x04: int length (number of characters to copy)

struct SubstringDescriptor {
    const char* source; // +0x00
    int length;         // +0x04
};

class MemoryBuffer {
    char* buffer;      // +0x00
    int writePos;      // +0x04
    int bufferSize;    // +0x08

public:
    void __thiscall appendSubstring(const SubstringDescriptor& desc) {
        int copyLen = desc.length;
        // Calculate remaining space in buffer
        size_t remaining = bufferSize - writePos;
        // Copy at most copyLen characters, ensuring null-termination
        _strncpy_s(buffer + writePos, remaining, desc.source, copyLen);
        // Advance write position by the number of bytes copied
        writePos += copyLen;
    }
};