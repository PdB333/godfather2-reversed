// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
    // this[0] = data pointer
    // this[1] = count (number of elements)
    // this[2] = capacity (allocated slots)
    if ((uint)this[2] < newCapacity) {
        // Allocate new buffer: each element is 0x18 bytes
        undefined8 *newData = (undefined8 *)FUN_009c8e80(newCapacity * 0x18);
        if (this[0] != 0) {
            uint copied = 0;
            if (this[1] != 0) {
                int srcOffset = 0;
                undefined8 *dst = newData;
                do {
                    undefined8 *src = (undefined8 *)(this[0] + srcOffset);
                    if (dst != (undefined8 *)0x0) {
                        *dst = *src;
                        dst[1] = src[1];
                        dst[2] = src[2];
                    }
                    copied++;
                    srcOffset += 0x18;
                    dst += 3;
                } while (copied < (uint)this[1]);
            }
            FUN_009c8f10(this[0]); // Free old buffer
        }
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}