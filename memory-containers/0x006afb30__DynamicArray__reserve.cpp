// FUNC_NAME: DynamicArray::reserve
// Function address: 0x006afb30
// Member offsets: this+0 = data pointer, this+4 = size (element count), this+8 = capacity (allocated slots)
// Copies existing elements to new buffer when growing capacity, preserving size.

void DynamicArray::reserve(unsigned int newCapacity)
{
    if ((unsigned int)this->capacity < newCapacity) {
        void* newBuffer = allocMemory(newCapacity * 4);  // element size = 4 bytes
        if (this->data != 0) {
            unsigned int i = 0;
            int* src = (int*)this->data;
            int* dst = (int*)newBuffer;
            if (this->size != 0) {
                do {
                    if (newBuffer != 0) {
                        *dst = *src;
                    }
                    i = i + 1;
                    src = src + 1;
                    dst = dst + 1;
                } while (i < (unsigned int)this->size);
            }
            deallocMemory(this->data);
        }
        this->data = newBuffer;
        this->capacity = newCapacity;
    }
    return;
}