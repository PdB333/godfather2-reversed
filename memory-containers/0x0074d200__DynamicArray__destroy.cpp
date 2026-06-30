// FUNC_NAME: DynamicArray::destroy
void __fastcall DynamicArray::destroy(int *thisPtr)
{
    int count = thisPtr[1]; // +0x04: number of elements
    while (--count >= 0)
    {
        if (*(int *)(*thisPtr + count * 8) != 0)
        {
            // Call destructor on each non-null element (8-byte entries)
            FUN_004daf90(*thisPtr + count * 8);
        }
    }
    thisPtr[1] = 0; // Reset count to 0
    FUN_009c8f10(*thisPtr); // Free the element array
    *thisPtr = 0;   // Clear pointer to array
    thisPtr[2] = 0; // +0x08: likely capacity or buffer size
    return;
}