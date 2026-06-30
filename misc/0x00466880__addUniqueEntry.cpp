// FUNC_NAME: addUniqueEntry
void __thiscall addUniqueEntry(void* thisPtr, int value)
{
    // Array of 4 ints at offset +0x18bc from this
    int* array = reinterpret_cast<int*>(reinterpret_cast<char*>(thisPtr) + 0x18bc);

    for (int i = 0; i < 4; ++i)
    {
        if (array[i] == value)
        {
            // Already present, nothing to do
            return;
        }
        if (array[i] == 0)
        {
            // Found an empty slot, insert value
            array[i] = value;
            return;
        }
    }
    // Array is full and value not found. No action taken.
}