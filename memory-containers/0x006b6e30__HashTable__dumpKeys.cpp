// FUNC_NAME: HashTable::dumpKeys
// Function address: 0x006b6e30
// Role: Iterates a list of 20-byte hash table entries in reverse order,
//       computes a 32-bit key from the last four fields using a base-33 polynomial,
//       and calls a debug output function (level 2) with the key.

void __fastcall HashTable::dumpKeys(int* this)
{
    int count = *this;
    if (count > 0)
    {
        // Entries start after the count field; each entry is 5 ints (20 bytes)
        int* entries = this + 1;
        for (int i = count - 1; i >= 0; i--)
        {
            int* entry = entries + i * 5;
            uint field1 = entry[1]; // +0x04
            uint field2 = entry[2]; // +0x08
            uint field3 = entry[3]; // +0x0C
            uint field4 = entry[4]; // +0x10

            // Compute key = field1 * 33^3 + field2 * 33^2 + field3 * 33 + field4
            ulonglong intermediate = (ulonglong)field1 * 0x21 + (ulonglong)field2;
            ulonglong part1 = __allmul(intermediate, 0x21, 0);
            ulonglong combined = part1 + (ulonglong)field3;
            int key = __allmul(combined, 0x21, 0) + field4;

            // Debug output: level 2, key, 0, 1
            FUN_008142f0(2, key, 0, 1);
        }
    }
}