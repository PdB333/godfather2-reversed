// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *thisPtr, uint newCapacity)
{
    // thisPtr[0] = data pointer (array of 16-byte elements)
    // thisPtr[1] = size (number of elements currently stored)
    // thisPtr[2] = capacity (max elements allocated)

    if ((uint)thisPtr[2] < newCapacity)
    {
        // Allocate new memory block: each element is 16 bytes (0x10)
        void *newData = (void *)FUN_009c8e80(newCapacity << 4);  // likely operator new or custom alloc

        if (thisPtr[0] != 0)
        {
            uint currentSize = (uint)thisPtr[1];
            if (currentSize != 0)
            {
                // Copy existing elements (16 bytes per element) from old to new buffer
                undefined8 *src = (undefined8 *)thisPtr[0];
                undefined8 *dst = (undefined8 *)newData;
                do {
                    *dst = src[0];
                    dst[1] = src[1];
                    src += 2;  // advance by 16 bytes (two undefined8)
                    dst += 2;
                    currentSize--;
                } while (currentSize > 0);
            }
            // Free old memory block
            FUN_009c8f10((int)thisPtr[0]);  // likely operator delete or custom free
        }

        // Update data pointer and capacity
        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity;
    }
}