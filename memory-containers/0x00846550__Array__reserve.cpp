// FUNC_NAME: Array::reserve
void __thiscall Array::reserve(int *this, uint minCapacity)
{
    int oldCount;
    uint oldCapacity;
    int *oldData;
    int *newData;
    uint i;
    
    oldCapacity = (uint)this[2]; // +0x08 capacity
    if (oldCapacity < minCapacity) {
        newData = (int *)FUN_009c8e80(minCapacity * 12); // allocate elementSize * newCapacity
        oldData = (int *)this[0]; // +0x00 data pointer
        if (oldData != 0) {
            oldCount = this[1]; // +0x04 size
            // copy each element (12 bytes per element)
            for (i = 0; i < (uint)oldCount; i++) {
                // each element is 12 bytes: 8 bytes + 4 bytes
                newData[i * 3] = oldData[i * 3];
                newData[i * 3 + 1] = oldData[i * 3 + 1];
                newData[i * 3 + 2] = oldData[i * 3 + 2];
            }
            FUN_009c8f10(oldData); // free old data
        }
        this[0] = (int)newData; // +0x00 data
        this[2] = minCapacity;  // +0x08 capacity
    }
}