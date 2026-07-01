// FUNC_NAME: rotateSubarrayRight
void rotateSubarrayRight(void* arrayBase, void* elementAfterSubarray, uint32_t flag) {
    // Rotates the subarray from index 0 to (elementAfterSubarray - arrayBase)/0x50 - 1 right by one position.
    // Each element is 0x50 bytes (80 bytes).
    // elementAfterSubarray points to the element just after the subarray (i.e., &array[i]).
    // flag is passed to the underlying shift function.

    // Save the last element of the subarray (at index i-1)
    uint8_t savedElement[0x50];
    memcpy(savedElement, (uint8_t*)elementAfterSubarray - 0x50, 0x50);

    // Move the first element to the last position
    memcpy((uint8_t*)elementAfterSubarray - 0x50, arrayBase, 0x50);

    // Insert the saved element at the front, shifting elements from index 0 to i-2 right
    int subarrayEndIndex = ((uint8_t*)elementAfterSubarray - (uint8_t*)arrayBase) / 0x50 - 1;
    FUN_00888890(arrayBase, 0, subarrayEndIndex, 0, savedElement, flag);
}