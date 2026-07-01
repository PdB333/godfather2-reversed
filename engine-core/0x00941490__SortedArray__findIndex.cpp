// FUNC_NAME: SortedArray::findIndex
class SortedArray {
public:
    uint32_t* m_data;  // +0x00: pointer to sorted array of uint32 keys (actually 8-byte entries, but only first 4 used)
    int m_count;       // +0x04: number of elements

    // Performs binary search for a key, returns index if found, -1 otherwise.
    // Algorithm: lower-bound search, returns the first index >= key (if key present).
    int findIndex(uint32_t key) const {
        int result = -1;
        int low = -1;
        int high = m_count;
        if (high != 0) {
            do {
                int mid = (low + high) >> 1;
                int newHigh = mid;
                if (m_data[mid] < key) {
                    newHigh = high;  // keep high unchanged when going right
                    low = mid;
                }
                high = newHigh;
            } while (low + 1 != high);
            // After loop, high is the insertion point (first index >= key)
            if (high < m_count && m_data[high] == key) {
                result = high;
            }
        }
        return result;
    }
};