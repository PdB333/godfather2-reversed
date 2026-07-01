// FUNC_NAME: SortedArray::binarySearch
int __thiscall SortedArray::binarySearch(int *this, uint *key)
{
    int count = this[1]; // +0x04: number of elements in the array
    int low = -1;
    int high = count;
    int mid;
    int result;

    if (count == 0) {
        return -1;
    }

    do {
        mid = (low + high) >> 1;
        result = mid;
        if (*(uint *)(this[0] + mid * 0x18) < *key) { // compare key at offset 0 of each 0x18-byte element
            result = high;
            low = mid;
        }
        high = result;
    } while (low + 1 != high);

    if (high < count && *(uint *)(this[0] + high * 0x18) == *key) {
        return high;
    }
    return -1;
}