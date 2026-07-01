// FUNC_NAME: Array::reserve
// Function at 0x00792010: Ensures internal capacity for a dynamic array.
// Fields: data +0x00, size +0x04, capacity +0x08
void __thiscall Array::reserve(uint newCapacity)
{
    if (this->capacity < newCapacity) {
        undefined4 *newData = (undefined4 *)FUN_009c8e80(newCapacity * 4);
        if (this->data != 0) {
            uint i = 0;
            undefined4 *dst = newData;
            if (this->size != 0) {
                do {
                    if (dst != (undefined4 *)0x0) {
                        *dst = *(undefined4 *)(this->data + i);
                    }
                    i = i + 1;
                    dst = dst + 1;
                } while (i < (uint)this->size);
            }
            FUN_009c8f10(this->data);
        }
        this->data = (int)newData;
        this->capacity = newCapacity;
    }
    return;
}