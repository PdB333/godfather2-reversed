// FUNC_NAME: HashTable::findEntryByKey
// Function at 0x006425f0: Searches through a compact hash table for an entry matching a given key.
// The table is an array of 32-bit integers stored at an offset of 0xC from the 'this' pointer.
// Each entry encodes:
//   bits 0-5:  type tag (valid value 0x18)
//   bits 6-14: key to compare against param_2
//   bits 15-32: delta (offset to next entry, relative to current index + 1, with 0x1ffff bias)
// The string "$a $ a4A" is used as a lookup table for prefix length during chain traversal.
// Returns 0 if a match is found, 1 if the chain ends without a match.
int __thiscall HashTable::findEntryByKey(int this, int index, uint key)
{
    int* entryPtr;          // Pointer to the current entry in the table
    int* adjustedEntry;     // Possibly shifted pointer for tag check
    int delta;              // Encoded offset to the next entry

    if (index != -1)
    {
        do
        {
            // Retrieve pointer to the entry at 'index' from the base array (offset 0xC)
            entryPtr = (int*)(*(int*)(this + 0xC) + index * 4);
            
            // Determine the adjusted entry: if the current index is 0 or if the preceding entry's
            // low 6 bits index into "$a $ a4A" and the high bit (0x80) is clear, use current pointer.
            if ((index < 1) ||
                (adjustedEntry = entryPtr - 1,
                 ("$a $ a4A"[entryPtr[-1] & 0x3f] & 0x80U) == 0))
            {
                adjustedEntry = entryPtr;
            }
            
            // Check the type tag (low 6 bits must be 0x18) and the key field (bits 6-14 must equal param_2)
            if ((((byte)*adjustedEntry & 0x3f) != 0x18) ||
                ((*adjustedEntry >> 6 & 0x1ffU) != key))
            {
                return 1;
            }
            
            // Extract the delta from bits 15-32, subtract bias 0x1ffff
            delta = (*entryPtr >> 6 & 0x3ffffU) - 0x1ffff;
        } while ((delta != -1) && (index = index + 1 + delta, index != -1));
    }
    return 0;
}