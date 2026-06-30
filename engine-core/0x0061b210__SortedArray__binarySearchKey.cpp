// FUNC_NAME: SortedArray::binarySearchKey
// Function at 0x0061b210: Binary search on a sorted array of 8-byte records (first uint is key).
// Returns the index of the element with key == *param_2, or -1 if not found.
// Class fields at +0x00: pointer to array, +0x04: element count.
int __thiscall SortedArray::binarySearchKey(int* this, uint* keyPtr)
{
    int count = this[1];          // +0x04: array size
    int low = -1;                 // lower bound -1 due to sentinel
    int high = count;             // upper bound
    int result = -1;

    if (count == 0) {
        return -1;
    }

    // Standard lower-bound binary search
    while (low + 1 < high) {
        int mid = (low + high) >> 1; // arithmetic shift for signed division by 2
        uint* array = (uint*)this[0]; // +0x00: pointer to array of 8-byte entries
        uint midKey = array[mid * 2]; // each element 8 bytes: key at offset 0

        if (midKey < *keyPtr) {
            low = mid;   // key is in the right half
        } else {
            high = mid;  // key is in the left half or equal
        }
    }

    // Check if we found an exact match
    if (high < count) {
        uint* array = (uint*)this[0];
        if (array[high * 2] == *keyPtr) {
            result = high;
        }
    }

    return result;
}