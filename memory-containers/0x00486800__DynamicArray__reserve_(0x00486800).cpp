// FUNC_NAME: DynamicArray::reserve (0x00486800)
void __thiscall DynamicArray::reserve(int newCapacity)
{
    int *dataArray; // eax? Actually *this->data
    int *newData;
    int i;

    // +0x00: data pointer
    // +0x04: element count
    // +0x08: capacity
    if (this->capacity < (uint)newCapacity) {
        newData = (int *)FUN_009c8e80(newCapacity * 4); // allocate new array
        if (this->data != 0) {
            i = 0;
            dataArray = newData; // keep track of current position
            if (this->elementCount != 0) {
                do {
                    if (dataArray != (int *)0x0) { // redundant check, always true
                        *dataArray = *(int *)(this->data + i);
                    }
                    i = i + 1;
                    dataArray = dataArray + 1;
                } while (i < (uint)this->elementCount);
            }
            FUN_009c8f10(this->data); // free old array
        }
        this->data = newData;
        this->capacity = newCapacity;
    }
}