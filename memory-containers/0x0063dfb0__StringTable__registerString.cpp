// FUNC_NAME: StringTable::registerString
void __thiscall StringTable::registerString(char *str)
{
    int len;
    int hashResult;
    int *table;
    int index;

    // Compute length of string (excluding null terminator)
    len = strlen(str); // pcVar3 - (str+1) gives len-1, but actual length used is len-1

    // Hash the string: parameters: (hashTableBase, str, len-1, flags=0)
    // Returns a handle/index into the string pool
    hashResult = FUN_00638920(*(int *)(this + 0x20), str, len - 1, 0);

    // Add the hashed result to the pool (likely insert into a list or hash chain)
    FUN_0063de90(hashResult);

    // Access the internal table at this+0x1c
    table = *(int **)(this + 0x1c);

    // Increment entry count (offset 0x34 = 13 * 4)
    table[0xd] = table[0xd] + 1; // m_count++

    // Compute index into an array of 12-byte entries (offset of base is from *table+0x18)
    // table[table[0xd] + 0xad] gives a bucket index (0xad = 173 entries offset)
    index = table[table[0xd] + 0xad];

    // Write table[6] (m_someValue) into the array slot at:
    // base = *(int*)(*table + 0x18)  // pointer to array
    // offset = 4 + index * 12  // each entry 12 bytes, starting at offset 4
    *(int *)(*(int *)(*table + 0x18) + 4 + index * 0xc) = table[6];
}