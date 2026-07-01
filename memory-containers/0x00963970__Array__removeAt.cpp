// FUNC_NAME: Array::removeAt
// Function address: 0x00963970
// Reconstructed C++ for removing an element from a simple dynamic array.

class Array {
public:
    int* data;      // +0x00: pointer to contiguous array of 4-byte elements
    int size;       // +0x04: current number of elements

    // Removes the element at 'index', shifting subsequent elements left and decrementing size.
    void removeAt(unsigned int index) {
        // Only shift if element is not the last one
        if (index < size - 1) {
            do {
                data[index] = data[index + 1];
                ++index;
            } while (index < size - 1);
        }
        --size;
    }
};