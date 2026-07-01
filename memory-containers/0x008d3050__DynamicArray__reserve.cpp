// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, uint newCapacity)
{
    // this[0] = data pointer (array of elements, each 0x18 bytes)
    // this[1] = current element count (size)
    // this[2] = current capacity (allocated slots)
    uint currentCapacity = this[2];
    if (currentCapacity < newCapacity)
    {
        // Allocate new block: newCapacity * elementSize (0x18)
        undefined8 *newData = (undefined8 *)FUN_009c8e80(newCapacity * 0x18);
        if (this[0] != 0)
        {
            uint i = 0;
            if (this[1] != 0)
            {
                int srcOffset = 0;
                undefined8 *dst = newData;
                do
                {
                    undefined8 *src = (undefined8 *)(this[0] + srcOffset);
                    if (dst != (undefined8 *)0x0)
                    {
                        *dst = *src;
                        dst[1] = src[1];
                        dst[2] = src[2];
                    }
                    i++;
                    srcOffset += 0x18;
                    dst += 3;
                } while (i < (uint)this[1]);
            }
            // Free old data
            FUN_009c8f10(this[0]);
        }
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}