// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity) // __thiscall, this in ESI
{
    // Class layout (assuming int* for 'this'):
    // +0x00: int* data;     // pointer to element array
    // +0x04: int size;      // current number of elements
    // +0x08: int capacity;  // allocated capacity (number of elements)

    // Only reallocate if requested capacity exceeds current capacity
    if (newCapacity > this->capacity) {
        // Allocate new buffer: each element is 8 bytes
        int* newData = (int*)FUN_009c8e80(newCapacity * 8); // Allocation function

        // Copy existing elements if any and if size > 0
        if (this->data != 0) {
            uint i = 0;
            int* src = this->data;
            int* dst = newData;
            if (this->size != 0) {
                do {
                    if (dst != 0) {
                        *dst = *src;                    // Copy first 4 bytes
                        dst[1] = *(src + 4);            // Copy next 4 bytes (8-byte element)
                    }
                    i++;
                    src += 2; // advance by 2 ints (8 bytes)
                    dst += 2;
                } while (i < (uint)this->size);
            }
            // Free old buffer
            FUN_009c8f10(this->data); // Deallocation function
        }

        // Update pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
    return;
}