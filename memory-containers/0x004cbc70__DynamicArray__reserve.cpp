// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity)
{
    undefined4 *newData;
    uint i;
    undefined4 *dst;
    int *this; // unaff_ESI

    if ((uint)this[2] < newCapacity) {
        newData = (undefined4 *)FUN_009c8e80(newCapacity * 4); // operator new[]
        if (*this != 0) {
            i = 0;
            dst = newData;
            if (this[1] != 0) {
                do {
                    if (dst != (undefined4 *)0x0) {
                        *dst = *(undefined4 *)(*this + i * 4);
                    }
                    i = i + 1;
                    dst = dst + 1;
                } while (i < (uint)this[1]);
            }
            FUN_009c8f10(*this); // operator delete[]
        }
        *this = (int)newData;
        this[2] = newCapacity;
    }
    return;
}