// FUNC_NAME: Array::reserve
// Function address: 0x0082b640
// Role: Reserves capacity in a dynamic array (reallocates if necessary, preserves existing elements)
// Layout: this[0]=data pointer, this[1]=size, this[2]=capacity

void __thiscall Array::reserve(int *this, uint newCapacity)
{
    undefined4 *newData;
    uint i;
    undefined4 *dstPtr;

    if ((uint)this[2] < newCapacity) {
        // Allocate new block of newCapacity elements (each 4 bytes)
        newData = (undefined4 *)allocateMemory(newCapacity * 4);
        if (this[0] != 0) {
            i = 0;
            dstPtr = newData;
            if (this[1] != 0) {
                do {
                    if (dstPtr != (undefined4 *)0x0) {
                        *dstPtr = *(undefined4 *)(this[0] + i * 4);
                    }
                    i = i + 1;
                    dstPtr = dstPtr + 1;
                } while (i < (uint)this[1]);
            }
            // Free old buffer
            freeMemory(this[0]);
        }
        // Update pointer and capacity (size remains unchanged)
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}