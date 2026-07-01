// FUNC_NAME: SortedArray::insertSortedElement
// Address: 0x008322a0
// Insert an element into a sorted dynamic array.
// The array is stored as: pointer at +0x08, size at +0x0C, capacity at +0x10.
// After insertion, qsort is called using compare function at 0x00833690 if size > 1.

#include <cstdlib>

class SortedArray {
public:
    int* elements;   // +0x08
    int size;        // +0x0C
    int capacity;    // +0x10

    // Growth helper at 0x0082a890
    void growArray(int newCapacity);

    void insertSortedElement(int value) {
        if (size == capacity) {
            // Double capacity (minimum 1)
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            growArray(newCapacity);
        }

        int* target = elements + size;
        size++;
        if (target != nullptr) {
            *target = value;
        }

        if (size > 1) {
            // Sort using compare function at 0x00833690
            qsort(elements, size, sizeof(int), (int (*)(const void*, const void*))0x00833690);
        }
    }
};