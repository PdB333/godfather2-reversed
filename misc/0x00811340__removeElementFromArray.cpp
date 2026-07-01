// FUNC_NAME: removeElementFromArray
void __thiscall removeElementFromArray(int thisPtr, uint index)
{
    // +0x80: count of elements in the array
    uint count = *(uint *)(thisPtr + 0x80);

    if (index < count)
    {
        // Shift elements left to fill the gap
        if (index < count - 1)
        {
            do {
                // Array starts at offset 0, each element is 4 bytes
                *(int *)(thisPtr + index * 4) = *(int *)(thisPtr + (index + 1) * 4);
                index++;
            } while (index < count - 1);
        }
        // Decrement the count
        (*(int *)(thisPtr + 0x80))--;
    }
}