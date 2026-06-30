// FUNC_NAME: StringTable::initializeErrorTable
void __thiscall StringTable::initializeErrorTable(void)
{
    // Iterates from 0x54 to 0x90 (0x3C bytes, step 4 => 15 entries)
    int index;
    for (index = 0x54; index < 0x90; index += 4)
    {
        // Get the string pointer from the static array at "table index is NaN" + index + 4
        char* strPtr = *(char**)("table index is NaN" + index + 4);
        
        // Compute the length of the string (just to find end? but not used)
        char* p = strPtr;
        while (*p != '\0')
            p++;
        
        // Compute a hash/ID for this string (FUN_00638920)
        int stringId = computeStringHash();
        
        // Store the ID into the table (this+0x10 points to an array of integers)
        *(int*)(*(int*)(this + 0x10) + index) = stringId;
        
        // Set bit 0x10 in the byte at offset +5 of the structure pointed to by the entry
        byte* flagsByte = (byte*)(*(int*)(*(int*)(this + 0x10) + index) + 5);
        *flagsByte |= 0x10;
    }
}