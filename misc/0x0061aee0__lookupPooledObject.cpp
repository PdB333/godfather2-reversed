// FUNC_NAME: lookupPooledObject
int* lookupPooledObject(unsigned int handle)
{
    // handle is passed in EAX; it's an index into a global pool
    // DAT_011a0f38 is a global array of 0x38-byte objects
    // Maximum 4096 entries (0x1000)
    if ((handle < 0x1000) && (handle * 0x38 != -0x11a0f28) &&
        (*(int *)(&DAT_011a0f38 + handle * 0x38) != 0))
    {
        int* ptr = *(int **)(*(int *)(&DAT_011a0f38 + handle * 0x38) + 0x1c);
        if (ptr != nullptr)
        {
            int subIndex = FUN_00617920(&someLocal); // returns a sub-index into an 8-byte entry array
            if (subIndex >= 0)
            {
                // ptr points to an array of 8-byte entries; each entry has a pointer at offset 0
                int* entry = (int *)(*ptr + 4 + subIndex * 8);
                if (entry != nullptr)
                {
                    // Returns offset into the entry (offset 0xc)
                    return (int *)(*entry + 0xc);
                }
            }
        }
    }
    // Default return, possibly from register EDI (uninitialized in this context)
    return (int *)unaff_EDI;
}