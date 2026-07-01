// FUNC_NAME: SortedArray::findKeyIndex
int __thiscall SortedArray::findKeyIndex(int* this, uint* keyPtr)
{
    int count = this[1];          // +0x04: number of elements
    int low = -1;
    int high = count;
    int result = -1;

    if (count != 0) {
        int currentHigh = high;
        do {
            int mid = (currentHigh + low) >> 1;  // mid = (low + high) / 2
            int newLow = mid;
            if (*(uint*)(this[0] + mid * 8) < *keyPtr) {
                newLow = currentHigh;
                low = mid;
            }
            currentHigh = newLow;
        } while (low + 1 != currentHigh);

        if (currentHigh < count && *(uint*)(this[0] + currentHigh * 8) == *keyPtr) {
            result = currentHigh;
        }
    }
    return result;
}