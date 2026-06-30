// FUNC_NAME: DynamicArray::setCapacity
// Address: 0x004c2e30
// Role: Ensures the internal buffer has at least the specified capacity. Grows if needed, never shrinks.

struct DynamicArray {
    uint32* data;      // +0x00
    uint32 size;       // +0x04
    uint32 capacity;   // +0x08

    void setCapacity(uint32 newCapacity);
};

void DynamicArray::setCapacity(uint32 newCapacity) {
    if (capacity < newCapacity) {
        // Allocate new block (4 bytes per element)
        uint32* newData = (uint32*)malloc(newCapacity * sizeof(uint32));
        
        if (data != nullptr) {
            // Copy existing elements
            uint32 i = 0;
            uint32* src = data;
            uint32* dst = newData;
            if (size != 0) {
                do {
                    if (dst != nullptr) { // always true, but kept for fidelity
                        *dst = *src;
                    }
                    i++;
                    src++;
                    dst++;
                } while (i < size);
            }
            // Free old buffer
            free(data);
        }
        
        // Update pointers and capacity
        data = newData;
        capacity = newCapacity;
    }
}