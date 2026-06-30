// FUNC_NAME: EARS::ObjectAllocator::allocateNewElement
// Address: 0x00559d40
// This function allocates a new element from a dynamic array/growable buffer.
// The array structure (this) has the following layout:
//   +0x00: base pointer to array elements (each of size 0x70 = 112 bytes)
//   +0x04: current count (number of used elements)
//   +0x08: capacity (total allocated slots)
// The element type has a region at +0x40 through +0x68 (44 bytes) that is zeroed on allocation.
// If capacity is exhausted, the array is expanded (doubled, or to 1 if currently 0).
// Returns pointer to the newly allocated element.

typedef struct Element_s {
    char data[0x70];
} Element;

class ObjectAllocator {
private:
    Element* elements;     // +0x00
    int count;             // +0x04
    int capacity;          // +0x08

    // Internal reallocation function (address: 0x0055a0c0)
    void resize(int newCapacity);

public:
    // Allocates a new element, zeroes a portion of it, and returns its pointer.
    // __thiscall (this in ESI)
    Element* allocateNewElement() {
        // Check if we need to expand the array
        if (count == capacity) {
            int newCap = (capacity == 0) ? 1 : (capacity * 2);
            resize(newCap);
        }

        // Calculate pointer to next empty slot
        Element* newElement = elements + count;  // count * 0x70

        if (newElement != nullptr) {
            // Zero out the region from offset +0x40 to +0x68 (44 bytes)
            // This clears game-specific fields in the element.
            newElement->data[0x48] = 0;
            // ... (all dwords zeroed individually per original code)
            // Actually the decompiled does: clear +0x48,0x4C,0x50,0x54,0x58,0x5C,
            // then +0x40,0x44, then +0x60,0x64,0x68.
            // For clarity we can use memset or loop:
            // memset(&newElement->data[0x40], 0, 0x2C); // from +0x40 to +0x6C
            // But to be exact, we replicate the original pattern:
            *(int*)(&newElement->data[0x48]) = 0;
            *(int*)(&newElement->data[0x4C]) = 0;
            *(int*)(&newElement->data[0x50]) = 0;
            *(int*)(&newElement->data[0x54]) = 0;
            *(int*)(&newElement->data[0x58]) = 0;
            *(int*)(&newElement->data[0x5C]) = 0;
            *(int*)(&newElement->data[0x40]) = 0;
            *(int*)(&newElement->data[0x44]) = 0;
            *(int*)(&newElement->data[0x60]) = 0;
            *(int*)(&newElement->data[0x64]) = 0;
            *(int*)(&newElement->data[0x68]) = 0;
        }

        int oldCount = count;
        count++;
        return elements + oldCount;
    }
};