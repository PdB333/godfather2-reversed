// FUNC_NAME: DynamicArray::addElement
// Address: 0x006aedf0
// Role: Adds a 12-byte element to a dynamic array, resizing if needed.

struct Element {
    uint64_t data0; // +0x00, 8 bytes
    uint32_t data1; // +0x08, 4 bytes
};

class DynamicArray {
public:
    Element* data;   // +0x00
    int size;        // +0x04
    int capacity;    // +0x08

    void addElement(const Element& element) {
        if (size == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity); // calls FUN_006ad900
        }
        Element* dest = data + size;
        size++;
        if (dest != nullptr) {
            *dest = element;
        }
    }

private:
    void resize(int newCapacity); // FUN_006ad900
};