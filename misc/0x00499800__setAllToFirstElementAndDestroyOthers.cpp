// FUNC_NAME: setAllToFirstElementAndDestroyOthers
void setAllToFirstElementAndDestroyOthers(void* start, void* end) {
    // start: pointer to the first element (0x0)
    // end: pointer to one past the last element (0x4 bytes each)
    // This loop copies the first element over all subsequent elements
    // and calls a destruction function on the overwritten values.
    int byteOffset = (char*)end - (char*)start; // initial offset in bytes
    while (byteOffset / sizeof(int) > 1) { // while more than one element remains
        // Point to the current last element
        int* lastElement = (int*)((char*)start + byteOffset - sizeof(int));
        int valueToDestroy = *lastElement;
        // Overwrite last element with the first element's value
        *lastElement = *(int*)start;
        // Destructor call (0 is a dummy context or slot index)
        FUN_00499930(0, valueToDestroy);
        // Move end pointer left by one element
        byteOffset -= sizeof(int);
    }
}