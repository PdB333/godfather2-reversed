// FUNC_NAME: heapSortExtractPhase
// Function address: 0x0069cd10
// Role: Extraction phase of heap sort for 8-byte elements (two uint32_t).
// Repeatedly swaps the root (first element) with the last element, then sifts down the new root.
// The array is assumed to already be a max-heap (built elsewhere).
// param_1: pointer to array of 8-byte elements (uint32_t pairs)
// param_2: pointer to one past the last element (end pointer)
void heapSortExtractPhase(uint32_t* array, uint32_t* end)
{
    int byteSize = (int)end - (int)array; // total bytes in the array

    // Loop while there are more than 1 element (byteSize/8 > 1)
    for (; byteSize > 8; byteSize -= 8)
    {
        // Save the last element (two uint32_t values)
        uint32_t last0 = *(uint32_t*)((int)array + byteSize - 8);
        uint32_t last1 = *(uint32_t*)((int)array + byteSize - 4);

        // Swap the first element (root) with the last element
        *(uint32_t*)((int)array + byteSize - 8) = array[0];
        *(uint32_t*)((int)array + byteSize - 4) = array[1];

        // Sift down the new root (which was the original last element) into the heap of size (byteSize/8 - 1)
        // FUN_0069c6c0 is the siftDown function
        siftDown(array, 0, (byteSize - 8) / 8, last0, last1);
    }
}