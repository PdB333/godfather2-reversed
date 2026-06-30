// FUNC_NAME: DynamicArray::pushBack16ByteElement
// Address: 0x0060f5c0
// Role: Push a 16-byte element (two uint64) into a dynamic array with automatic growth.
// The array layout: offset 0 = pointer to data (Element*), offset 4 = size (int), offset 8 = capacity (int)
// Element size = 0x10 (16 bytes)

struct Element {
    uint64_t first;   // +0x00
    uint64_t second;  // +0x08
};

class DynamicArray {
public:
    Element* m_data;    // +0x00
    int m_size;         // +0x04
    int m_capacity;     // +0x08

    // __thiscall: this in ECX
    void pushBack(const Element& src) {
        int size = m_size;
        int cap = m_capacity;

        if (size == cap) {
            // Grow the array: double capacity, or set to 1 if current is 0
            int newCap;
            if (cap == 0) {
                newCap = 1;
            } else {
                newCap = cap * 2;
            }
            reallocate(newCap);  // 0x0060fc40
        }

        // Compute destination pointer: base + (size * 0x10)
        Element* dst = m_data + m_size;
        // Increment size
        m_size++;

        // Copy 16 bytes from source to destination
        if (dst != nullptr) {
            dst->first = src.first;
            dst->second = src.second;
        }
    }

private:
    void reallocate(int newCapacity); // defined elsewhere (0x0060fc40)
};