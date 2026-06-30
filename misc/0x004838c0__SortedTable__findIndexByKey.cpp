// FUNC_NAME: SortedTable::findIndexByKey
// Address: 0x004838c0
// Binary search on a sorted table of 16-byte elements (first 4 bytes are key).
// Class layout:
// +0x00: void* elements (pointer to base of array)
// +0x04: int count (number of elements)
int __thiscall SortedTable::findIndexByKey(const uint* keyPtr)
{
    int low = -1;
    int high = this->count;
    if (high == 0)
        return -1;
    do {
        int mid = (low + high) >> 1;
        if (*(uint*)(this->elements + mid * 0x10) < *keyPtr) {
            low = mid;
        } else {
            high = mid;
        }
    } while (low + 1 != high);
    if (high < this->count && *(uint*)(this->elements + high * 0x10) == *keyPtr) {
        return high;
    }
    return -1;
}