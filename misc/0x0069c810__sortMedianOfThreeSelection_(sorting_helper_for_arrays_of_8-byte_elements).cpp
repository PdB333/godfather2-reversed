// FUNC_NAME: sortMedianOfThreeSelection (sorting helper for arrays of 8-byte elements)
void sortMedianOfThreeSelection(int *pStart, int *pMid, int *pEnd) {
    int count = (pEnd - pStart) >> 3; // number of 8-byte elements in the range
    if (count > 0x28) { // 40 elements threshold
        // Compute indices for median-of-three pivot candidates
        int step = (count + (count >> 31 & 7)) >> 3; // approx count/8, rounded up for negative? but count is positive, so step = count/8
        int pivot1 = pStart + step * 8;
        int pivot2 = pMid - step * 8;
        int pivot3 = pEnd - step * 8;
        int pivot4 = pMid + step * 8;
        int pivot5 = pMid;
        int pivot6 = pEnd - step * 16;
        // Rearrange candidates: sort first, middle, last groups
        sortThreeElements(pStart, pivot1, pivot1 + step * 16); // sorts pStart, pivot1, and pivot1+2*step
        sortThreeElements(pivot2, pMid, pivot2 + step * 8);   // sorts pivot2, pMid, pivot2+step
        sortThreeElements(pivot6, pivot3, pEnd);              // sorts pivot6, pivot3, pEnd
        sortThreeElements(pivot1, pMid, pivot3);              // final median arrangement
    } else {
        // Small range: simple sort
        sortThreeElements(pStart, pMid, pEnd);
    }
}