// FUNC_NAME: DynamicArray::growCapacity
void __thiscall DynamicArray::growCapacity(int *this, uint newCapacity)
{
    undefined4 *newBuffer;
    uint i;
    undefined4 *destPtr;

    if ((uint)this[2] < newCapacity) {
        // Allocate new buffer with size = newCapacity * 4
        newBuffer = (undefined4 *)FUN_009c8e80(newCapacity * 4);
        if (*this != 0) {
            // Copy existing elements from old buffer to new buffer
            i = 0;
            destPtr = newBuffer;
            if (this[1] != 0) {
                do {
                    if (newBuffer != (undefined4 *)0x0) {
                        *destPtr = *(undefined4 *)(*this + i * 4);
                    }
                    i = i + 1;
                    destPtr = destPtr + 1;
                } while (i < (uint)this[1]);
            }
            // Free old buffer
            FUN_009c8f10(*this);
        }
        // Update pointer and capacity
        *this = (int)newBuffer;
        this[2] = newCapacity;
    }
    return;
}