// FUNC_NAME: SortedArray::findIndex

// Binary search on a sorted array of 8-byte entries (key at offset 0, value at offset 4)
// Returns index of matching entry, or -1 if not found
class SortedArray
{
public:
    struct Entry
    {
        uint32_t key;   // +0x00
        uint32_t value; // +0x04
    };

    Entry* m_data;  // +0x00: pointer to sorted array of entries
    int32_t m_count; // +0x04: number of entries in the array

    // Searches for the entry with the given key using binary search.
    // __thiscall
    int32_t __thiscall findIndex(const uint32_t key) const
    {
        int32_t low  = -1;
        int32_t high = m_count; // exclusive upper bound

        if (m_count != 0)
        {
            int32_t midIdx;
            int32_t newHigh;

            do
            {
                midIdx = (low + high) >> 1; // integer division by 2
                newHigh = midIdx;

                // Compare key at midIdx with the search key
                if (m_data[midIdx].key < key)
                {
                    // key is in the upper half
                    newHigh = high;
                    low = midIdx;
                }

                high = newHigh;
            } while (low + 1 != high); // loop until low+1 == high

            // After loop, high is the insertion index (first element >= key)
            if (high < m_count && m_data[high].key == key)
            {
                return high; // found exact match
            }
        }

        return -1; // not found
    }
};