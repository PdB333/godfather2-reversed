// FUNC_NAME: Array::reserve

// Function address: 0x005effe0
// Identified role: Reserves capacity for a dynamic array (int-based) in EA EARS engine.
// Class layout: data pointer at +0x00, size at +0x04, capacity at +0x08
// Uses custom allocator wrappers: MemAlloc (0x009c8e80) and MemFree (0x009c8f10)

class Array {
public:
    int* data;     // +0x00 : pointer to element buffer
    int size;      // +0x04 : current number of elements
    int capacity;  // +0x08 : allocated capacity (in elements)
};

void Array::reserve(uint newCapacity) {
    if (capacity < newCapacity) {
        // Allocate new buffer (size = newCapacity * sizeof(int) = newCapacity * 4)
        int* newData = (int*)MemAlloc(newCapacity * 4);
        if (data != nullptr) {
            // Copy existing elements
            uint i = 0;
            int* src = data;
            int* dst = newData;
            if (size != 0) {
                do {
                    // Safety check against null destination (redundant but present in original)
                    if (dst != nullptr) {
                        *dst = *src;
                    }
                    i++;
                    src++;
                    dst++;
                } while (i < static_cast<uint>(size));
            }
            // Free the old buffer
            MemFree(data);
        }
        data = newData;
        capacity = static_cast<int>(newCapacity);
    }
}