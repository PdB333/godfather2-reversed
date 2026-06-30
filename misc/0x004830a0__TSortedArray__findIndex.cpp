// FUNC_NAME: TSortedArray::findIndex

class TSortedArray {
public:
    struct Entry {
        uint32 key;    // +0x00
        uint32 value;  // +0x04
    };

    Entry* entries; // +0x00: pointer to sorted array of 8-byte entries
    int32 count;    // +0x04: number of entries in the array

    // Binary search for an entry with the given key.
    // Returns the index if found, -1 otherwise.
    int32 findIndex(uint32 key) const {
        int32 low = -1;
        int32 high = this->count;

        while (low + 1 != high) {
            int32 mid = (low + high) >> 1; // mid = (low + high) / 2
            if (this->entries[mid].key < key) {
                low = mid;
            } else {
                high = mid;
            }
        }

        if (high < this->count && this->entries[high].key == key) {
            return high;
        }
        return -1;
    }
};