// FUNC_004a7a00: GrowableArray::reserve
// This function ensures that the internal buffer can hold at least 'newCapacity' elements,
// each of size 8 bytes. If the current capacity is less than requested, it allocates a new
// buffer, copies existing elements, and frees the old buffer.

struct GrowableArray {
    int* data;          // +0x00: pointer to array of 8-byte elements (e.g., pair of ints)
    int  count;         // +0x04: number of stored elements
    int  capacity;      // +0x08: allocated capacity (max elements before reallocation)

    void __thiscall reserve(uint newCapacity);
};

void __thiscall GrowableArray::reserve(uint newCapacity) {
    // Only reallocate if requested capacity exceeds current capacity
    if ((uint)capacity < newCapacity) {
        // Allocate new buffer: newCapacity * 8 bytes
        int* newData = (int*)FUN_009c8e80(newCapacity * 8);
        if (data != nullptr && count > 0) {
            // Copy existing elements (each 8 bytes) to the new buffer
            int* src = data;
            int* dst = newData;
            int elements = count;
            for (int i = 0; i < elements; i++) {
                // Copy two ints (8 bytes) per element
                dst[0] = src[0];
                dst[1] = src[1];
                src += 2;
                dst += 2;
            }
        }
        // Free old buffer if it existed
        if (data != nullptr) {
            FUN_009c8f10(data);
        }
        // Update pointer and capacity
        data = newData;
        capacity = newCapacity;
    }
}