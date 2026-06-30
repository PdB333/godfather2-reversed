// FUNC_NAME: introsort_loop
void introsort_loop(void* first, void* last, int depthLimit)
{
    int numElements = (int)((char*)last - (char*)first) >> 2; // /4 for 4-byte elements

    do {
        if (numElements < 33) {
            if (numElements > 1 && first != last) {
                insertionSort(first, last);
            }
            return;
        }

        if (depthLimit < 1) {
            if (numElements > 32) {
                // Align size to 4 bytes and check for at least one element (>= 8 bytes? Actually > 4 means >= 8 bytes => >=2 elements)
                if (((int)((char*)last - (char*)first) & 0xFFFFFFFC) > 4) {
                    heapSortBuild();
                }
                heapSortLoop();
            }
            return;
        }

        void* leftEnd;   // End of left partition
        void* rightStart; // Start of right partition
        partition(&leftEnd, &rightStart, first, last);

        // Reduce depth limit: depthLimit = depthLimit / 2 + (depthLimit/2)/2
        depthLimit = depthLimit / 2 + (depthLimit / 2) / 2;

        // Compare byte sizes of left and right subarrays (aligned to 4)
        if (((int)((char*)leftEnd - (char*)first) & 0xFFFFFFFC) < ((int)((char*)last - (char*)rightStart) & 0xFFFFFFFC)) {
            introsort_loop(first, leftEnd, depthLimit);
            first = rightStart;
        } else {
            introsort_loop(rightStart, last, depthLimit);
            last = leftEnd;
        }

        numElements = (int)((char*)last - (char*)first) >> 2;
    } while (true);
}