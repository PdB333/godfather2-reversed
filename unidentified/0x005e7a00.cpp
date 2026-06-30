// FUN_NAME: hashTableLookupAndSetValue
uint __cdecl hashTableLookupAndSetValue(uint handle, int value)
{
    uint hash = handle ^ 0xad103100;                                              // XOR with constant to compute hash
    byte maxHash = *(byte *)(DAT_01223504 + 0x1c);                               // maximum allowed hash value
    if (hash < maxHash)
    {
        // Table at DAT_01223504+4 is an array of 256 pointers, indexed by low byte of hash
        int *entryPtr = *(int **)(DAT_01223504 + 4 + ((hash & 0xff) * 4));
        if (entryPtr != NULL)
        {
            entryPtr[0x68 / 4] = value;                                          // write value at offset +0x68 (e.g., an int field)
            return 1;                                                            // success
        }
    }
    return 0;                                                                    // failure (invalid handle or missing entry)
}