// FUNC_NAME: DataArray::insert
void* DataArray::insert(uint index)
{
    // this: in_EAX, structure: +0 = data (array of 12-byte elements), +4 = size, +8 = capacity
    if (size == capacity) {
        if (capacity == 0) {
            reallocate(1);
        } else {
            reallocate(capacity * 2);
        }
    }

    if (index < size) {
        // Shift elements to the right by one position
        int shiftCount = size - index;
        for (int i = shiftCount; i > 0; i--) {
            // Copy element at index+shiftCount-1 to index+shiftCount
            char* src = (char*)data + (index + i - 1) * 12;
            char* dst = (char*)data + (index + i) * 12;
            memcpy(dst, src, 12);
        }
    }

    // Clear the new slot
    char* newSlot = (char*)data + index * 12;
    memset(newSlot, 0, 12);

    size++;
    return (void*)newSlot;
}