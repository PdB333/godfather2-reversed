// FUNC_NAME: PointerArray::reserve
void __thiscall PointerArray::reserve(int newCapacity) {
    // param_1 points to the object, param_2 is new capacity
    if ((unsigned int)capacity >= (unsigned int)newCapacity) {
        return; // nothing to do
    }

    // Allocate new memory block
    int** newData = (int**)allocateMemory(newCapacity * sizeof(int*));

    if (data != NULL) {
        // Copy old entries and update back-pointers
        for (unsigned int i = 0; i < count; ++i) {
            int* oldElem = data[i];
            if (newData != NULL) {
                newData[i] = oldElem;
                if (oldElem != NULL) {
                    // Update the back-pointer (at offset +8 bytes / +2 ints) to new location
                    *(int**)(oldElem + 2) = &newData[i];
                }
            } else {
                // If newData is NULL (should not happen), clear back-pointer
                if (oldElem != NULL) {
                    *(int**)(oldElem + 2) = NULL;
                }
            }
            // Clear old slot
            data[i] = NULL;
        }
        freeMemory(data);
    }

    // Update object state
    data = newData;
    capacity = newCapacity;
}