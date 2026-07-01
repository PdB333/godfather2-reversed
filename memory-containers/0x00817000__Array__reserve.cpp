// FUNC_NAME: Array::reserve
void __thiscall Array::reserve(int *this, uint newCapacity)
{
    undefined4 *newData;
    int oldIndex;
    undefined4 *oldElement;
    undefined4 *newElement;
    uint i;

    if ((uint)this[2] < newCapacity) {
        newData = (undefined4 *)FUN_009c8e80(newCapacity * 0x18); // allocate new array (element size 0x18)
        oldIndex = 0;
        if (this[0] != 0) {
            i = 0;
            newElement = newData;
            if (this[1] != 0) {
                do {
                    oldElement = (undefined4 *)(this[0] + oldIndex);
                    if (newElement != (undefined4 *)0x0) {
                        *newElement = *oldElement;               // copy offset 0x00
                        newElement[1] = oldElement[1];           // copy offset 0x04
                        FUN_004d3b50(oldElement + 2);            // copy/init offset 0x08 (e.g., reference counting)
                    }
                    if (oldElement[2] != 0) {
                        (*(code *)oldElement[5])(oldElement[2]); // call destructor on old element (offset 0x14 = function ptr, offset 0x08 = object)
                    }
                    i = i + 1;
                    oldIndex = oldIndex + 0x18;
                    newElement = newElement + 6;                 // advance by 6 dwords (0x18 bytes)
                } while (i < (uint)this[1]);
            }
            FUN_009c8f10(this[0]); // free old array
        }
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}