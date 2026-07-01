// FUNC_NAME: Container::findByFourIntKeys
int __thiscall Container::findByFourIntKeys(void* this, int* targetKey)
{
    uint32_t count = *(uint32_t*)((uint8_t*)this + 0xC); // +0xC: number of elements
    if (count == 0) return 0;

    int** elementArray = *(int***)((uint8_t*)this + 0x8); // +0x8: pointer to array of pointers
    for (uint32_t i = 0; i < count; i++)
    {
        int* element = elementArray[i];
        // Compare four consecutive ints at offsets 0x1C, 0x20, 0x24, 0x28
        if ((element[0x1C / 4] == targetKey[0]) &&
            (element[0x20 / 4] == targetKey[1]) &&
            (element[0x24 / 4] == targetKey[2]) &&
            (element[0x28 / 4] == targetKey[3]))
        {
            return (int)element; // Return pointer to the matching element (as int)
        }
    }
    return 0;
}