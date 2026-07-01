// FUNC_NAME: ResizeableArray::reserve
void __thiscall ResizeableArray::reserve(int *this, uint newCapacity)
{
    void *newData;
    uint index;
    void *dstPtr;
    
    // Only expand if requested capacity is larger than current capacity
    if ((uint)this[2] < newCapacity) {
        newData = (void *)FUN_009c8e80(newCapacity * 4);
        if (this[0] != (void *)0x0) {
            index = 0;
            dstPtr = newData;
            if (this[1] != 0) {
                do {
                    if (dstPtr != (void *)0x0) {
                        *(uint *)dstPtr = *(uint *)(this[0] + index * 4);
                    }
                    index = index + 1;
                    dstPtr = (void *)((int)dstPtr + 4);
                } while (index < (uint)this[1]);
            }
            FUN_009c8f10(this[0]);
        }
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}