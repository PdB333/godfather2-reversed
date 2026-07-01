// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(unsigned int newCapacity)
{
    // Object layout: this->data (int*), this->count (int), this->capacity (int)
    // Offsets: +0x00 data, +0x04 count, +0x08 capacity
    if ((unsigned int)this->capacity < newCapacity) {
        // Allocate new block of 4-byte elements
        int* newData = (int*)FUN_009c8e80(newCapacity * 4);  // malloc/new equivalent
        if (this->data != 0) {
            unsigned int i = 0;
            int* dst = newData;
            if (this->count != 0) {
                do {
                    if (dst != 0) {  // Defensive check (should always be non-null)
                        *dst = *(int*)(this->data + i);
                    }
                    i++;
                    dst++;
                } while (i < (unsigned int)this->count);
            }
            FUN_009c8f10(this->data);  // free/delete old block
        }
        this->data = newData;
        this->capacity = newCapacity;
    }
    // Note: count remains unchanged (only capacity is increased)
}