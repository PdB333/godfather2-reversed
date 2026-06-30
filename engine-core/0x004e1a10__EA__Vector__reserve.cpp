// FUNC_NAME: EA::Vector::reserve
void __thiscall EA::Vector::reserve(uint newCapacity)
{
    void* newData;
    uint i;
    uint elementCount;
    uint* capacityPtr; // +0x08
    uint* countPtr;    // +0x04
    void** dataPtr;    // +0x00

    dataPtr = (void**)(this + 0x00);
    countPtr = (uint*)(this + 0x04);
    capacityPtr = (uint*)(this + 0x08);

    if (*capacityPtr < newCapacity)
    {
        // Allocate new block: each element is 0x18 bytes
        newData = allocate(newCapacity * 0x18);
        if (*dataPtr != 0)
        {
            elementCount = *countPtr;
            if (elementCount != 0)
            {
                // Copy existing elements (each 24 bytes)
                for (i = 0; i < elementCount; i++)
                {
                    ((uint64_t*)newData)[i * 3 + 0] = ((uint64_t*)(*dataPtr))[i * 3 + 0];
                    ((uint64_t*)newData)[i * 3 + 1] = ((uint64_t*)(*dataPtr))[i * 3 + 1];
                    ((uint64_t*)newData)[i * 3 + 2] = ((uint64_t*)(*dataPtr))[i * 3 + 2];
                }
            }
            deallocate(*dataPtr);
        }
        *dataPtr = newData;
        *capacityPtr = newCapacity;
    }
}