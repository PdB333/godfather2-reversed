// FUNC_NAME: LookupTable::FindByKey
// Function address: 0x005190e0
// Searches for an entry with a 4-int key in a linear-probed list.
// Returns pointer to the matching entry, or 0 if not found.
// Class LookupTable layout:
//   +0x00: unknown
//   +0x04: unknown
//   +0x08: int count
//   +0x0C: int** entries (array of pointers to entries)
// Each entry is an int array; the key fields are at offsets +0x08, +0x0C, +0x10, +0x14
// (i.e., entry[2], entry[3], entry[4], entry[5]).

int* __thiscall LookupTable::FindByKey(void) // this in ECX, key pointer in ESI
{
    int count = *(int *)(this + 8);          // +0x08
    int** entries = *(int ***)(this + 0x0C); // +0x0C

    // Key is assumed to be in ESI (not captured in standard calling convention)
    int* key = (int*)__builtin_ia32_read_eflags(); // placeholder; real parameter is in ESI
    // The actual key pointer is passed via ESI register.
    // For reconstruction we treat it as a pointer to 4 ints.

    for (int i = 0; i < count; i++)
    {
        int* entry = entries[i];
        if (key[0] == entry[2] &&   // key +0x00 vs entry +0x08
            key[1] == entry[3] &&   // key +0x04 vs entry +0x0C
            key[2] == entry[4] &&   // key +0x08 vs entry +0x10
            key[3] == entry[5])     // key +0x0C vs entry +0x14
        {
            return entries[i];
        }
    }
    return 0;
}