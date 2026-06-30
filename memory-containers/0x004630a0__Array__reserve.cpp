// FUNC_NAME: Array::reserve
void Array::reserve(unsigned int newCapacity)
{
    // This checks against capacity (offset +0x08) of the Array object (this in ESI)
    if (newCapacity > (unsigned int)this->capacity) {
        // Allocate new block of 4-byte elements (offset +0x00 is data pointer)
        unsigned int* newData = (unsigned int*)FUN_009c8e80(newCapacity * 4); // EA custom malloc
        if (this->data != 0) {
            // Copy existing elements (count at offset +0x04)
            unsigned int idx = 0;
            unsigned int* src = this->data;
            unsigned int* dst = newData;
            while (idx < (unsigned int)this->count) {
                *dst = *src;
                idx++;
                src++;
                dst++;
            }
        }
        // Free old data
        FUN_009c8f10(this->data); // EA custom free
        this->data = newData;
        this->capacity = newCapacity;
    }
}