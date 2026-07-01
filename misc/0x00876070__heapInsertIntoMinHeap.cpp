// FUNC_NAME: heapInsertIntoMinHeap
void heapInsertIntoMinHeap(void* heapArray, int heapSize, int minIndex, int value, float key)
/*
  Inserts an element into a min-heap stored as an array of 8-byte entries.
  Each entry: [4 bytes value][4 bytes float key].
  The heap supports 0-based indexing with 'heapSize' as the slot to insert.
  'minIndex' is the root index (typically 0) used as a lower bound.
  This implements the standard bottom-up heap insertion (bubble-up) for a min-heap.
*/
{
    int currentIndex = heapSize;   // Index of the new element (initially at end)
    int parentIndex;
    float* parentKeyPtr;

    // While we haven't reached the root and the parent's key is greater than the new key
    while (minIndex < currentIndex) {
        parentIndex = (currentIndex - 1) / 2;  // Parent index
        parentKeyPtr = (float*)(heapArray + 4 + parentIndex * 8); // point to parent's key

        if (key <= *parentKeyPtr) {
            break;  // Heap property satisfied: parent is smaller or equal
        }

        // Move parent down to currentIndex
        *(int*)(heapArray + currentIndex * 8) = *(int*)(heapArray + parentIndex * 8);
        *(float*)(heapArray + 4 + currentIndex * 8) = *(float*)(heapArray + 4 + parentIndex * 8);
        
        currentIndex = parentIndex;  // Move up to parent
    }

    // Place new element at the found slot
    *(int*)(heapArray + currentIndex * 8) = value;
    *(float*)(heapArray + 4 + currentIndex * 8) = key;
}