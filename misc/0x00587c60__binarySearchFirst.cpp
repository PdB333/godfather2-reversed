// FUNC_NAME: binarySearchFirst
// Function at 0x00587c60: Binary search on an array of pointers to structures, returning pointer to first matching element.
// The array is sorted by a key extracted from each structure. The key is either the first int or second int
// depending on a flag at offset 0xB (byte) and the value of the first int.
// Parameters: array (pointer to array of pointers), size (number of elements), key (value to search for).
// Returns pointer to the array slot containing the matching pointer, or 0 if not found.

int* __fastcall binarySearchFirst(int** array, int size, int key)
{
    int low = 0;
    int high = size;

    while (low < high)
    {
        int mid = (low + high) >> 1;
        int* entry = array[mid];

        // Determine the key for this entry
        int entryKey;
        if (((*(unsigned char*)(entry + 0xB) & 0x20) == 0) || (*entry < 2))
        {
            entryKey = *entry; // first int
        }
        else
        {
            entryKey = entry[1]; // second int
        }

        if (entryKey < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }

    if (low < size)
    {
        int* entry = array[low];
        int entryKey;
        if (((*(unsigned char*)(entry + 0xB) & 0x20) == 0) || (*entry < 2))
        {
            entryKey = *entry;
        }
        else
        {
            entryKey = entry[1];
        }

        if (entryKey == key)
        {
            // Scan backwards to find the first occurrence (in case of duplicates)
            while (low > 0)
            {
                int* prevEntry = array[low - 1];
                int prevKey;
                if (((*(unsigned char*)(prevEntry + 0xB) & 0x20) == 0) || (*prevEntry < 2))
                {
                    prevKey = *prevEntry;
                }
                else
                {
                    prevKey = prevEntry[1];
                }
                if (prevKey != key)
                    break;
                low--;
            }
            return &array[low];
        }
    }
    return 0;
}