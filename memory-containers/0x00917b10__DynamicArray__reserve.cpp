// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int* this, uint newCapacity)
{
    int* newData;
    uint i;
    int* dst;

    if ((uint)this[2] < newCapacity) {
        newData = (int*)Allocate(newCapacity * 4);
        if (this[0] != 0) {
            i = 0;
            dst = newData;
            if (this[1] != 0) {
                do {
                    if (dst != (int*)0x0) {
                        *dst = *(int*)(this[0] + i * 4);
                    }
                    i = i + 1;
                    dst = dst + 1;
                } while (i < (uint)this[1]);
            }
            Free((int*)this[0]);
        }
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}