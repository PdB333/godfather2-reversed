// FUNC_NAME: partitionArray
// Rearranges elements in an array segment based on a predicate (likely used by quicksort or partitioning).
// Parameters: first and last are inclusive pointers to 4-byte elements.
// Uses predicate function at 0x00587780 and swap function at 0x00588e00.
void partitionArray(int* first, int* last) {
    if (first == last) return; // empty range

    int* leftWalker = first + 1;
    if (leftWalker == last) return; // only one element

    int* rightWalker = first + 2; // scans forward from third element

    do {
        // Check predicate on the pivot (first element)
        int pivotResult = predicate(*first);
        if (pivotResult == 0) {
            // If pivot fails predicate, check element at rightWalker-2 (two positions before current scanner)
            int elemResult = predicate(*(rightWalker - 2));
            int* scanBack = rightWalker - 2;
            if (elemResult != 0) {
                // Scan backward while elements satisfy predicate
                do {
                    int* found = scanBack;
                    int result = predicate(*(found - 1));
                    scanBack = found - 1;
                } while (result != 0);
                // If found position is distinct from leftWalker and not adjacent, swap
                if (found != leftWalker && leftWalker != rightWalker) {
                    swap(found, rightWalker);
                }
            }
        } else if (first != leftWalker && leftWalker != rightWalker) {
            // Pivot satisfies predicate: swap pivot with current rightWalker element
            swap(first, rightWalker);
        }
        leftWalker++;
        rightWalker++;
    } while (leftWalker != last);
}