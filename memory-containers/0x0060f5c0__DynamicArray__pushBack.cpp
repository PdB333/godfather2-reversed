// FUNC_NAME: DynamicArray::pushBack

// Represents a dynamic array of 16-byte elements (two 8-byte values).
// Used by the EA EARS engine for various container structures.
// Offset layout:
//   +0x00: uint8_t* buffer    (pointer to memory block)
//   +0x04: int32_t  count     (number of elements stored)
//   +0x08: int32_t  capacity  (allocated capacity in number of elements)

class DynamicArray {
public:
    // Element type: an opaque 16-byte structure (two 8-byte values)
    struct Element {
        uint64_t data[2];
    };

    uint8_t* buffer;   // +0x00
    int32_t  count;    // +0x04
    int32_t  capacity; // +0x08

    // __thiscall: this in ECX, element reference in EDI (by convention)
    void pushBack(const Element& elem) {
        // Check if we need to grow the internal buffer
        if (count == capacity) {
            int32_t newCap = (capacity == 0) ? 1 : (capacity * 2);
            resize(newCap); // FUN_0060fc40
        }

        // Write the new element at the current end of the buffer
        Element* slot = reinterpret_cast<Element*>(buffer + count * sizeof(Element));
        count++;

        if (slot != nullptr) {
            slot->data[0] = elem.data[0];
            slot->data[1] = elem.data[1];
        }
    }

    // Called to reallocate the internal buffer (implemented elsewhere)
    void resize(int32_t newCapacity);
};