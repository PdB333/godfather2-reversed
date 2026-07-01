// FUN_NAME: heapBuild

void __cdecl heapBuild(int* basePtr, int* endPtr, int compareObject) {
    int tempValue;
    int count = (endPtr - basePtr) >> 2; // Number of elements (4 bytes each)
    if (count > 1) {
        int heapIndex = ((count - 2) >> 1) + 1; // Last parent index (1-based)
        do {
            tempValue = *(basePtr + (heapIndex - 1));  // Store current parent value
            siftDown(basePtr, heapIndex, count, heapIndex, &tempValue, compareObject);
            heapIndex--;
        } while (heapIndex != 0);
    }
}