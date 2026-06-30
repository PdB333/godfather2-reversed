// FUNC_NAME: UintKeyArray::binarySearch
int __thiscall UintKeyArray::binarySearch(uint *key) {
    int count = this->count;                     // +0x04: number of elements in the array
    int low = -1;
    int high = count;
    int result = -1;

    if (count != 0) {
        int mid;
        int candidate;
        do {
            mid = (high + low) >> 1;             // integer average
            candidate = mid;
            if (*(uint *)(this->array + mid * 8) < *key) {  // +0x00: pointer to array of 8-byte entries (uint key + unknown)
                candidate = high;                // move lower bound up
                low = mid;
            }
            high = candidate;
        } while (low + 1 != candidate);

        // After loop, 'candidate' is the insertion point or match
        if (candidate < count && *(uint *)(this->array + candidate * 8) == *key) {
            result = candidate;
        }
    }
    return result;
}