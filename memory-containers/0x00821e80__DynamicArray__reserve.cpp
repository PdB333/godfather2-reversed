// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(uint newCapacity)
{
    // If current capacity is less than requested
    if (this->capacity < newCapacity) {
        // Allocate new block (4 bytes per element)
        undefined4* newData = (undefined4*)operatorNew(newCapacity * 4);
        if (this->data != 0) {
            uint i = 0;
            undefined4* dst = newData;
            if (this->size != 0) {
                // Copy existing elements
                do {
                    if (dst != 0) { // defensive check, should always be true
                        *dst = *(undefined4*)(this->data + i * 4);
                    }
                    i = i + 1;
                    dst = dst + 1;
                } while (i < this->size);
            }
            operatorDelete(this->data);
        }
        this->data = (int)newData;
        this->capacity = newCapacity;
    }
}