// FUNC_NAME: StreamBuffer::hasDataToProcess
// Function address: 0x0090d7b0
// Checks if there is pending data in a stream buffer that can be processed.
// Returns true if bit 5 of flags is clear, currentCount is non-zero and <= maxCount.

class StreamBuffer {
public:
    uint32_t mFlags;       // +0x00: Bitfield flags (bit 5 = blocked/disabled)
    uint32_t mMaxCount;    // +0x04: Maximum items allowed
    uint32_t mCurrentCount; // +0x08: Number of items currently buffered

    bool hasDataToProcess() {
        // Check if not blocked (bit 5 clear) and there are items to process
        // within the allowed limit
        return !(mFlags & (1 << 5)) &&       // Bit 5 not set
               mCurrentCount != 0 &&        // Some items available
               mCurrentCount <= mMaxCount;  // Not exceeding max
    }
};