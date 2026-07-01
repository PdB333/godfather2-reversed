// FUNC_NAME: heapSortStep
void heapSortStep(uint32_t* arrayStart, uint32_t* arrayEnd, int32_t compareContext) {
    int32_t sizeBytes = (int32_t)arrayEnd - (int32_t)arrayStart;
    // Perform heap sort by repeatedly swapping root (first 8 bytes) with last element
    // and then sifting down on the reduced heap.
    while (sizeBytes > 8) {
        uint32_t lastValHigh = *(uint32_t*)((int32_t)arrayStart + sizeBytes - 4);
        uint32_t lastValLow  = *(uint32_t*)((int32_t)arrayStart + sizeBytes - 8);
        // Swap first element (two 32-bit values) with the last element
        *(uint32_t*)((int32_t)arrayStart + sizeBytes - 8) = arrayStart[0];
        *(uint32_t*)((int32_t)arrayStart + sizeBytes - 4) = arrayStart[1];
        // Sift down the new root in the sub-heap of size (sizeBytes - 8) bytes
        siftDown(arrayStart, 0, (sizeBytes - 8) / 8, lastValLow, lastValHigh, compareContext);
        sizeBytes -= 8;
    }
}