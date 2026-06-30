// FUNC_NAME: Container::addElement
void __thiscall Container::addElement(const void* pElement)
{
    int* thisPtr = reinterpret_cast<int*>(this);
    int size = thisPtr[1]; // +0x04: current number of elements
    int capacity = thisPtr[2]; // +0x08: allocated capacity
    if (size == capacity)
    {
        // Double capacity (or set to 1 if initially zero)
        int newCapacity;
        if (capacity == 0)
            newCapacity = 1;
        else
            newCapacity = capacity * 2;
        // Grow the internal buffer (FUN_0061a830 handles reallocation)
        this->grow(newCapacity); // Will update thisPtr[0] and thisPtr[2]
        // Re-read pointers after grow
        thisPtr = reinterpret_cast<int*>(this);
    }
    // Compute pointer to the new element slot
    char* pSlot = reinterpret_cast<char*>(thisPtr[0]) + thisPtr[1] * 0x14;
    // Increment size
    thisPtr[1]++;
    if (pSlot != nullptr)
    {
        // Copy the 20-byte structure (0x14 bytes) from pElement
        // The source likely contains two 64-bit values followed by one 32-bit value
        // (matches 8+8+4 = 20)
        const uint64_t* src64 = reinterpret_cast<const uint64_t*>(pElement);
        uint64_t* dst64 = reinterpret_cast<uint64_t*>(pSlot);
        dst64[0] = src64[0];
        dst64[1] = src64[1];
        *reinterpret_cast<uint32_t*>(&dst64[2]) = *reinterpret_cast<const uint32_t*>(&src64[2]);
    }
}