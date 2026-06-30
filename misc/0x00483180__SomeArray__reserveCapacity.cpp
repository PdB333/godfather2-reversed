// FUNC_NAME: SomeArray::reserveCapacity
void SomeArray::reserveCapacity(uint newCapacity)
{
    if ((uint)capacity < newCapacity)
    {
        // Allocate new buffer: newCapacity elements, each 8 bytes (pair of ints)
        int* newBuffer = (int*)operator new(newCapacity * 8);

        // Copy existing elements to new buffer
        if (data != nullptr && count > 0)
        {
            uint i = 0;
            int* dst = newBuffer;
            do
            {
                // Copy one element (two ints)
                *dst = data[i * 2];
                dst[1] = data[i * 2 + 1];
                ++i;
                dst += 2;
            } while (i < (uint)count);
        }

        // Free old buffer if any
        if (data != nullptr)
        {
            operator delete(data);
        }

        // Update pointer and capacity
        data = newBuffer;
        capacity = newCapacity;
    }
    // otherwise, capacity is sufficient, do nothing
}