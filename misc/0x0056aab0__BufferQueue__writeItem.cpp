// FUNC_NAME: BufferQueue::writeItem
// Function address: 0x0056aab0
// Role: Writes a 12-byte data item into a buffer queue. Supports two modes:
//   - state 1: Dynamic buffer with allocation/reallocation.
//   - state 2: Callback-based processing.

#include <cstdint>

// External allocators (likely from EARS memory manager)
extern void* (*g_allocator)(uint32_t size, uint32_t flags);          // DAT_0120554c
extern void* (*g_reallocator)(void* ptr, uint32_t newSize, uint32_t flags); // DAT_01205550

class BufferQueue {
public:
    // Field offsets (in bytes from 'this')
    int32_t state;               // +0x00   // 1 = buffer mode, 2 = callback mode
    int32_t field_4;             // +0x04   // Unused?
    int32_t field_8;             // +0x08   // Unused?
    int32_t writeOffset;         // +0x0C   // Current write position in buffer (index 3)
    int32_t bufferCapacity;      // +0x10   // Allocated size of buffer (index 4)
    void*   bufferPtr;           // +0x14   // Pointer to dynamic buffer (index 5, used in state 1)
    int32_t field_18;            // +0x18   // Unused? (index 6)
    int32_t callbackContext;     // +0x1C   // Context for callback mode (index 7)

    // Function pointer for callback mode (overlaps with bufferPtr in union sense, but at same offset)
    // In state 2, bufferPtr is interpreted as a function pointer.
    void* getCallbackPtr() const { return bufferPtr; }
    void setCallbackPtr(void* p) { bufferPtr = p; }

    // Write an item (12 bytes) from 'data' into the queue.
    // Returns 'this' on success, nullptr on failure.
    __thiscall int32_t* writeItem(const uint8_t* data); // param_1 is data pointer
};

// Implementation
int32_t* BufferQueue::writeItem(const uint8_t* data) {
    if (state != 1) {
        // State is not buffer mode
        if (state != 2) {
            // Unknown state, return failure
            return nullptr;
        }
        // Callback mode: invoke bufferPtr as a function, passing context, data, and size 12.
        auto callback = (int32_t (*)(int32_t, const uint8_t*, uint32_t))bufferPtr;
        uint8_t result = callback(callbackContext, data, 0xC);
        // Return this if callback succeeded (non-zero), else null
        return (result != 0) ? this : nullptr;
    }

    // State 1: buffer mode
    if (bufferPtr == nullptr) {
        // Allocate initial buffer of 0x200 bytes
        if (g_allocator == nullptr) {
            bufferPtr = nullptr;
        } else {
            bufferPtr = g_allocator(0x200, 0x30404);
        }
        if (bufferPtr == nullptr) {
            return nullptr;
        }
        bufferCapacity = 0x200;
    }

    // Check if there is space for 12 bytes
    if ((uint32_t)(bufferCapacity - writeOffset) < 0xC) {
        // Not enough space, reallocate to add 0x200 bytes
        int32_t newCapacity = bufferCapacity + 0x200;
        if (g_reallocator == nullptr) {
            return nullptr;
        }
        void* newPtr = g_reallocator(bufferPtr, newCapacity, 0x30404);
        if (newPtr == nullptr) {
            return nullptr;
        }
        bufferPtr = newPtr;
        bufferCapacity = newCapacity;
    }

    // Write the 12 bytes (two parts: 8 bytes + 4 bytes) at current write position
    uint8_t* dest = (uint8_t*)bufferPtr + writeOffset;
    *reinterpret_cast<uint64_t*>(dest) = *reinterpret_cast<const uint64_t*>(data);
    *reinterpret_cast<uint32_t*>(dest + 8) = *reinterpret_cast<const uint32_t*>(data + 8);
    writeOffset += 0xC;

    return this;
}