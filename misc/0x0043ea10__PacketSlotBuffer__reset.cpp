// FUNC_NAME: PacketSlotBuffer::reset
// Function at 0x0043ea10: Resets the buffer to its initial state. If the current count exceeds the maximum (15), the allocated data buffer is freed. This appears to be a safety cleanup before resetting the buffer for reuse.
// Structure offsets:
//   +0x04: char* mData        - pointer to allocated buffer
//   +0x14: int mCurrentCount  - number of items currently stored
//   +0x18: unsigned int mMaxCount - maximum capacity (set to 15)

class PacketSlotBuffer {
public:
    char* mData;             // +0x04
    int mCurrentCount;       // +0x14
    unsigned int mMaxCount;  // +0x18

    // __thiscall on ecx
    void reset() {
        if (mCurrentCount > 15) {
            // Free the overflowed data (function at 0x009c8eb0 is a deallocation routine)
            FUN_009c8eb0(mData);
        }
        mMaxCount = 15;      // Reset capacity to default (16 slots: 0..15)
        mCurrentCount = 0;   // Clear count
        mData = 0;           // Null the pointer
    }
};