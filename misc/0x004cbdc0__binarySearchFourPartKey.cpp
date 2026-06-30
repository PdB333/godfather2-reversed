// FUNC_NAME: binarySearchFourPartKey
int binarySearchFourPartKey(const uint32_t *key, uint32_t **entries, int count)
{
    // Binary search on an array of pointers to FourKeyEntry structs sorted by
    // 4-part key (fields at offsets +0x04, +0x08, +0x0C, +0x10).
    // Returns index of exact match or -1 if not found.
    if (count > 0)
    {
        uint32_t key0 = key[0];
        int low = -1;
        int high = count;

        do
        {
            int mid = (low + high) / 2; // floor((low+high)/2)
            uint32_t *entry = entries[mid];
            int newLow = mid;

            // Compare primary key (offset +0x04)
            if (key0 <= entry[1]) // entry[1] is field at +0x04
            {
                if (entry[1] <= key0) // equal so far, check secondary keys
                {
                    // Compare secondary key (+0x08)
                    if (entry[2] < key[1]) // entry[2] is field at +0x08
                    {
                        goto continueLoop;
                    }
                    if (entry[2] <= key[1])
                    {
                        // Compare tertiary key (+0x0C)
                        if (entry[3] < key[2])
                        {
                            goto continueLoop;
                        }
                        if (entry[3] <= key[2])
                        {
                            // Compare quaternary key (+0x10)
                            if (entry[4] < key[3]) // entry[4] is field at +0x10
                            {
                                goto continueLoop;
                            }
                            // If all keys equal, default is to keep mid as candidate
                        }
                    }
                }
                // If key0 < entry[1] or all keys equal, shift search to left half
                newLow = low;
                high = mid;
            }
            // If key0 > entry[1], the loop continues with low = mid, high unchanged
continueLoop:
            low = newLow;
        } while (low + 1 < high);

        // After loop, check if entry at 'high' is an exact match
        if (high != count)
        {
            uint32_t *entry = entries[high];
            if (entry[1] == key0 &&
                entry[2] == key[1] &&
                entry[3] == key[2] &&
                entry[4] == key[3])
            {
                return high;
            }
        }
    }
    return -1;
}