// FUNC_NAME: RandomReplacementArray::insertElement

void __thiscall RandomReplacementArray::insertElement(int value, ArrayDescriptor* descriptor) {
    // Lock mutex associated with this object (param_1 = this)
    lockMutex(this);

    // Attempt random replacement of an existing element
    uint32_t i = 0;
    if (descriptor->mSize != 0) {
        do {
            int32_t r1 = generateRandomNumber(); // FUN_00791750
            int32_t r2 = generateRandomNumber();
            if (r1 < r2) {
                // Replace element at index i with the new value
                int32_t* elementPtr = getElementAtIndex(i); // FUN_006bee40
                *elementPtr = value;
                return; // Done after replacement
            }
            i++;
        } while (i < (uint32_t)descriptor->mSize);
    }

    // No replacement occurred; append at the end
    if (descriptor->mSize == descriptor->mCapacity) {
        // Need to grow the array
        int32_t newCapacity = (descriptor->mCapacity == 0) ? 1 : descriptor->mCapacity * 2;
        resizeArray(newCapacity); // FUN_006b1e10
    }

    // Store the value at the new slot
    int32_t* slot = descriptor->mData + descriptor->mSize;
    descriptor->mSize++;
    if (slot != nullptr) {
        *slot = value;
    }
}

// Note: ArrayDescriptor struct (param_3) contains:
// +0x00: int* mData       // pointer to dynamically allocated array
// +0x04: int   mSize      // current number of elements
// +0x08: int   mCapacity  // allocated capacity (number of elements)

// Helper functions:
// FUN_00791e70 - lockMutex (takes this pointer)
// FUN_00791750 - generateRandomNumber (returns int)
// FUN_006bee40 - getElementAtIndex (returns pointer to element at given index in the array)
// FUN_006b1e10 - resizeArray (reallocates array to new capacity)