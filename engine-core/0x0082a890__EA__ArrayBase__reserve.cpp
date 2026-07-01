// FUNC_NAME: EA::ArrayBase::reserve
// Address: 0x0082a890
// Role: Ensures internal array capacity is at least newCapacity, growing if necessary.
// It allocates a new buffer of newCapacity elements (each 4 bytes), copies existing elements,
// then frees old buffer.

void EA::ArrayBase::reserve(uint newCapacity)
{
    // this layout (offsets relative to this):
    // +0x00: data pointer (int*)
    // +0x04: size (uint)
    // +0x08: capacity (uint)

    if (capacity < newCapacity)
    {
        int* newData = (int*)FUN_009c8e80(newCapacity * 4); // allocate new buffer (element size 4)
        if (data != 0)
        {
            uint i = 0;
            int* dst = newData;
            if (size != 0)
            {
                do
                {
                    if (dst != 0)
                    {
                        *dst = *(int*)((int)data + i * 4);
                    }
                    i++;
                    dst++;
                } while (i < size);
            }
            FUN_009c8f10(data); // free old buffer
        }
        data = newData;
        capacity = newCapacity;
    }
}