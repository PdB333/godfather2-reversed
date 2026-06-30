// FUNC_NAME: releaseObjectArray
void __fastcall releaseObjectArray(int* container)
{
    int count = container[1];                    // +0x04: number of entries in the array
    int* arrayBase = (int*)container[0];         // +0x00: pointer to 8-byte entries

    // Iterate backwards and release each non-null object
    for (int i = count - 1; i >= 0; --i)
    {
        int* entry = (int*)((unsigned char*)arrayBase + i * 8);
        if (*entry != 0)                        // first 4 bytes of the entry (object pointer)
        {
            FUN_004daf90(entry);                 // release the entry (presumably frees its resources)
        }
    }

    // Free the underlying array buffer
    if (arrayBase != 0)
    {
        FUN_009c8f10(arrayBase);                 // memory deallocation (likely operator delete[])
    }
}