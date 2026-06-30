// FUNC_NAME: KeyedTable::findEntry
// Function address: 0x00604d20
// Searches an array of fixed-size entries (0x101 bytes each) for a matching key byte.
// Returns a pointer to the data at offset 5 within the matching entry, or 0 if not found.
// Structure: [int size] followed by [entries[size] each of 0x101 bytes].
// Entry layout: byte key at offset 0, then 4 bytes (unknown), then data at offset 5.

int __thiscall KeyedTable::findEntry(int *this, char key)
{
    int i;
    int *entryPtr;

    i = 0;
    // this[0] is the size (number of entries)
    if (0 < *this) {
        // this[1] points to the first entry (array of 0x101-byte blocks)
        entryPtr = this + 1;
        do {
            // Compare the first byte of the current entry with the key
            if ((char)*entryPtr == key) {
                // Return pointer to offset 5 within this entry (skipping key and 4 unknown bytes)
                return (int)((char *)this + i * 0x101 + 5);
            }
            i = i + 1;
            entryPtr = (int *)((int)entryPtr + 0x101);
        } while (i < *this);
    }
    return 0;
}