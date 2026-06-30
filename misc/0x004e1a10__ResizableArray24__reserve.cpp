// FUNC_NAME: ResizableArray24::reserve
class ResizableArray24 {
public:
    // The array element size is 0x18 (24) bytes
    // Offsets relative to this:
    // +0x00: data pointer (int*)
    // +0x04: count (int)
    // +0x08: capacity (int)

    void reserve(uint newCapacity) {
        // Only resize if requested capacity is larger than current
        if (newCapacity <= (uint)this->capacity) {
            return;
        }

        // Allocate new block: newCapacity * elementSize (0x18)
        void* newData = malloc(newCapacity * 0x18);
        if (newData == nullptr) {
            return; // allocation failure, leave unchanged (original code doesn't check)
        }

        // Copy existing elements from old to new
        uint currentCount = (uint)this->count;
        if (currentCount > 0) {
            // Copy each 24-byte element
            for (uint i = 0; i < currentCount; i++) {
                // Source pointer: old data + i * 0x18
                uint8_t* src = (uint8_t*)this->data + i * 0x18;
                // Destination pointer: newData + i * 0x18
                uint8_t* dst = (uint8_t*)newData + i * 0x18;
                // Copy 3 * 8 bytes (24 bytes) using two 8-byte loads
                *(uint64_t*)dst = *(uint64_t*)src;
                *(uint64_t*)(dst + 8) = *(uint64_t*)(src + 8);
                *(uint64_t*)(dst + 16) = *(uint64_t*)(src + 16);
            }
        }

        // Free old data
        free(this->data);

        // Update members
        this->data = (int*)newData;
        this->capacity = (int)newCapacity;
    }

private:
    int* data;      // +0x00
    int count;      // +0x04
    int capacity;   // +0x08
};