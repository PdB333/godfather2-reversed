// FUNC_NAME: Vector::insert

// 0x006179b0 - Insert a new element at the specified index in a dynamic array of 8-byte elements.
// The vector structure (offset +0x00: data pointer, +0x04: count, +0x08: capacity).
// Returns a pointer to the slot where the caller should write the new element.
int* __thiscall Vector::insert(int insertIndex)
{
    int count = this->count;
    int capacity = this->capacity;

    // Expand if full
    if (count == capacity)
    {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        this->reallocate(newCapacity); // Calls FUN_00617cb0
    }

    int oldCount = this->count;

    // If inserting not at the end, shift elements to make room
    if (insertIndex != oldCount)
    {
        // Copy the last element one slot forward
        int* lastSlot = this->data + oldCount * 2; // each element is 2 ints
        lastSlot[0] = lastSlot[-2];
        lastSlot[1] = lastSlot[-1];

        // Shift remaining elements from oldCount-1 down to insertIndex+1
        int shiftIdx = oldCount;
        while (insertIndex < --shiftIdx)
        {
            int* currentSlot = this->data + shiftIdx * 2;
            currentSlot[0] = (currentSlot - 2)[0];
            currentSlot[1] = (currentSlot - 2)[1];
        }
    }

    // Update count
    this->count++;

    // Return pointer to empty slot at insertIndex
    return this->data + insertIndex * 2;
}