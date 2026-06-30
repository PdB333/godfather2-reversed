// FUNC_NAME: PairArray::addPair
void PairArray::addPair(int first, int second)
{
    int count = *(int *)(this + 0xB4);
    int capacity = *(int *)(this + 0xB8);
    if (count == capacity) {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        // Grow the internal buffer (realloc function at 0x004496b0)
        PairArray::resizeArray(capacity);
    }
    int *slot = *(int **)(this + 0xB0) + count * 2; // each element is 8 bytes (two ints)
    if (slot != nullptr) {
        *slot = 0xfe16702f; // debug sentinel or placeholder (overwritten below)
    }
    // After potential resize, re-fetch slot pointer (buffer may have moved)
    slot = *(int **)(this + 0xB0) + count * 2;
    *(int *)(this + 0xB4) = count + 1; // increment count
    slot[0] = first;
    slot[1] = second;
}