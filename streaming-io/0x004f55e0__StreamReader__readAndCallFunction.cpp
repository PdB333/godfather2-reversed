// FUNC_NAME: StreamReader::readAndCallFunction

class StreamReader {
public:
    uint8_t* mReadPtr; // +0x18

    // Reads a packed message from the stream and invokes a callback.
    // The message format: first 4-byte word (functionId or context) at current read position,
    // then the remaining 6 words (24 bytes) are read from the next 4-byte-aligned position.
    // The callback receives these 7 words as (uint32_t, uint32_t, uint32_t, uint64_t, uint32_t, uint32_t).
    void readAndCallFunction(void (**callback)(uint32_t, uint32_t, uint32_t, uint64_t, uint32_t, uint32_t)) {
        // Read the first word from the current (possibly unaligned) buffer position
        uint32_t firstWord = *(uint32_t*)mReadPtr;

        // Align pointer to the next 4-byte boundary after skipping 7 bytes?
        // This is a peculiar alignment: (ptr + 7) & ~3 advances by at least 4 bytes,
        // ensuring subsequent reads are from 4-byte aligned addresses.
        uint32_t* alignedPtr = (uint32_t*)((uint32_t)(mReadPtr) + 7U & 0xFFFFFFFCu);
        mReadPtr = (uint8_t*)alignedPtr;

        // Read the next 6 words from the aligned buffer
        uint32_t arg2 = alignedPtr[0]; // +0
        uint32_t arg3 = alignedPtr[1]; // +4
        uint64_t arg4 = *(uint64_t*)(alignedPtr + 2); // +8 (8 bytes)
        uint32_t arg5 = alignedPtr[4]; // +16
        uint32_t arg6 = alignedPtr[5]; // +20

        // Invoke the callback with all arguments
        (*callback)(firstWord, arg2, arg3, arg4, arg5, arg6);
    }
};