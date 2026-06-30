// FUNC_NAME: BufferAllocator::appendBlock
// Address: 0x0056aab0
// This function manages a dynamic buffer for fixed-size (12-byte) blocks.
// It supports two modes: buffered (state 1) and delegated (state 2).
// Returns 'this' on success, null on failure.

class BufferAllocator {
public:
    // Mode flags
    enum Mode {
        MODE_BUFFERED = 1,
        MODE_DELEGATED = 2
    };

    // External allocation functions (global function pointers, e.g., from platform layer)
    typedef void* (*AllocFunc)(size_t size, int flags);
    typedef void* (*ReallocFunc)(void* ptr, size_t newSize, int flags);

    static AllocFunc s_allocFunc;   // DAT_0120554c
    static ReallocFunc s_reallocFunc; // DAT_01205550

    // Fields
    int mode;                 // +0x00: 1 = buffered, 2 = delegated
    int pad1;                 // +0x04: (unused in this function, likely alignment)
    int writePos;             // +0x08: current write position (offset in buffer)
    int capacity;             // +0x0C: total allocated capacity (bytes)
    union {
        char* buffer;         // +0x10: allocated buffer (mode 1)
        bool (*delegateFunc)(int context, void* data, size_t size); // +0x10: function pointer (mode 2)
    };
    int delegateContext;      // +0x14: context parameter for delegate (mode 2)
    // There might be more fields, but not used here.

    // Append a 12-byte block to the buffer.
    // Returns this on success, 0 on failure.
    void* appendBlock(void* block) {
        if (mode == MODE_BUFFERED) {
            // Buffered mode: manage internal buffer
            if (buffer == NULL) {
                // First allocation
                if (s_allocFunc == NULL) {
                    return NULL;
                }
                buffer = (char*)s_allocFunc(0x200, 0x30404);
                if (buffer == NULL) {
                    return NULL;
                }
                capacity = 0x200;
            }

            // Ensure enough space for 12 bytes
            if ((uint)(capacity - writePos) < 0xC) {
                int newCapacity = capacity + 0x200;
                if (s_reallocFunc == NULL) {
                    return NULL;
                }
                char* newBuffer = (char*)s_reallocFunc(buffer, newCapacity, 0x30404);
                if (newBuffer == NULL) {
                    return NULL;
                }
                buffer = newBuffer;
                capacity = newCapacity;
            }

            // Write 12 bytes at current position
            *(uint64*)(buffer + writePos) = *(uint64*)block;
            *(uint32*)(buffer + writePos + 8) = *(uint32*)((uint8*)block + 8);
            writePos += 0xC;
            return this;
        }
        else if (mode == MODE_DELEGATED) {
            // Delegated mode: call external function to process the block
            bool success = delegateFunc(delegateContext, block, 0xC);
            return success ? this : NULL;
        }
        // Unknown mode
        return NULL;
    }
};