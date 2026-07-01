// FUNC_NAME: destroySlotArray
// Reconstructed function at 0x0098b790
// Processes a range of 16-byte slots, destroying non-null objects.
// param_1: pointer to an integer that holds the current slot address (updated iteratively)
// param_2: start address of the slot range
// param_3: end address of the slot range
// param_4: initial value for *param_1 (should be start address)
// Returns: param_1 (pointer to updated iterator)
int* destroySlotArray(int* iteratorPtr, int startAddr, int endAddr, int initialValue)
{
    *iteratorPtr = initialValue; // Set the iterator to the starting slot
    if (startAddr != endAddr) {
        do {
            // If the first field (object pointer) of the current slot is non-null, destroy it
            if (*iteratorPtr != 0) {
                destroySlotElement(startAddr); // Destroys the object at the slot
            }
            // Advance iterator and current address by 16 bytes (slot size)
            *iteratorPtr += 0x10;
            startAddr += 0x10;
        } while (startAddr != endAddr);
    }
    return iteratorPtr;
}