// FUNC_NAME: ArrayBase::removeAtIndex
// Address: 0x006ea530
// Role: Removes an element at a given index from a dynamic array, shifting subsequent elements left.

class ArrayBase {
public:
    int* data;      // +0x00: pointer to array of 4-byte elements
    int count;      // +0x04: number of elements currently stored
};

void __thiscall ArrayBase::removeAtIndex(unsigned int index) {
    // Shift elements left if the index is not the last one
    if (index < (unsigned int)(count - 1)) {
        do {
            data[index] = data[index + 1];
            index++;
        } while (index < (unsigned int)(count - 1));
    }
    // Decrement the element count
    count--;
}