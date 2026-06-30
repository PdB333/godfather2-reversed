// FUNC_NAME: Container::findIndexByKey
int Container::findIndexByKey(int key) {
    int count = *(int *)(this + 0xb4) - 1; // +0xb4: number of pairs
    if (count >= 0) {
        int *pairPtr = (int *)(*(int *)(this + 0xb0) + count * 8); // +0xb0: pointer to array of 8-byte pairs (key, value)
        do {
            if (*pairPtr == key) {
                return count;
            }
            count--;
            pairPtr -= 2; // move backwards by two ints (one pair)
        } while (count >= 0);
    }
    return -1;
}