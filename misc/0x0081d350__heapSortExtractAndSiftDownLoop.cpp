// FUNC_NAME: heapSortExtractAndSiftDownLoop
void heapSortExtractAndSiftDownLoop(void* arrayStart, void* arrayEnd, uint32_t context) {
    // param_1 = arrayStart, param_2 = arrayEnd, param_3 = context
    // Compute total size in bytes (offset from start to end)
    int32_t sizeBytes = (int32_t)arrayEnd - (int32_t)arrayStart;

    // Loop while more than one element remains (size > 12 bytes)
    while (sizeBytes / 12 > 1) {
        // Read the last element (which will become the new root after extraction)
        // Element consists of 8 bytes (key?) followed by 4 bytes (value?) — total 12 bytes
        uint64_t lastKey   = *(uint64_t*)((int32_t)arrayStart + sizeBytes - 12);
        uint32_t lastValue = *(uint32_t*)((int32_t)arrayStart + sizeBytes - 4);

        // Move the first element (current max) to the end of the heap
        *(uint64_t*)((int32_t)arrayStart + sizeBytes - 12) = *(uint64_t*)arrayStart;
        *(uint32_t*)((int32_t)arrayStart + sizeBytes - 4) = *(uint32_t*)((int32_t)arrayStart + 8);

        // Sift down the new root (the extracted element) into the remaining heap
        FUN_0081aee0(
            arrayStart,               // heap base
            0,                        // root index
            (sizeBytes - 12) / 12,    // new heap size in elements (excluding extracted one)
            lastKey,                  // value to place at root
            lastValue,
            context                   // opaque context (e.g., comparator data)
        );

        // Reduce heap size by one element
        sizeBytes -= 12;
    }
}