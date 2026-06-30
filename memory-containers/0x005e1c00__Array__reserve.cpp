// FUNC_NAME: Array::reserve

void __thiscall Array::reserve(uint newCapacity)
{
    if (this->capacity < newCapacity)
    {
        // Allocate new buffer: each element is 4 bytes
        undefined4* newData = (undefined4*)FUN_009c8e80(newCapacity * 4); // likely malloc or realloc

        if (this->data != nullptr)
        {
            uint copiedCount = 0;
            undefined4* dst = newData;

            if (this->count != 0)
            {
                do
                {
                    // Copy element by element
                    if (dst != nullptr)
                    {
                        *dst = *(undefined4*)(this->data + copiedCount * 4);
                    }
                    copiedCount++;
                    dst++;
                } while (copiedCount < this->count);
            }

            // Free old buffer
            FUN_009c8f10(this->data); // likely free
        }

        // Update pointer and capacity
        this->data = (int*)newData;
        this->capacity = newCapacity;
    }
}