// FUNC_NAME: buildHeap
// Function address: 0x0069c8a0
// Role: Build a binary heap from an array of 8-byte elements (two 4-byte fields).
// The array is defined by a base pointer (param_1) and a past-the-end pointer (param_2).
// The heap order is determined by the sift-down function FUN_0069c6c0.
// This function handles both positive and negative sizes (though sizes are positive in practice).

extern void siftDown(int base, int index, int size, int firstHalf, int secondHalf);

void buildHeap(int base, int end) {
    // Compute the number of 8-byte elements between base and end
    int size = (end - base) >> 3;
    
    // Compute the starting index for heapification:
    // floor(size/2) truncated toward zero, guaranteeing non-negative for positive size
    int startIndex = size - (size >> 31) >> 1;
    
    if (startIndex > 0) {
        // Iterate from startIndex down to 1 (inclusive), sifting each element
        int currentElementAddr = base + startIndex * 8;
        do {
            // Extract the two halves of the current element (8 bytes = two 4-byte ints)
            int* secondHalfPtr = (int*)(currentElementAddr - 4);
            int* firstHalfPtr = (int*)(currentElementAddr - 8);
            
            // Move to the previous element and decrement index
            currentElementAddr -= 8;
            startIndex--;
            
            // Sift down the element at the new currentIndex
            siftDown(base, startIndex, size, *firstHalfPtr, *secondHalfPtr);
        } while (startIndex > 0);
    }
}