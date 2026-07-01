// FUNC_NAME: ArrayBase::removeAt
// Function address: 0x0084a1e0
// Removes the element at the given index from a dynamic array of 8-byte elements.
// The array is stored as a pointer to the buffer (offset 0) and a count (offset 4).

struct ArrayBase {
    void* buffer; // +0x00: pointer to array of 8-byte elements
    unsigned int count; // +0x04: number of elements currently stored
};

void __thiscall ArrayBase::removeAt(unsigned int index)
{
    // Shift all elements after 'index' left by one slot (8 bytes)
    if (index < this->count - 1)
    {
        do {
            // Copy the next element (8 bytes) into the current position
            unsigned int* src = (unsigned int*)((char*)this->buffer + (index + 1) * 8);
            unsigned int* dst = (unsigned int*)((char*)this->buffer + index * 8);
            dst[0] = src[0];
            dst[1] = src[1];
            index++;
        } while (index < this->count - 1);
    }

    // Decrease the element count
    this->count--;
}