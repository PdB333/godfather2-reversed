// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(uint newCapacity)
{
    // param_1 = this
    // param_2 = newCapacity
    if (this->capacity < newCapacity) // this+0x08
    {
        // Allocate new buffer (4 bytes per element)
        int* newData = (int*)FUN_009c8e80(newCapacity * 4); // malloc-like
        if (this->data != nullptr) // this+0x00
        {
            uint i = 0;
            int* dst = newData;
            if (this->count != 0) // this+0x04
            {
                do {
                    if (dst != nullptr) {
                        *dst = *(int*)(this->data + i * 4);
                    }
                    i++;
                    dst++;
                } while (i < this->count);
            }
            FUN_009c8f10(this->data); // free old buffer
        }
        this->data = newData; // this+0x00
        this->capacity = newCapacity; // this+0x08
    }
}