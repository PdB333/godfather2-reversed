// FUNC_NAME: HashTable::addEntry
void HashTable::addEntry(int key)
{
    // First array: 12-byte elements (e.g., key struct)
    // +0x14: base pointer, +0x18: size, +0x1C: capacity
    if (size12 == capacity12)
    {
        if (capacity12 == 0)
            capacity12 = 1;
        else
            capacity12 *= 2;
        reallocateFirstArray(capacity12); // FUN_005f0040
    }
    // Zero out new 12-byte element
    uint8_t* newElem12 = firstArray + size12 * 12;
    size12++;
    if (newElem12)
    {
        *(uint64_t*)newElem12 = 0;
        *(uint32_t*)(newElem12 + 8) = 0;
    }

    // Second array: 4-byte elements (e.g., values)
    // +0x08: base pointer, +0x0C: size, +0x10: capacity
    if (size4 == capacity4)
    {
        if (capacity4 == 0)
            capacity4 = 1;
        else
            capacity4 *= 2;
        reallocateSecondArray(capacity4); // FUN_005effe0
    }
    uint32_t* newElem4 = secondArray + size4 * 4;
    size4++;
    if (newElem4)
    {
        *newElem4 = 0;
    }

    // Set the last element of second array based on key
    uint32_t* lastElem4 = secondArray + (size4 - 1) * 4;
    if (key != 0)
    {
        *lastElem4 = hashFunction(key); // FUN_004dafd0
    }
    else
    {
        *lastElem4 = 0;
    }
}