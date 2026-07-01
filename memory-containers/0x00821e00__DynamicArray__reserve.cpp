// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
    int *oldData;
    uint i;
    int *newData;
    
    if ((uint)this[2] < newCapacity) {
        newData = (int *)malloc(newCapacity * 4);
        if (*this != 0) {
            i = 0;
            if (this[1] != 0) {
                do {
                    if (newData != (int *)0x0) {
                        newData[i] = *(int *)(*this + i * 4);
                    }
                    i = i + 1;
                } while (i < (uint)this[1]);
            }
            free(*this);
        }
        *this = (int)newData;
        this[2] = newCapacity;
    }
    return;
}