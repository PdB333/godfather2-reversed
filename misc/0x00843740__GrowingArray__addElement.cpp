// FUNC_NAME: GrowingArray::addElement
int *__fastcall GrowingArray::addElement(GrowingArray *this)
{
    int size = this->m_size;          // this+0x4
    int capacity = this->m_capacity;   // this+0x8

    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate internal buffer to new capacity (FUN_008431d0)
        GrowingArray::grow(this, capacity);
    }

    int newIndex = this->m_size;        // Current size becomes index
    uint8_t *newElement = this->m_data + newIndex * 8;  // Each element is 8 bytes

    // Zero-initialize the new element (two 4-byte fields)
    *(int32_t *)newElement = 0;
    *(int32_t *)(newElement + 4) = 0;

    this->m_size = newIndex + 1;        // Increment size

    return (int *)newElement;           // Return pointer to newly added element
}