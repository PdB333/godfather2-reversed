// FUNC_NAME: StreamReader::readAligned64_32AndCall

class StreamReader {
public:
    // +0x18: uint8_t* readPos;  // current read position in buffer
    uint8_t* readPos;  // actually at offset +0x18 of the object

    // Typedef for callback: receives two halves of a 64-bit value and an extra 32-bit value
    using ReadTripletCallback = void (*)(uint32_t low32, uint32_t high32, uint32_t extra);

    // Reads an aligned 8+4 byte chunk and calls the supplied callback.
    // Reads 12 bytes total starting at the next 4-byte boundary from current position.
    void readAligned64_32AndCall(ReadTripletCallback* callbackOut) {
        // Align the current read pointer to the next 4-byte boundary
        uint8_t* aligned = reinterpret_cast<uint8_t*>((reinterpret_cast<uint32_t>(this->readPos) + 3) & ~3);
        this->readPos = aligned;  // store aligned pointer

        // Read the 64-bit value (8 bytes) from the aligned address
        uint64_t value64 = *reinterpret_cast<uint64_t*>(aligned);

        // Advance pointer by 8 (the 64-bit value)
        this->readPos = aligned + 8;

        // Read the 32-bit value that follows (next 4 bytes)
        uint32_t extra = *reinterpret_cast<uint32_t*>(this->readPos);

        // Advance pointer by 4 (the 32-bit value) so total advance is 12 bytes from aligned start
        this->readPos = aligned + 12;

        // Split the 64-bit value into low and high 32-bit parts
        uint32_t low32  = static_cast<uint32_t>(value64);
        uint32_t high32 = static_cast<uint32_t>(value64 >> 32);

        // Invoke the callback stored at the caller-supplied pointer
        (*callbackOut)(low32, high32, extra);
    }
};