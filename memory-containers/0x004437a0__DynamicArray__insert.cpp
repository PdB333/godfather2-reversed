// FUNC_NAME: DynamicArray::insert
// Address: 0x004437a0
// Inserts a new element (8 bytes) at the given index, shifting later elements right.
// Returns pointer to the newly inserted slot.
// Structure: (this+0x00): data pointer, (this+0x04): element count, (this+0x08): capacity

void* __thiscall DynamicArray::insert(int index)
{
    int count = this->count;           // offset +0x04
    int capacity = this->capacity;     // offset +0x08

    // Grow array if full (double capacity, or set to 1 if currently 0)
    if (count == capacity)
    {
        int newCap = (capacity == 0) ? 1 : (capacity * 2);
        this->resize(newCap);          // calls FUN_00443fa0
    }

    // If inserting before the end, shift elements to make room
    if (index != count)
    {
        // Copy the last element one slot forward (to the new end position)
        int* newEnd = this->data + count * 2; // each element is 2 ints (8 bytes)
        if (newEnd != 0)
        {
            newEnd[0] = newEnd[-2];    // copy first field of last element
            newEnd[1] = newEnd[-1];    // copy second field
        }

        // Shift elements from (count-1) down to (index+1) to the right
        int i = count;
        while (--i > index)
        {
            int* cur = this->data + i * 2;
            cur[0] = cur[-2];          // copy from element i-1
            cur[1] = cur[-1];
        }

        this->count = count + 1;
        return this->data + index * 2;
    }
    else
    {
        // Appending at end: just increment count and return pointer
        this->count = count + 1;
        return this->data + index * 2;
    }
}