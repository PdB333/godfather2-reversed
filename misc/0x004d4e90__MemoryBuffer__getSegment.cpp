// FUNC_NAME: MemoryBuffer::getSegment
// Functions: 0x004d4e90 - Retrieves a contiguous segment from a memory buffer.

// Represents a buffer with current position and validity flag.
class MemoryBuffer {
public:
    struct Segment {
        uint32_t start;      // +0x00 Current offset (position) in the buffer
        uint32_t remaining;  // +0x04 Bytes available from start to end
        uint32_t totalSize;  // +0x08 Total size of the buffer
        uint32_t success;    // +0x0C Flag: 0 on success, nonzero on failure
    };

    // Attempts to get the remaining segment from this buffer.
    Segment* __thiscall getSegment(Segment* outSegment) {
        // Check if the buffer is valid (non-zero flag at +0x04)
        if (this->valid != 0) {
            uint32_t currentPos = this->currentPos;  // +0x00
            // Get total buffer size (e.g., from an external pool or internal state)
            uint32_t totalSize = getBufferSize(currentPos);
            if ((totalSize != 0) && (currentPos < totalSize)) {
                // Success: fill output segment and advance internal position
                outSegment->start = currentPos;
                outSegment->remaining = totalSize - currentPos;
                outSegment->totalSize = totalSize;
                outSegment->success = 0;
                // Advance the buffer's write/read position
                advancePosition(currentPos, totalSize - currentPos);
                return outSegment;
            }
        }
        // Failure: zero out the segment
        outSegment->start = 0;
        outSegment->remaining = 0;
        outSegment->totalSize = 0;
        outSegment->success = 0;
        return outSegment;
    }

private:
    uint32_t currentPos;  // +0x00 Current offset in the buffer
    uint32_t valid;       // +0x04 Non-zero if the buffer is allocated/valid

    // Helper: returns the total size of the buffer given the current position.
    // (Implementation details abstracted; may involve a separate pool or header)
    static uint32_t __stdcall getBufferSize(uint32_t /*param*/); // FUN_004d4e20

    // Helper: updates the buffer's internal position after consuming a segment.
    static void __stdcall advancePosition(uint32_t pos, uint32_t size); // FUN_004d3c40
};