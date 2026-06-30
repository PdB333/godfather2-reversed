// FUNC_NAME: ArrayContainer::removeElement
// Function address: 0x00411f20
// Removes an element at the given index from a dynamic array.
// Object layout: data array starting at offset 0, 4-byte elements; count at offset 0x80.
// __fastcall calling convention: this in ECX (or equivalent), index in EDX.

typedef unsigned int uint32;

class ArrayContainer {
public:
    // +0x00: first element (4 bytes each)
    // +0x80: count (uint32)

    void removeElement(uint32 index) {
        uint32* countPtr = reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0x80);
        uint32 count = *countPtr;

        if (index < count) {
            if (index < count - 1) {
                // Shift remaining elements left by one
                int* data = reinterpret_cast<int*>(this);
                uint32 i = index;
                do {
                    data[i] = data[i + 1];
                    i++;
                } while (i < count - 1);
            }
            (*countPtr)--;
        }
    }
};