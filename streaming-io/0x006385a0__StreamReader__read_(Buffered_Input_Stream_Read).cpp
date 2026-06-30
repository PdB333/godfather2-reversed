// FUNC_NAME: StreamReader::read (Buffered Input Stream Read)
// Address: 0x006385a0
// Role: Reads up to requestedSize bytes from a buffered stream into a destination buffer.
// Internal buffer is refilled on-demand via a callback function.
// Returns 0 on success, or the original requestedSize on error (incomplete read or stream error).

class BufferedStreamReader {
    // Structure layout:
    // +0x00: uint32_t m_remaining;      // Number of bytes left in the buffer
    // +0x04: uint8_t* m_current;       // Pointer to next byte to read from buffer
    // +0x08: FillFuncPtr m_fillFunc;   // Callback to refill buffer
    // +0x0C: void* m_fillContext;      // Context parameter for fill callback
    // (FillFuncPtr is a function pointer taking (uint32_t arg1, void* context, uint32_t* outSize) returning uint8_t*)

    typedef uint8_t* (__stdcall *FillFuncPtr)(uint32_t, void*, uint32_t*);

    uint32_t m_remaining;
    uint8_t* m_current;
    FillFuncPtr m_fillFunc;
    void* m_fillContext;

public:
    // __thiscall implied; 'this' in ESI
    uint32_t __thiscall read(void* destBuffer, uint32_t requestedSize) {
        uint32_t remainingToRead = requestedSize;

        if (requestedSize == 0) {
            return 0;
        }

        do {
            // If internal buffer is empty, refill it
            if (m_remaining == 0) {
                uint32_t newBufferSize;
                uint8_t* newBuffer = m_fillFunc(0, m_fillContext, &newBufferSize);

                // Check for fill failure
                if (newBuffer == nullptr || newBufferSize == 0) {
                    return requestedSize;  // Return original size to indicate error
                }

                // Temporarily skip the first byte to check for error sentinel
                m_current = newBuffer + 1;
                m_remaining = newBufferSize - 1;
                uint8_t firstByte = *newBuffer;

                // Sentinel byte 0xFF indicates stream error/end
                if (firstByte == 0xFF) {
                    return requestedSize;  // Error, return original size
                }

                // Restore buffer to include the first byte (it was only peeked)
                m_remaining = newBufferSize;
                m_current = newBuffer;
            }

            // Determine how many bytes to copy in this chunk
            uint32_t chunkSize = m_remaining;
            if (remainingToRead < m_remaining) {
                chunkSize = remainingToRead;
            }

            // Copy from internal buffer to destination
            memcpy(destBuffer, m_current, chunkSize);

            // Advance internal buffer pointers
            m_remaining -= chunkSize;
            m_current += chunkSize;

            // Advance destination pointer and decrement remaining count
            destBuffer = (void*)((uint8_t*)destBuffer + chunkSize);
            remainingToRead -= chunkSize;

        } while (remainingToRead != 0);

        return 0;  // Success, all bytes read
    }
};