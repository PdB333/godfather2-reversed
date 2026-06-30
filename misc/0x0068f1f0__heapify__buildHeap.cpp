// FUNC_NAME: heapify::buildHeap
// Function address: 0x0068f1f0
// Role: Builds a heap from an array of 4-byte elements. 
// param_1: Pointer to start of array (int*)
// param_2: Pointer to end of array (one past last element)
// param_3: Additional context (e.g., comparator or extra data) passed to siftDown
void buildHeap(int* arrayStart, int* arrayEnd, int context) {
    int elementCount = (arrayEnd - arrayStart); // Number of elements (each 4 bytes => pointer difference already in element count)
    int startingIndex = elementCount >> 1;      // Start from middle (last parent)
    while (startingIndex > 0) {
        startingIndex--;
        int element = arrayStart[startingIndex];
        siftDown(arrayStart, startingIndex, elementCount, element, context);
    }
}