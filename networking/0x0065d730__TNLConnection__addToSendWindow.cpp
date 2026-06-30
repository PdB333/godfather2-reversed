// FUNC_NAME: TNLConnection::addToSendWindow
// Function address: 0x0065d730
// Role: Enqueues a data chunk into the send window circular buffer for reliable transmission.
// Uses a packet allocator to copy the chunk data, then stores pointer and size in the window.

struct SendWindow {
    void** entries;      // +0x00: array of 8-byte entries (pointer + size)
    int capacity;        // +0x04: number of slots
    int headIndex;       // +0x08: index of oldest slot
    int count;           // +0x0c: number of used slots
};

class PacketAllocator {
public:
    virtual void* allocate(); // returns a writable buffer
};

class TNLConnection {
    // +0x00: vtable pointer
    SendWindow* mSendWindow;   // +0x04
    PacketAllocator* mAllocator; // +0x08
    // ... other fields

    // chunk data is passed in registers in_EAX (unused?), unaff_retaddr = data pointer, unaff_EDI = size
    void addToSendWindow(void* chunkData, int chunkSize /* in EAX? */) {
        // instrumentation/debug call
        FUN_0065dda0(/* in_EAX */);

        // Check if window is not full and allocator is available
        if (mSendWindow->count < mSendWindow->capacity && mAllocator != nullptr) {
            // Allocate a buffer from the allocator
            void* dst = mAllocator->allocate();

            // Copy the chunk data into the allocated buffer
            memcpy(dst, chunkData, chunkSize);

            // Calculate write position (head + count, modulo capacity)
            int writeIdx = mSendWindow->headIndex + mSendWindow->count;
            if (writeIdx >= mSendWindow->capacity) {
                writeIdx -= mSendWindow->capacity;
            }

            // Store the buffer pointer and size in the slot (8 bytes per slot)
            mSendWindow->entries[writeIdx * 2] = dst;
            mSendWindow->entries[writeIdx * 2 + 1] = (void*)chunkSize; // store size as pointer-sized

            // Increment used count
            mSendWindow->count++;
        }
    }
};