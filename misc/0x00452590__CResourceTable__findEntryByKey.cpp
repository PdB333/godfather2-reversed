// FUNC_NAME: CResourceTable::findEntryByKey
uint __fastcall CResourceTable::findEntryByKey(int thisPtr)
{
    // Key structure pointed by edi (set by caller)
    // Offsets: +0x00: type (byte), +0x04: int1, +0x08: int2, +0x0C: int3, +0x10: int4,
    //          +0x14: pointer to wide string, +0x18: int id
    SearchKeyStruct* searchKey; // edi, passed via register

    uint entryCount = *(uint*)(thisPtr + 0x500);
    if (entryCount == 0)
        return 0xFFFFFFFF;

    // Array of 40-byte entries starts at thisPtr + 0x0C
    // Entry layout: +0x00: type (byte), +0x04: int1, +0x08: int2, 
    //               +0x0C: int3, +0x10: int4, +0x14: wchar_t* name,
    //               +0x18: int id
    int* entryIter = (int*)(thisPtr + 0x0C); // points to the first entry's int3? Actually it's at start of entry, but we treat as int* for offset arithmetic

    for (uint index = 0; ; index++)
    {
        if (entryCount <= index)
            return 0xFFFFFFFF;

        // Check type byte at entryIter[-3] (offset 0)
        if (*(byte*)(entryIter - 3) == '\0')
        {
            // Type 0: identify by id and name
            if (entryIter[3] == *(int*)(searchKey + 0x18)) // compare ids at offset 24
            {
                if (entryIter[3] == 0) // id 0? then return early? Actually if id is 0 and matches, just return
                {
                    return index;
                }

                // Compare wide strings (two bytes at a time)
                wchar_t* entryName = (wchar_t*)entryIter[2]; // pointer at offset 20
                wchar_t* keyName   = *(wchar_t**)((byte*)searchKey + 0x14); // key name pointer at +0x14
                int cmpResult = 0;
                do
                {
                    wchar_t entryChar = *entryName;
                    wchar_t keyChar   = *keyName;
                    if (entryChar != keyChar)
                    {
                        cmpResult = (entryChar < keyChar) ? -1 : 1;
                        break;
                    }
                    if (entryChar == L'\0')
                        break;
                    entryName++;
                    keyName++;
                } while (true);

                if (cmpResult == 0)
                {
                    return index;
                }
            }
        }
        else
        {
            // Type non-zero: identify by four integers
            if (entryIter[-2] == *(int*)((byte*)searchKey + 4) &&   // offset +4
                entryIter[-1] == *(int*)((byte*)searchKey + 8) &&   // offset +8
                entryIter[0]  == *(int*)((byte*)searchKey + 0xC) && // offset +12
                entryIter[1]  == *(int*)((byte*)searchKey + 0x10))  // offset +16
            {
                return index;
            }
        }

        // Advance to next entry (10 ints = 40 bytes)
        entryIter += 10;
    }
}