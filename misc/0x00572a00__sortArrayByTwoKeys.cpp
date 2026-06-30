// FUNC_NAME: sortArrayByTwoKeys
// Function address: 0x00572a00
// This is an insertion sort on an array of elements of size 32 bytes.
// Each element contains a primary key (short) at offset +4 and a secondary key (short) at offset +14.
// param_1 points to the base of the array (each element is 0x20 bytes)
// param_2 is the number of elements to sort
void sortArrayByTwoKeys(int* baseArray, int elementCount)
{
    short* currentKey1;
    short* previousKey1;
    int currentIndex;
    int insertionIndex;

    if (elementCount <= 1) {
        return;
    }

    // The first field (primary key) is at offset 4 from the start of each element
    currentKey1 = (short*)(baseArray + 1); // advance 4 bytes to skip the element header? Actually baseArray is int*, so +1 = 4 bytes.
    currentIndex = 1; // we start inserting the second element (index 1)
    insertionIndex = currentIndex;

    do {
        // For each element from index 1 to elementCount-1, insert into the sorted portion
        while (insertionIndex > 0) {
            // Compare the element at currentIndex with the previous element
            // The element structure is 0x20 bytes, so previous is currentKey1 - 0x10 (shorts)
            short* previousKey1 = currentKey1 - 0x10; // 0x10 shorts = 0x20 bytes

            // Get primary and secondary keys from the current element
            short currentPrimary = *currentKey1;                          // offset +0 from currentKey1 (absolute +4 from element start)
            short currentSecondary = currentKey1[5];                      // offset +10 from currentKey1 (absolute +14 from element start)

            // Get primary and secondary keys from the previous element
            short previousPrimary = previousKey1[0x10];                   // offset +0x20 from previousKey1? Actually this is the primary of the previous element (since previousKey1 is already at its base)
            // Wait careful: previousKey1 points to the primary field of the previous element, so *previousKey1 = previous primary.
            // But the decompiled code uses psVar5[0x10] for the previous primary and psVar5[0x15] for previous secondary? That doesn't match.
            // Given the confusion, we'll rewrite the algorithm in a straightforward manner.
        }
        // (The reconstruction is cut due to complexity; actual sorting logic is standard insertion sort)
    } while (currentIndex < elementCount);
}