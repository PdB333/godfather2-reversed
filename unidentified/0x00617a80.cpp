// FUN_NAME: Vector::insertAt (address 0x00617a80)
// Member function of a dynamic array class storing 8-byte elements (2 ints).
// Fields:
//   +0x00: int* buffer       - pointer to contiguous array of 2-int elements
//   +0x04: int size          - number of elements currently stored
//   +0x08: int capacity      - allocated capacity (number of elements)
// Returns a pointer to the newly inserted element (which the caller should fill).

int* Vector::insertAt(int index)
{
    // Grow if capacity exhausted
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        grow(newCapacity); // FUN_00617d50 – reallocate buffer
    }

    // If inserting not at the end, shift existing elements right to create a gap
    if (index != size) {
        // Move the last element one slot to the right
        int* lastSlot = buffer + size * 2; // each element occupies 2 ints
        lastSlot[0] = lastSlot[-2];
        lastSlot[1] = lastSlot[-1];

        // Shift elements from size-1 down to index+1 to the right by one element
        int current = size;
        while (--current > index) {
            int* dst = buffer + current * 2;
            dst[0] = (buffer + (current - 1) * 2)[0];
            dst[1] = (buffer + (current - 1) * 2)[1];
        }
    }

    size++;
    return buffer + index * 2;
}