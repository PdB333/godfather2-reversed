// FUNC_NAME: FindArrayEntry
// Function address: 0x008e5eb0
// Role: Linear search for a 128-bit key in a dynamic array.
// The container structure: [0] = pointer to array of 16-byte entries, [4] = number of entries.

uint FindArrayEntry(int* container, int* key)
{
    uint count = container[1];
    if (count != 0)
    {
        int* entries = (int*)container[0];
        for (uint i = 0; i < count; i++)
        {
            // Compare all 4 ints (16 bytes)
            if (entries[0] == key[0] &&
                entries[1] == key[1] &&
                entries[2] == key[2] &&
                entries[3] == key[3])
            {
                return i;
            }
            entries += 4;
        }
    }
    return 0xFFFFFFFF;
}