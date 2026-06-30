// FUNC_NAME: heapSort8Byte
// Sorts an array of 8-byte (two 32-bit words) elements in descending order using heap sort.
// Parameters: start - pointer to first element, end - pointer past the last element.
// The heap property is maintained via a call to siftDown8Byte().

#include <cstdint>

// External heapify function: restores heap for a sub-array after a swap.
// Parameters: array, root index, element count, and the two words of the new root value.
extern void siftDown8Byte(uint32_t* array, int root, int numElements, uint32_t word0, uint32_t word1);

void heapSort8Byte(uint32_t* start, uint32_t* end)
{
    // Convert end pointer to byte offset from start
    int byteOffset = reinterpret_cast<int>(end) - reinterpret_cast<int>(start);
    // Number of 8-byte elements
    int elementCount = byteOffset >> 3;

    // Iterate down to a single element
    while (elementCount > 1)
    {
        // Save the last element (two 32-bit words)
        uint32_t lastWord0 = *reinterpret_cast<uint32_t*>(reinterpret_cast<int>(start) + byteOffset - 8);
        uint32_t lastWord1 = *reinterpret_cast<uint32_t*>(reinterpret_cast<int>(start) + byteOffset - 4);

        // Swap the first element with the last element
        *reinterpret_cast<uint32_t*>(reinterpret_cast<int>(start) + byteOffset - 8) = start[0];
        *reinterpret_cast<uint32_t*>(reinterpret_cast<int>(start) + byteOffset - 4) = start[1];
        start[0] = lastWord0;
        start[1] = lastWord1;

        // Reduce heap size (remove the last element, now containing the max)
        byteOffset -= 8;
        elementCount--;

        // Restore heap property for the reduced heap, passing the new root values
        siftDown8Byte(start, 0, elementCount, lastWord0, lastWord1);
    }
}