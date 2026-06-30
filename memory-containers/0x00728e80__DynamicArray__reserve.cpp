// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int* thisPtr, uint newCapacity)
{
    // Structure layout (assuming 3 fields):
    // +0x00: int* data
    // +0x04: uint size
    // +0x08: uint capacity
    int*& data = *(int**)thisPtr;
    uint& size = *(uint*)(thisPtr + 1);
    uint& capacity = *(uint*)(thisPtr + 2);

    if (capacity < newCapacity)
    {
        // Allocate new buffer (4 bytes per element)
        int* newData = (int*)operator new[](newCapacity * 4); // FUN_009c8e80

        // Copy existing elements if any
        if (data != nullptr)
        {
            uint i = 0;
            int* src = data;
            int* dst = newData;
            if (size != 0)
            {
                do
                {
                    if (dst != nullptr) // always true, but kept as per decompiled logic
                    {
                        *dst = *src;
                    }
                    i++;
                    src++;
                    dst++;
                } while (i < size);
            }
            // Free old buffer
            operator delete[](data); // FUN_009c8f10
        }

        // Update pointer and capacity
        data = newData;
        capacity = newCapacity;
    }
    // No return
}