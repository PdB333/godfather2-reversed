// FUNC_NAME: DynamicArray::insertFront

// 0x006687e0: Insert 'count' zeroed elements at the front of a dynamic array.
// Shifts existing elements right and grows if needed. Returns 0 on success,
// or non-zero if the grow (realloc) failed (from FUN_00667740).

struct DynamicArray {
    int size;        // +0x00: current number of elements
    int capacity;    // +0x04: allocated element count
    int* data;       // +0x0C: pointer to element buffer (each element 4 bytes)
};

int __thiscall DynamicArray::insertFront(int count)
{
    if (count <= 0) {
        return 0;
    }

    // Need to grow the buffer if capacity insufficient
    if (this->capacity < this->size + count) {
        int result = grow(); // FUN_00667740 (realloc/grow)
        if (result != 0) {
            return result;
        }
    }

    this->size += count;
    int oldSize = this->size - count; // Actually: newSize - count
    int newSize = this->size;

    int* data = this->data;

    // Shift existing elements right by 'count' positions (prepend)
    if (count <= newSize - 1) {
        int numElements = oldSize; // number of old elements to move
        int* dst = &data[newSize - 1];
        int* src = &data[oldSize - 1];
        while (numElements > 0) {
            *dst-- = *src--;
            numElements--;
        }
    }

    // Zero the newly inserted front elements
    int* clearStart = data;
    for (int i = 0; i < count; i++) {
        clearStart[i] = 0;
    }

    return 0;
}