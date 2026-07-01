//FUNC_NAME: PointerArray::clear (or ObjectArray::releaseAll) at 0x00843260
// This function clears an array of pointers, releasing each non-null element,
// then deallocates the array and resets the container fields.
void __fastcall PointerArray::clear(int *thisPtr)
{
    int count = thisPtr[1]; // +0x04: number of elements
    int *arrayBase = (int *)thisPtr[0]; // +0x00: pointer to array of 8-byte entries

    // Iterate from last to first, releasing each non-null pointer
    for (int i = count - 1; i >= 0; i--)
    {
        int *entry = (int *)((char *)arrayBase + i * 8); // each entry is 8 bytes
        if (entry[0] != 0) // first 4 bytes is the pointer to release
        {
            FUN_004daf90(entry[0]); // release/destroy the object
        }
    }

    thisPtr[1] = 0; // reset count
    FUN_009c8f10(arrayBase); // deallocate the array memory
    thisPtr[0] = 0; // clear array pointer
    thisPtr[2] = 0; // +0x08: some other field (maybe capacity or flags)
}