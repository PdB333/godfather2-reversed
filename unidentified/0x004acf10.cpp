// FUNC_ADDRESS: 0x004acf10
// FUNC_NAME: EARSArray::push_back
// Role: Adds an element to a dynamic array with optional flag setting
// The array stores pointers/values as 4-byte entries. The flag at +0x18 controls some behavior (e.g., ownership of elements).
// Growth policy: capacity starts at 0, becomes 1, then doubles each time it's exceeded.

void __thiscall EARSArray::push_back(int thisPtr, undefined4 value, char setFlag)
{
    uint16_t* flags;
    undefined4* slot;
    int newCapacity;

    flags = (uint16_t*)(thisPtr + 0x18);
    if (setFlag != '\0') {
        *flags = *flags | 1;  // Set bit 0
    }

    // Clone or copy the value (likely a reference count increase or deep copy)
    undefined4 clonedValue = FUN_004dafd0(value);

    int currentSize = *(int*)(thisPtr + 0x24);
    int currentCapacity = *(int*)(thisPtr + 0x28);

    if (currentSize == currentCapacity) {
        // Need to grow
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        FUN_004ae9b0(newCapacity);  // Reallocate to new capacity
    }

    slot = (undefined4*)(*(int*)(thisPtr + 0x20) + *(int*)(thisPtr + 0x24) * 4);
    *(int*)(thisPtr + 0x24) = *(int*)(thisPtr + 0x24) + 1;  // Increment size
    if (slot != (undefined4*)0x0) {
        *slot = clonedValue;
    }

    // Increment a secondary counter at +0x1a (likely total pushes or version)
    *(short*)(thisPtr + 0x1a) = *(short*)(thisPtr + 0x1a) + 1;
    return;
}