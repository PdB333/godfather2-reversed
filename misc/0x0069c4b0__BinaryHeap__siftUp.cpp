// FUNC_NAME: BinaryHeap::siftUp
void BinaryHeap::siftUp(uint32_t* heapArray, int holeIndex, int rootIndex, uint32_t newKey, uint32_t newValue)
{
    // holeIndex is the position of the new element (to be inserted), rootIndex is the first valid index (typically 0)
    // Each heap entry is 8 bytes: first 4 bytes = key (priority), next 4 bytes = value
    // The key's low byte is used for comparison (min-heap: smaller key = higher priority)

    if (holeIndex <= rootIndex) {
        // No sifting needed if at root
        return;
    }

    do {
        int parentIndex = (holeIndex - 1) / 2; // parent in a binary heap (0-based)
        // Compare new key's low byte with parent's low byte
        if ((newKey & 0xFF) <= (heapArray[parentIndex * 2] & 0xFF)) {
            break; // heap property satisfied
        }
        // Move parent entry down to the hole
        heapArray[holeIndex * 2]     = heapArray[parentIndex * 2];
        heapArray[holeIndex * 2 + 1] = heapArray[parentIndex * 2 + 1];
        holeIndex = parentIndex;
    } while (holeIndex > rootIndex); // continue while hole is not at the root

    // Place new entry at the final hole position
    heapArray[holeIndex * 2]     = newKey;
    heapArray[holeIndex * 2 + 1] = newValue;
}