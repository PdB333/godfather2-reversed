// FUNC_NAME: siftDown (heap sift-down operation)
#include <cstdint>

// Forward declaration of the sift-step helper (called from FUN_0068eec0)
// This function likely performs comparison and swaps between parent/child in the heap
void siftDownStep(uint32_t* array, int parentIndex, int childIndex, uint32_t value, uint32_t userData);

/**
 * Performs a sift-down operation on a heap stored in 'array'.
 * The heap is stored as contiguous 4-byte elements.
 *
 * @param array   Pointer to the base of the heap array.
 * @param endPtr  Pointer to one-past-the-end of the array (byte address).
 * @param userData Opaque context passed through to the sift step (e.g., comparator).
 */
void siftDown(uint32_t* array, uint32_t* endPtr, uint32_t userData)
{
    // Convert pointer difference to byte size
    int sizeInBytes = reinterpret_cast<int>(endPtr) - reinterpret_cast<int>(array);
    int numElements = sizeInBytes >> 2; // Divide by 4 (size of uint32_t)

    // While there are more than 1 element (heap has a child to sift into)
    while (1 < numElements)
    {
        // Grab the last element (at index numElements-1)
        uint32_t lastValue = array[numElements - 1];

        // Swap the root (first element) with the last element
        array[numElements - 1] = array[0];

        // Notify the sift step: we are moving 'lastValue' from the root into its correct position
        siftDownStep(array, 0, numElements - 1, lastValue, userData);

        // Reduce size by one element and continue sifting down
        sizeInBytes -= 4;
        numElements = sizeInBytes >> 2;
    }
}