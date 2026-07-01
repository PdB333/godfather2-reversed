// FUNC_NAME: DynamicArray::pushBack

struct Element {
    uint64_t field0;      // +0x00: 8 bytes
    int32_t field1;       // +0x08: 4 bytes
    uint8_t field2;       // +0x0C: 1 byte
    uint8_t field3;       // +0x0D: 1 byte
    // remaining 30 bytes (0x2C - 0x0E) are not copied here
};

class DynamicArray {
public:
    Element* data;        // +0x00: pointer to element array
    int32_t size;         // +0x04: current number of elements
    int32_t capacity;     // +0x08: allocated capacity (in elements)

    void pushBack(const Element* newElement);
    void grow(int newCapacity); // FUN_00855960
};

void DynamicArray::pushBack(const Element* newElement) {
    // Check if we need to grow the array
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        grow(capacity); // Reallocate to new capacity
    }

    // Compute destination pointer for the new element
    Element* dest = data + size;
    size++;

    if (dest != nullptr) {
        // Copy the first 14 bytes of the element (fields up to +0x0D)
        dest->field0 = newElement->field0;
        dest->field1 = newElement->field1;
        dest->field2 = newElement->field2;
        dest->field3 = newElement->field3;

        // Post-insertion hook (e.g., update internal state)
        onElementAdded(); // FUN_00854270
    }
}