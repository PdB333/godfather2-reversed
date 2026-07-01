// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int *this, unsigned int newCapacity)
{
    unsigned int oldCapacity = this[2]; // offset +0x08: capacity
    if (oldCapacity < newCapacity)
    {
        // Allocate new buffer (4 bytes per element)
        int *newBuffer = (int *)FUN_009c8e80(newCapacity * 4);
        if (this[0] != 0) // offset +0x00: data pointer
        {
            unsigned int count = this[1]; // offset +0x04: element count
            if (count != 0)
            {
                // Copy existing elements
                for (unsigned int i = 0; i < count; i++)
                {
                    if (newBuffer != 0)
                    {
                        newBuffer[i] = *(int *)(this[0] + i * 4);
                    }
                }
            }
            // Free old buffer
            FUN_009c8f10(this[0]);
        }
        // Update buffer and capacity
        this[0] = (int)newBuffer;
        this[2] = newCapacity;
    }
}