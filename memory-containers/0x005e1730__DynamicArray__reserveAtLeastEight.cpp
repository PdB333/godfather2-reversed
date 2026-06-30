// FUNC_NAME: DynamicArray::reserveAtLeastEight
// Address: 0x005e1730
// This function grows a dynamic array's capacity to at least 8 elements.

// Structure layout (offsets from this):
//   +0x00: int* data      (pointer to allocated array)
//   +0x04: int  size       (number of elements currently stored)
//   +0x08: int  capacity   (maximum number of elements that can be stored)

void __thiscall DynamicArray::reserveAtLeastEight()
{
    // If capacity is already >= 8, do nothing.
    if (this->capacity < 8)
    {
        // Allocate space for 8 elements (each 4 bytes).
        int* newData = (int*)FUN_009c8e80(0x20); // custom alloc: 32 bytes

        // If there is existing data, copy it over.
        if (this->data != nullptr)
        {
            // Copy up to 'size' elements.
            if (this->size != 0)
            {
                uint i = 0;
                int* dst = newData;
                do
                {
                    // The null check on dst is likely redundant, but present in the binary.
                    if (dst != nullptr)
                    {
                        *dst = this->data[i];
                    }
                    i++;
                    dst++;
                } while (i < (uint)this->size);
            }
            // Free the old data.
            FUN_009c8f10(this->data); // custom dealloc
        }

        // Update the data pointer and capacity.
        this->data = newData;
        this->capacity = 8;
    }
}