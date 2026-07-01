// FUNC_NAME: EarsArray::pushBack
// Address: 0x0095e9a0
// Role: Adds an element (32 bytes) to the dynamic array, growing capacity if needed. Copies the element in two 16-byte halves.

class EarsArray {
public:
    char* data;       // +0x00: pointer to element buffer
    int   size;       // +0x04: current number of elements
    int   capacity;   // +0x08: allocated element capacity

    // Internal: reallocate the buffer to new capacity (calls realloc or new allocation)
    void reallocate(int newCapacity); // Address: 0x0095e090

    // Internal: copy 16 bytes from source to destination
    static void copy16Bytes(void* dst, void* src); // Address: 0x004d3b50
};

void EarsArray::pushBack(void* element) {
    // element is a pointer to a 32-byte block, likely a pair of 16-byte structures.

    int curSize = this->size;
    int curCap = this->capacity;

    // Check if we need to grow
    if (curSize == curCap) {
        int newCap;
        if (curCap == 0) {
            newCap = 1;
        } else {
            newCap = curCap * 2;
        }
        this->reallocate(newCap); // grow buffer
    }

    // Current size becomes the index where the new element will be placed
    int index = this->size;
    this->size = index + 1; // increment after use

    // Compute destination address
    char* dest = this->data + index * 0x20;

    // Only copy if destination is non-null (should always be true after realloc)
    if (dest != nullptr) {
        // Copy first 16 bytes from element
        this->copy16Bytes(dest, element);
        // Copy second 16 bytes from element + 0x10
        this->copy16Bytes(dest + 0x10, (char*)element + 0x10);
    }
}