// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray_reserve(uint newCapacity)
{
    undefined4 *newBuffer;
    uint i;
    undefined4 *dstPtr;
    int *this = unaff_ESI;

    if ((uint)this[2] < newCapacity) {
        newBuffer = (undefined4 *)operator_new(newCapacity * 4);
        if (*this != 0) {
            i = 0;
            dstPtr = newBuffer;
            if (this[1] != 0) {
                do {
                    if (dstPtr != (undefined4 *)0x0) {
                        *dstPtr = *(undefined4 *)(*this + i * 4);
                    }
                    i = i + 1;
                    dstPtr = dstPtr + 1;
                } while (i < (uint)this[1]);
            }
            operator_delete(*this);
        }
        *this = (int)newBuffer;
        this[2] = newCapacity;
    }
    return;
}