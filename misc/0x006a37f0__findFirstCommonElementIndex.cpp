// FUNC_NAME: findFirstCommonElementIndex
int findFirstCommonElementIndex(short *arrayA, short *arrayB)
{
    int aIndex = 0;
    // Iterate through arrayA until a zero terminator is found
    if (*arrayA != 0) {
        do {
            int bIndex = 0;
            // Scan arrayB for the current element from arrayA
            if (*arrayB != 0) {
                short currentB = *arrayB;
                do {
                    // If the element from arrayA matches current element in arrayB, return index in arrayA
                    if (arrayA[aIndex] == currentB) {
                        return aIndex;
                    }
                    // Move to next element in arrayB
                    currentB = arrayB[bIndex + 1];
                    bIndex = bIndex + 1;
                } while (currentB != 0);
            }
            // Move to next element in arrayA
            aIndex = aIndex + 1;
        } while (arrayA[aIndex] != 0);
    }
    // No common element found
    return -1;
}