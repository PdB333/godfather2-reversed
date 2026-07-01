// FUNC_NAME: addIndicesToArray
void __thiscall addIndicesToArray(void* thisObj, int groupIndex, int* array, bool* outSuccess)
{
    // thisObj+0x60 points to a global data structure with total slot count at +0x20
    int* dataPtr = *(int**)((char*)thisObj + 0x60);
    uint totalSlots = *(uint*)((char*)dataPtr + 0x20);

    uint startIndex = groupIndex * 0x2e;      // 0x2e = 46 slots per group
    uint endIndex = startIndex + 0x2e;

    do {
        if (endIndex <= startIndex) {
            break;
        }

        // Check if the current index is within valid bounds
        if (totalSlots <= startIndex) {
            *outSuccess = true;
            break;
        }

        // Get the element pointer for this global index
        void* element = getElementByGlobalIndex(startIndex);    // FUN_004bb610

        // Resize the dynamic array (element size 0x10) if capacity is insufficient
        int count = array[1];
        int capacity = array[2];
        if (count == capacity) {
            int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
            resizeDynamicArray(newCapacity);    // FUN_00407880
        }

        // Append the element to the array
        int newCount = array[1] + 1;
        array[1] = newCount;
        if (array[0] != 0) {
            assignDynamicArrayElement(element, newCount - 1);   // FUN_004d3b50 (stores element at index)
        }

        startIndex++;
    } while (true);

    // Signal success if the processed range exactly matches the total slots
    if (endIndex == totalSlots) {
        *outSuccess = true;
    }
}