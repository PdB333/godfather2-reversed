// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(uint newCapacity)
{
    // Structure offsets: +0x00 data pointer, +0x04 count, +0x08 capacity
    if (this->capacity < newCapacity) {
        int* newData = (int*)malloc(newCapacity * 4);
        if (this->data != 0) {
            uint i = 0;
            int* dest = newData;
            while (i < this->count) {
                if (dest != 0) {
                    *dest = this->data[i];
                }
                i++;
                dest++;
            }
            free(this->data);
        }
        this->data = newData;
        this->capacity = newCapacity;
    }
}