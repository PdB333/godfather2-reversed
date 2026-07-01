// FUNC_NAME: DataMap::lookup
// Function address: 0x0084a470
// Role: Searches a linear array of key-value pairs (each pair is two ints) for a matching key.
//       Returns the associated value if found, or 0 if not found.

int __thiscall DataMap::lookup(int key) {
    uint i = 0;
    // +0x14: entryCount (number of key-value pairs)
    // +0x10: entries (pointer to array of int pairs: [key0, value0, key1, value1, ...])
    if (this->entryCount != 0) {
        int* entryPtr = this->entries;
        do {
            if (*entryPtr == key) {
                // Dead code from original: check for overflow (i==0xffffffff) is never true
                if (i == 0xffffffff) {
                    return 0;
                }
                // Return the value at offset 1 in the pair
                return this->entries[i * 2 + 1];
            }
            i++;
            entryPtr += 2;
        } while (i < this->entryCount);
    }
    return 0;
}