// FUNC_NAME: HistoryBuffer::addEntry
// Address: 0x008e6b60
// Role: Adds a 16-byte entry to a bounded history buffer. Resizes the buffer (doubles capacity) when full,
// and ensures the number of entries never exceeds 12 by removing the oldest (front) entry.

#include <cstdint>

// 16-byte structure stored in the buffer (offset +0x00 to +0x0F)
struct HistoryEntry {
    uint32_t data[4]; // or appropriate members
};

// Class representing a bounded history buffer (fixed max 12 entries)
// Offsets (relative to this):
//   +0x58: HistoryEntry* buffer (pointer to heap-allocated array)
//   +0x5C: int32_t size (current number of entries)
//   +0x60: int32_t capacity (allocated entry count)
class HistoryBuffer {
public:
    HistoryEntry* buffer;   // +0x58
    int32_t size;           // +0x5C
    int32_t capacity;       // +0x60

    // Reallocate buffer to hold 'newCapacity' entries (size preserved)
    void reallocateBuffer(int32_t newCapacity);   // FUN_008defe0

    // Remove the first (oldest) entry and shift the rest forward (size decremented)
    void removeFirstEntry();                      // FUN_008e5e60

    void addEntry(const HistoryEntry& entry) {
        // If the buffer is full, grow capacity
        if (size == capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity *= 2;
            }
            reallocateBuffer(capacity);
        }

        // Copy the 16-byte entry to the end of the buffer
        HistoryEntry* dest = &buffer[size];
        *dest = entry; // struct copy (16 bytes)

        size++;

        // Enforce maximum of 12 entries; remove oldest if exceeded
        while (size > 12) {
            removeFirstEntry(); // removes entry at index 0, decrements size
        }
    }
};