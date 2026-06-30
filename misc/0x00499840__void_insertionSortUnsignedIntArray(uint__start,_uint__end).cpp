// FUNC_NAME: void insertionSortUnsignedIntArray(uint* start, uint* end)
void insertionSortUnsignedIntArray(uint* start, uint* end)
{
    uint* currentPtr = start + 1; // Start from second element
    if (currentPtr != end) {
        do {
            uint currentValue = *currentPtr;
            if (currentValue < *start) {
                // Insert at front: shift entire sorted block right by one
                int shiftCount = currentPtr - start; // Number of elements in sorted block (including start)
                if (shiftCount > 0) {
                    _memmove_s(currentPtr + (1 - shiftCount), shiftCount * 4, start, shiftCount * 4);
                }
                *start = currentValue;
            }
            else {
                // Scan backwards to find insertion point
                uint previousValue = currentPtr[-1];
                uint* scanPtr = currentPtr;
                while (currentValue < previousValue) {
                    *scanPtr = previousValue;
                    previousValue = scanPtr[-2];
                    scanPtr = scanPtr - 1;
                }
                *scanPtr = currentValue;
            }
            currentPtr = currentPtr + 1;
        } while (currentPtr != end);
    }
}