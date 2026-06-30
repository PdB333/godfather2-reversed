// FUNC_NAME: StringTable::addString
void __fastcall StringTable::addString(int unusedParam, char *str) // this in ESI
{
    char *p;
    int len;
    int hash;
    int *internal;   // +0x1c from this (pointer to internal data block)
    int *dataBlock;  // pointer pointed by internal[0] (first field)
    int *arrayBase;  // derived from dataBlock+0x18
    int entryIndex;  // computed index for the table

    // Compute string length
    p = str;
    while (*p != '\0')
        p++;
    len = p - (str + 1); // Actually pcVar3 - (param_2 + 1) = strlen(str)

    // Hash the string (FUN_00638920 likely a hash function)
    hash = hashString(*(int *)(this + 0x20), str, len, 0);

    // Insert hash into internal table (FUN_0063de90)
    addToTable(hash);

    // Access internal data at offset +0x1c
    internal = *(int **)(this + 0x1c);

    // Increment index field at offset 0x34 (internal[0xd])
    internal[0xd]++;

    // Complex table write:
    // internal[0] points to a data block (dataBlock)
    dataBlock = (int *)*internal;  // offset 0x00 in internal
    // dataBlock + 0x18 holds a pointer (arrayBase)
    arrayBase = (int *)*(int *)((char *)dataBlock + 0x18);
    // Compute entry offset: internal[ internal[0xd] + 0xad ] * 12 + 4
    entryIndex = internal[ internal[0xd] + 0xad ];
    // Write internal[6] (offset 0x18) into the table
    *(int *)((char *)arrayBase + 4 + entryIndex * 0xc) = internal[6];
}