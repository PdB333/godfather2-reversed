// FUN_00443820: Array::removeElement (removes element at index from dynamic array of 8-byte structures)
void __fastcall Array::removeElement(uint index, int* arrayDesc)
{
    // arrayDesc[0] = pointer to array data (each element is 8 bytes)
    // arrayDesc[1] = number of elements (uint32)
    uint32_t* data = (uint32_t*)arrayDesc[0];
    uint32_t count = (uint32_t)arrayDesc[1];

    if (index < count - 1)
    {
        do {
            // Shift elements left by one (each element is two 32-bit fields)
            data[index * 2] = data[(index + 1) * 2];
            data[index * 2 + 1] = data[(index + 1) * 2 + 1];
            index++;
        } while (index < count - 1);
    }
    // Decrease size
    arrayDesc[1] = (int)(count - 1);
}