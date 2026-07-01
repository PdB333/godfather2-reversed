// FUNC_NAME: Array::pushBack
// Address: 0x007a1890
// Role: Appends a 16-byte element to a dynamic array, expanding capacity if necessary. 
//   The container structure: [0] = data pointer, [4] = size, [8] = capacity.
void __thiscall Array::pushBack(void *this, const uint64_t element[2])
{
    int size = *(int *)((char *)this + 4);
    int capacity = *(int *)((char *)this + 8);

    if (size == capacity) {
        // Resize: double capacity (or use 1 if originally 0)
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        // Internal resize function (likely reallocates)
        FUN_0079af20(newCapacity); // Assume void grow(int newCapacity) 
    }

    // Calculate insertion position and copy 16 bytes
    uint64_t *dst = (uint64_t *)(*(int *)this + size * 0x10);
    *(int *)((char *)this + 4) = size + 1; // Increment size

    if (dst != nullptr) {
        dst[0] = element[0];
        dst[1] = element[1];
    }
}