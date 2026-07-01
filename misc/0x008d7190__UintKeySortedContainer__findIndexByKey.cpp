// FUNC_NAME: UintKeySortedContainer::findIndexByKey
// Address: 0x008d7190
// Role: Binary search for a uint key in a sorted array of 0x2c-byte elements. Returns index or -1.

class UintKeySortedContainer {
public:
    // +0x00: pointer to array of elements (each 0x2c bytes, first uint is key)
    // +0x04: count of elements
    int __thiscall findIndexByKey(const uint* key) const;

private:
    uint* mArray;   // +0x00
    int   mCount;   // +0x04
};

// Offset: +0x00 (mArray) -> uint* (base of array)
// Offset: +0x04 (mCount) -> int
// Each element: 0x2c bytes, first field: uint key at offset 0x00 within element.

int __thiscall UintKeySortedContainer::findIndexByKey(const uint* key) const {
    int low = -1;
    int high = mCount;   // high is exclusive

    if (mCount != 0) {
        do {
            int mid = (high + low) >> 1;   // mid = low + (high-low)/2
            int newHigh = mid;

            if (mArray[mid * 0x2c / sizeof(uint)] < *key) {
                // Element at mid is less than key; search right half
                low = mid;
                newHigh = high;   // keep high unchanged
            }
            // else: newHigh = mid (narrow high boundary)

            high = newHigh;
        } while (low + 1 != high);   // continue while range is more than 1

        // At this point, high is the first index where array[high] >= key
        if (high < mCount && mArray[high * 0x2c / sizeof(uint)] == *key) {
            return high;
        }
    }

    return -1;
}