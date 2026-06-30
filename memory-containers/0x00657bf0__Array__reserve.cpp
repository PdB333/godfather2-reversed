// FUNC_NAME: Array::reserve
// Function address: 0x00657bf0
// Role: Resize a dynamic array to at least the given capacity, aligning capacity to a 16-element boundary.
// The array stores 4-byte elements (e.g., pointers or ints). 
// Offsets: this+0x4 = capacity (number of elements), this+0x8 = buffer pointer (void*).
// Uses malloc/free from the EARS allocator.

struct Array {
    // +0x00: possibly other fields (not accessed here)
    uint32_t capacity; // +0x04
    void*    buffer;   // +0x08
};

void Array::reserve(uint32_t newCapacity)
{
    // Only grow if we need more space
    if (this->capacity < newCapacity)
    {
        // Round up to a multiple of 16 elements (each 4 bytes)
        uint32_t alignedCapacity = newCapacity + (0x10 - (newCapacity & 0xf));
        uint32_t oldElementCount = this->capacity;

        void* newBuffer = malloc(alignedCapacity * 4);
        void* oldBuffer = this->buffer;

        // Temporarily set the new buffer, copy old data, then restore for free
        this->buffer = newBuffer;
        memcpy(this->buffer, oldBuffer, oldElementCount * 4);

        this->buffer = oldBuffer;
        free(oldBuffer);

        this->buffer = newBuffer;
        this->capacity = alignedCapacity;
    }
}