// FUNC_NAME: BinarySearch3Uint
// Address: 0x00499300
// Performs binary search on an array of 12-byte (3-uint32) records.
// Returns pointer to the first element not less than the key (insertion point).
uint* BinarySearch3Uint(uint* begin, uint* end, uint* key)
{
    int size = (end - begin) / 3;  // Number of 3-uint elements
    uint* result = begin;

    while (size > 0)
    {
        int half = size / 2;
        uint* mid = begin + half * 3;

        // Compare three-uint key with mid element (lexicographically)
        bool less = false;
        if (*mid < *key)
            less = true;
        else if (*mid == *key)
        {
            if (mid[1] < key[1])
                less = true;
            else if (mid[1] == key[1] && mid[2] < key[2])
                less = true;
        }

        if (less)
        {
            begin = mid + 3;
            size = size - half - 1;
        }
        else
        {
            size = half;
        }
    }
    return begin;
}