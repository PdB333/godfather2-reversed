// FUN_00435840: SortedArray::binarySearch

// Structure representing a 8-byte sorted key-value pair
struct KeyValuePair {
    uint32_t key;    // +0x00: sorted key
    uint32_t value;  // +0x04: associated value
};

// The object contains a pointer to the array and its size
// Offset: +0x00 -> KeyValuePair* data
// Offset: +0x04 -> int32_t size
class SortedArray {
public:
    // Binary search for the index of a given key.
    // Returns the index if found, -1 otherwise.
    int binarySearch(uint32_t key) const {
        int32_t size = this->size;
        int32_t low = -1;
        int32_t high = size;
        int32_t resultIdx = -1;

        if (size > 0) {
            do {
                int32_t mid = (low + high) >> 1;
                int32_t newHigh = mid;

                // If the key at mid is less than the search key, narrow to the right half
                if (this->data[mid].key < key) {
                    newHigh = high;
                    low = mid;
                }

                high = newHigh;
            } while (low + 1 != high); // standard binary search termination

            // After loop, 'high' is the candidate index
            if (high < size && this->data[high].key == key) {
                resultIdx = high;
            }
        }

        return resultIdx;
    }
};