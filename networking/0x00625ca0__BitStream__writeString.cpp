// FUNC_NAME: BitStream::writeString
// Function at 0x00625ca0: Writes a string into the bitstream with a type tag (4) and a reference to the string data.
// The string is stored as a 4-byte tag followed by a 4-byte offset/handle returned by writeStringData.
// If the string is null, writes a zero tag (0) instead.

struct BitStreamBufferInfo {
    uint32_t mCapacity; // +0x20
    uint32_t mSize;     // +0x24
};

class BitStream {
public:
    // +0x00: vtable or other fields
    // +0x08: current write pointer (uint8_t**)
    uint8_t** mWritePtr; // offset +0x08
    // +0x10: pointer to buffer info
    BitStreamBufferInfo* mBufferInfo; // offset +0x10

    void writeString(const char* str);
    void growBuffer(); // FUN_00627360
    uint32_t writeStringData(const char* str, int length); // FUN_00638920
};

void BitStream::writeString(const char* str) {
    if (str == nullptr) {
        // Write a null tag (0) and advance pointer
        **mWritePtr = 0;
        *mWritePtr += 8; // advance by 8 bytes (tag + value)
        return;
    }

    // Calculate string length
    const char* p = str;
    while (*p != '\0') {
        p++;
    }
    int length = p - str; // strlen

    // Check if buffer has room for the string data (tag + offset + actual string)
    // The condition checks if capacity <= size, meaning we need to grow
    if (mBufferInfo->mCapacity <= mBufferInfo->mSize) {
        growBuffer();
    }

    // Write the string tag (4) at current write position
    uint32_t* writePos = reinterpret_cast<uint32_t*>(*mWritePtr);
    writePos[0] = 4; // type tag for string

    // Write the string data and get the offset/handle
    uint32_t stringHandle = writeStringData(str, length);
    writePos[1] = stringHandle;

    // Advance write pointer by 8 bytes (tag + handle)
    *mWritePtr += 8;
}