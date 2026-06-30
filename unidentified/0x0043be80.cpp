// FUN_0043be80: registerGroupNameHashes
void registerGroupNameHashes(void)
{
    // Global hash table or context, likely a handle for adding hashed strings
    i32 hashContext = DAT_01223414;

    // Table of 11 (0x2c / 4) group name string pointers, starting at 0x0110aba0
    const char** groupNameTable = (const char**)0x0110aba0;

    for (u32 i = 0; i < 0x2c; i += 4)
    {
        const char* str = *(const char**)((u32)groupNameTable + i);

        if (str != NULL && *str != '\0')
        {
            i32 hash = 0;
            const char* p = str;
            u8 c;
            while ((c = *p) != '\0')
            {
                u32 ch = (u32)c;
                // Convert uppercase ASCII letters to lowercase (0x41-0x5A -> add 0x20)
                if (ch - 0x41 < 0x1A)
                    ch += 0x20;

                hash = hash * 0x1003F + ch; // EA standard string hash (multiplier 65599)
                p++;
            }

            // Hash is valid (nonzero or non-1? The check avoids -1, but normally hash != 0 suffices)
            if (hash != -1)
            {
                // Register the hashed group name with the hashContext
                // The third argument 1 might indicate "add" vs "lookup"
                FUN_0043c140(hashContext, hash, 1);
            }
        }
    }
}