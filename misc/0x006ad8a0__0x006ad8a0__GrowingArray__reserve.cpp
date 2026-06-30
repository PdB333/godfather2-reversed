// FUNC_NAME: 0x006ad8a0: GrowingArray::reserve
// Reconstructed from Ghidra decompilation for EA EARS engine vector-like container.

void __thiscall GrowingArray::reserve(void *this, uint newCapacity)
{
    int *oldData;
    int *newData;
    uint oldCapacity;
    uint oldSize;
    uint i;

    oldCapacity = *(uint *)((int)this + 8); // +0x08: capacity
    if (oldCapacity < newCapacity)
    {
        newData = (int *)FUN_009c8e80(newCapacity * 4); // allocate new buffer (4 bytes per element)
        oldData = *(int **)this; // +0x00: data pointer
        oldSize = *(uint *)((int)this + 4); // +0x04: count of elements

        if (oldData != 0 && oldSize != 0)
        {
            i = 0;
            do {
                if (newData != 0) {
                    newData[i] = oldData[i];
                }
                i++;
            } while (i < oldSize);
        }

        if (oldData != 0) {
            FUN_009c8f10(oldData); // free old buffer
        }

        *(int **)this = newData; // update data pointer
        *(uint *)((int)this + 8) = newCapacity; // update capacity
        // size (offset +0x04) remains unchanged
    }
    // If capacity already >= newCapacity, do nothing
}