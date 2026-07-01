// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
    int *newData;
    uint i;
    int *oldElement;
    int *newElement;

    if ((uint)this[2] < newCapacity) {
        newData = (int *)FUN_009c8e80(newCapacity * 0x1c); // allocate 28 bytes per element
        if (this[0] != 0) {
            i = 0;
            if (this[1] != 0) {
                newElement = (int *)((int)newData + 0x18); // start at offset 0x18 (end of first element)
                do {
                    // Calculate old element pointer: newElement + oldBase - newBase - 0x18
                    oldElement = (int *)((int)newElement + this[0] + (-0x18 - (int)newData));
                    if (newElement != (int *)0x18) {
                        // Copy first 12 bytes (3 ints)
                        newElement[-2] = 0; // clear? Actually these are set to zero before copy? Wait, the code sets newElement[-2]=0, newElement[-1]=0, *newElement=0, then copies. That seems like initialization then copy. But the copy overwrites. So it's clearing then copying.
                        newElement[-1] = 0;
                        *newElement = 0;
                        newElement[-6] = *oldElement;       // offset 0
                        newElement[-5] = oldElement[1];     // offset 4
                        newElement[-4] = oldElement[2];     // offset 8
                        FUN_00792320(oldElement + 4);       // move sub-object at offset 16
                        *(char *)(newElement + -3) = *(char *)(oldElement + 3); // copy byte at offset 12
                    }
                    if (oldElement[4] != 0) {
                        FUN_009c8f10(oldElement[4]); // free old sub-object pointer at offset 16
                    }
                    i++;
                    newElement += 7; // advance 28 bytes (7 ints)
                } while (i < (uint)this[1]);
            }
            FUN_009c8f10(this[0]); // free old data buffer
        }
        this[0] = (int)newData;
        this[2] = (int)newCapacity;
    }
    return;
}