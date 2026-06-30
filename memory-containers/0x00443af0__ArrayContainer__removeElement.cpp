// FUNC_NAME: ArrayContainer::removeElement

struct ArrayContainer {
    int* data;  // +0x00: pointer to array of 8-byte elements
    int count;  // +0x04: number of elements currently stored
};

// 0x00443af0 - Remove an element from a compact 8-byte-per-element array by index.
// Shifts subsequent elements left by one (each element is 2 ints) and decrements count.
void __fastcall ArrayContainer::removeElement(int index) {
    // Only shift if index is not the last element
    if (index < this->count - 1) {
        int* base = this->data;
        do {
            base[index * 2] = base[index * 2 + 2];
            base[index * 2 + 1] = base[index * 2 + 3];
            ++index;
        } while (index < this->count - 1);
    }
    this->count--;
}