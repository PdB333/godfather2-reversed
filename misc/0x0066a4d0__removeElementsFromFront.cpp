// FUNC_NAME: removeElementsFromFront
// Function address: 0x0066a4d0
// Removes the first `count` elements from a dynamic array structure (capacity, size, data pointer).
// The structure layout: +0x00 size (int), +0x04 capacity (int), +0x08 flags (int), +0x0C data (int*)
void __fastcall removeElementsFromFront(int unused, int* arrayStruct, int count)
{
    int currentSize;
    int* dataPtr;
    int i;

    if (count <= 0) {
        return;
    }

    currentSize = arrayStruct[0];  // +0x00: size

    // If count >= size, just clear the entire array
    if (currentSize <= count) {
        arrayStruct[2] = 0;                     // +0x08: flags (reset)
        arrayStruct[0] = 0;                     // +0x00: size = 0
        _memset((void*)arrayStruct[3], 0, arrayStruct[1] * 4); // +0x0C: data, zero whole capacity
        return;
    }

    // Shift remaining elements left by `count` positions
    dataPtr = (int*)arrayStruct[3];  // +0x0C: data pointer
    int* srcPtr = dataPtr + count;
    int elementsToShift = currentSize - count;

    for (i = 0; i < elementsToShift; i++) {
        dataPtr[i] = srcPtr[i];
    }

    // Zero the vacated slots at the end
    for (i = elementsToShift; i < currentSize; i++) {
        dataPtr[i] = 0;
    }

    // Update size
    arrayStruct[0] = elementsToShift;
}