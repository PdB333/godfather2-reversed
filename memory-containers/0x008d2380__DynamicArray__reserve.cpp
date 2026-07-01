// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
    // this[0] = data pointer
    // this[1] = size (number of elements)
    // this[2] = capacity (allocated count)
    // Each element is 0x1c (28) bytes

    if ((uint)this[2] < newCapacity) {
        // Allocate new block: newCapacity * 28 bytes
        undefined8 *newData = (undefined8 *)FUN_009c8e80(newCapacity * 0x1c); // likely malloc

        if (this[0] != 0) {
            uint count = 0;
            if (this[1] != 0) {
                int srcOffset = 0;
                undefined8 *dst = newData;
                do {
                    undefined8 *src = (undefined8 *)(this[0] + srcOffset);
                    if (dst != (undefined8 *)0x0) {
                        // Copy 28 bytes: 3 * 8 bytes + 4 bytes
                        *dst = *src;
                        dst[1] = src[1];
                        dst[2] = src[2];
                        *(undefined4 *)(dst + 3) = *(undefined4 *)(src + 3);
                    }
                    count++;
                    srcOffset += 0x1c;
                    dst = (undefined8 *)((int)dst + 0x1c);
                } while (count < (uint)this[1]);
            }
            FUN_009c8f10(this[0]); // likely free
        }
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}