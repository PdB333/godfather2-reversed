// FUNC_NAME: heapSort (likely member of a container class, e.g., Array::heapSort)
// Address: 0x00889490
// Role: Heap sort implementation for an array of 32-bit values.
// Sorts the array in-place using a siftDown helper (FUN_00888940).
// Parameters:
//   data       - pointer to the first element of the array
//   end        - pointer to one past the last element (i.e., data + count)
//   compareFunc - comparator function or context passed to siftDown
void heapSort(undefined4* data, int end, undefined4 compareFunc)
{
    undefined4 lastValue;
    int size;
    undefined4* currentEnd;

    // Save the comparator for later use
    // (uVar1 = param_3)
    // (iVar2 = (end - (int)data) >> 2)  -> number of elements
    size = (end - (int)data) >> 2;

    // Only proceed if more than one element
    if (1 < size) {
        // Start from the last element
        currentEnd = (undefined4*)(end - 4);

        do {
            // Save the value of the last element (currentEnd)
            lastValue = *currentEnd;

            // Swap the first element into the last position
            *currentEnd = *data;

            // Sift down the value that was originally at the end (now at the root)
            // Parameters: data, start index 0, new size (size-1), flag 0,
            //             pointer to the value to sift down, comparator
            siftDown(data, 0, size - 1, 0, &lastValue, compareFunc);

            // Move the end pointer left (reduce heap size)
            currentEnd = currentEnd - 1;

            // Recalculate the number of elements from data to currentEnd (inclusive)
            size = ((4 - (int)data) + (int)currentEnd) >> 2;
        } while (1 < size);
    }
}