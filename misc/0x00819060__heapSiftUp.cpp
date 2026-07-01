// FUNC_NAME: heapSiftUp
void heapSiftUp(void* baseArray, int currentIndex, int startIndex, uint64_t newDataLow, uint32_t newDataHigh, CompareFunc comparator)
{
    // Sift up the new element from currentIndex towards startIndex.
    // Each element is 12 bytes (0xC): 8-byte low part, 4-byte high part.
    // comparator returns true if the parent should be moved down (i.e., parent > new element in some ordering).
    while (startIndex < currentIndex)
    {
        int parentIndex = (currentIndex - 1) / 2;
        uint8_t* parentElem = (uint8_t*)baseArray + parentIndex * 0xC;

        // Compare the parent element (as 8+4) with the new element.
        // The comparison function takes pointers to both elements.
        if (!comparator(parentElem, &newDataLow))
            break;

        // Move parent down to current position.
        uint8_t* currentElem = (uint8_t*)baseArray + currentIndex * 0xC;
        *(uint64_t*)currentElem = *(uint64_t*)parentElem;
        *(uint32_t*)(currentElem + 8) = *(uint32_t*)(parentElem + 8);

        currentIndex = parentIndex;
    }

    // Place the new element at the final position.
    uint8_t* dest = (uint8_t*)baseArray + currentIndex * 0xC;
    *(uint64_t*)dest = newDataLow;
    *(uint32_t*)(dest + 8) = newDataHigh;
}