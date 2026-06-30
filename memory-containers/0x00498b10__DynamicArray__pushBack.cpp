// FUNC_NAME: DynamicArray::pushBack

struct Element {
    uint64_t field0;  // 8 bytes
    uint32_t field1;  // 4 bytes
};

class DynamicArray {
    // Offset: +0x00
    Element* data;
    // Offset: +0x04
    int size;
    // Offset: +0x08
    int capacity;

    // Reallocate internal buffer to new capacity
    void reallocate(int newCapacity);

public:
    // Add element at end; element passed via EDI (caller convention)
    void pushBack(Element* elem);
};

void DynamicArray::pushBack(Element* elem) {
    int currentCapacity = capacity;

    // Grow if full
    if (size == currentCapacity) {
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        reallocate(newCapacity);
    }

    // Write element at current end
    Element* dest = &data[size];
    dest->field0 = elem->field0;
    dest->field1 = elem->field1;
    size++;
}