// FUNC_NAME: DynamicArray::removeAt
// Function at 0x006027d0: Removes element at given index from a dynamic array (elements are 16 bytes), shifts subsequent elements left, and decrements the size.

struct DynamicArray {
    int* data;  // +0x00: pointer to element storage
    int size;   // +0x04: current number of elements
    // capacity likely elsewhere (e.g., +0x08)
};

void __thiscall DynamicArray::removeAt(uint32 index) {
    if (index < static_cast<uint32>(size - 1)) {
        int offset = index << 4; // index * 16 bytes per element
        do {
            unsigned long long* dst = reinterpret_cast<unsigned long long*>(data + offset);
            unsigned long long* src = reinterpret_cast<unsigned long long*>(data + offset + 0x10);
            // Copy element at i+1 to element at i (16 bytes)
            *dst = *src;               // first 8 bytes
            dst[1] = src[1];           // second 8 bytes
            index++;
            offset += 0x10;
        } while (index < static_cast<uint32>(size - 1));
    }
    size--;
}