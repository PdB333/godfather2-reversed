// FUNC_NAME: StringTable::lookup
// This function appears to implement a hash-based string lookup table.
// It hashes the input string and searches a table for a match.
// Returns pointer to the matching entry or null if not found.
__fastcall StringEntry* StringTable::lookup(const char* str, int param_1) {
    byte bVar1;
    uint hashIndex;
    byte *pbVar3;
    int cmpResult;
    byte *nodeStr2;
    bool bVar6;
    
    // param_1 is likely the string length or type parameter
    // Only process strings with length in range 4-11 (param_1 - 4 < 8 means param_1 < 12, and UINT wrap check)
    if (param_1 - 4U < 8) { // param_1 >= 4 && param_1 < 12
        // Hash using character table lookup at DAT_00e2b538 (likely a hash or weight table)
        // Add first char's hash value, last char's hash value, and length
        hashIndex = (int)(char)(&DAT_00e2b538)[*str] +
                   (int)(char)(&DAT_00e2b538)[str[param_1 - 1]] + param_1;
        
        if (hashIndex < 0xc) { // Valid hash index (0-11, so table has 12 entries)
            // Compare the full string with stored entry
            // PTR_DAT_01129170 is a table of StringEntry pointers (each entry has a string pointer)
            StringEntry* entry = (&PTR_DAT_01129170)[hashIndex * 2]; // Every 2 entries
            
            // Compare first byte
            if (*str == *(char*)entry) {
                pbVar5 = (byte*)(entry + 1);
                pbVar3 = (byte*)(str + 1);
                // String comparison loop
                do {
                    bVar1 = *pbVar3;
                    bVar6 = bVar1 < *pbVar5;
                    if (bVar1 != *pbVar5) {
                        cmpResult = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
                        goto checkResult;
                    }
                    if (bVar1 == 0) break; // End of string
                    bVar1 = pbVar3[1];
                    bVar6 = bVar1 < pbVar5[1];
                    if (bVar1 != pbVar5[1]) {
                        cmpResult = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
                        goto checkResult;
                    }
                    pbVar3 = pbVar3 + 2;
                    pbVar5 = pbVar5 + 2;
                } while (bVar1 != 0);
                cmpResult = 0;
checkResult:
                if (cmpResult == 0) {
                    return &PTR_DAT_01129170 + hashIndex * 2; // Return matching entry
                }
            }
        }
    }
    return nullptr;
}