// FUNC_NAME: DynamicArray::initArraySlots
// Function address: 0x00667820
// Role: Initializes an array of dynamic slots, allocating memory for each slot's data buffer.
// Each slot has a structure: [capacity (int), elementSize (int), count (int), dataPtr (void*)]
// The array is terminated by a null pointer in the slot chain.

int DynamicArray::initArraySlots(int* slotArray)
{
    int slotIndex = 0;
    if (slotArray != nullptr) {
        int** currentSlotPtr = &slotArray; // pointer to current slot's first field
        int* currentSlot = slotArray;
        do {
            // Allocate buffer for slot data: 0x40 (64) elements of size 4
            void* buffer = _calloc(4, 0x40);
            currentSlot[3] = (int)buffer; // +0xC: dataPtr
            if (buffer == nullptr) {
                // Allocation failed - cleanup previously allocated slots
                if (slotIndex != 0) {
                    currentSlotPtr = &slotArray;
                    currentSlot = slotArray;
                    do {
                        slotIndex--;
                        if ((void*)currentSlot[3] != nullptr) {
                            _memset((void*)currentSlot[3], 0, currentSlot[0] * 4); // zero out buffer
                            _free((void*)currentSlot[3]);
                            currentSlot[3] = 0; // clear dataPtr
                            currentSlot[0] = 0; // reset capacity
                            currentSlot[1] = 0; // reset elementSize
                            currentSlot[2] = 0; // reset count
                        }
                        currentSlot = (int*)currentSlotPtr[1]; // move to next slot
                        currentSlotPtr++;
                    } while (slotIndex != 0);
                }
                return -2; // error code
            }
            currentSlotPtr++;
            currentSlot[0] = 0;  // +0x00: capacity = 0
            currentSlot[1] = 0x40; // +0x04: elementSize = 64 (0x40)
            currentSlot[2] = 0;  // +0x08: count = 0
            currentSlot = (int*)*currentSlotPtr; // advance to next slot in array
            slotIndex++;
        } while (currentSlot != nullptr);
    }
    return 0; // success
}