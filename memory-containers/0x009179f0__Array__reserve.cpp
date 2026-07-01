// FUNC_NAME: Array::reserve
// Address: 0x009179f0
// Role: Ensures the array has capacity for at least newCapacity elements. If current capacity is insufficient, allocates a new buffer, copies existing elements, and frees the old buffer.

void __thiscall Array::reserve(int* this, uint newCapacity)
{
    uint* capacityPtr = reinterpret_cast<uint*>(this + 2); // +0x08: capacity
    if (*capacityPtr < newCapacity)
    {
        // Allocate new buffer (4 bytes per element)
        undefined4* newBuffer = reinterpret_cast<undefined4*>(allocateMemory(newCapacity * 4));
        if (*this != 0) // +0x00: data pointer
        {
            uint count = reinterpret_cast<uint*>(this + 1)[0]; // +0x04: count
            uint i = 0;
            undefined4* dest = newBuffer;
            if (count != 0)
            {
                do
                {
                    if (dest != nullptr)
                    {
                        *dest = *(undefined4*)(*this + i * 4);
                    }
                    i++;
                    dest++;
                } while (i < count);
            }
            freeMemory(*this);
        }
        *this = reinterpret_cast<int>(newBuffer);
        *capacityPtr = newCapacity;
    }
    return;
}