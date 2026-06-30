// FUNC_NAME: Vector::reserve (some internal EA EARS vector class)

void Vector::reserve(uint newCapacity)
{
    // Offset: +0x00 -> buffer pointer (int*)
    // Offset: +0x04 -> size (uint)
    // Offset: +0x08 -> capacity (uint)

    if (this->capacity < newCapacity)
    {
        int* newBuffer = (int*)operator new[](newCapacity * 4); // FUN_009c8e80
        if (this->buffer != nullptr)
        {
            uint count = 0;
            int* dst = newBuffer;
            if (this->size != 0)
            {
                do
                {
                    if (dst != nullptr)
                    {
                        *dst = this->buffer[count]; // copy element (4 bytes)
                    }
                    ++count;
                    ++dst;
                } while (count < this->size);
            }
            operator delete[](this->buffer); // FUN_009c8f10
        }
        this->buffer = newBuffer;
        this->capacity = newCapacity;
    }
    // Note: this->size remains unchanged.
}