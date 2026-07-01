//FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
    undefined4 *newData;
    uint i;
    undefined4 *dst;

    if ((uint)this[2] < newCapacity) {
        newData = (undefined4 *)operatorNew(newCapacity * 4); // FUN_009c8e80
        if (this[0] != 0) {
            i = 0;
            dst = newData;
            if (this[1] != 0) {
                do {
                    if (dst != (undefined4 *)0x0) {
                        *dst = *(undefined4 *)(this[0] + i * 4);
                    }
                    i = i + 1;
                    dst = dst + 1;
                } while (i < (uint)this[1]);
            }
            operatorDelete((void *)this[0]); // FUN_009c8f10
        }
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}