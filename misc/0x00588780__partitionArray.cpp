// FUNC_NAME: partitionArray
void partitionArray(int* startPtr, int* endPtr)
{
    int* currentPtr;
    int* nextPtr;
    int* scanPtr;
    int* foundPtr;
    char cmpResult;

    // If start and end are the same or adjacent (no elements between), nothing to do
    if ((startPtr == endPtr) || (startPtr + 1 == endPtr)) {
        return;
    }

    currentPtr = startPtr + 1; // first element after pivot (pivot at startPtr)
    nextPtr = startPtr + 2;    // second element after pivot

    // Iterate through the array from the second element onward
    while (currentPtr != endPtr) {
        cmpResult = compareFunc(); // compare current element? (no argument - likely uses global pivot)
        if (cmpResult == 0) {
            // Element at nextPtr is "less" (or equal?) - need to find a "greater" element to swap
            cmpResult = compareFunc();
            scanPtr = nextPtr - 2; // start scanning from the element before nextPtr
            if (cmpResult != 0) {
                // Scan backwards to find an element that is "less" (returns 0)
                do {
                    foundPtr = scanPtr;
                    cmpResult = compareFunc();
                    scanPtr = foundPtr - 1;
                } while (cmpResult != 0);
                // Swap the found "less" element with the current "greater" element
                if ((foundPtr != currentPtr) && (currentPtr != nextPtr)) {
                    swapElements(foundPtr, nextPtr);
                }
            }
        } else {
            // Element at nextPtr is "greater" - swap pivot (startPtr) with it if not adjacent
            if ((startPtr != currentPtr) && (currentPtr != nextPtr)) {
                swapElements(startPtr, nextPtr);
            }
        }
        currentPtr++;
        nextPtr++;
    }
}