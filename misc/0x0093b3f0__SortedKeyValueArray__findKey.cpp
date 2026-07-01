// FUNC_NAME: SortedKeyValueArray::findKey
// Function at 0x0093b3f0: Binary search for a key in a sorted key-value array.
// Class structure: +0x00: uint* data (array of 8-byte entries: uint key, uint value)
//                   +0x04: int count (number of entries)
// Returns index if found, -1 otherwise.

typedef unsigned int uint;

struct SortedKeyValueArray {
    uint* data;   // +0x00
    int count;    // +0x04

    // Binary search for key, returning index or -1
    int findKey(uint* keyPtr) const {
        int low = -1;
        int high = count;

        while (low + 1 != high) {
            int mid = (low + high) >> 1; // (low+high)/2
            uint midKey = data[mid * 2]; // key is first uint in each 8-byte entry
            if (midKey < *keyPtr) {
                low = mid;
            } else {
                high = mid;
            }
        }

        int result = -1;
        if (high < count) {
            if (data[high * 2] == *keyPtr) {
                result = high;
            }
        }
        return result;
    }
};