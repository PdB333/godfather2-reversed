// FUNC_NAME: Array::push_back
void __thiscall Array::push_back(undefined4 value)
{
    int currentSize = *(int *)(this + 0x68);   // +0x68: current number of elements
    int capacity = *(int *)(this + 0x6c);      // +0x6c: allocated capacity

    if (currentSize == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Grow the internal buffer to newCapacity
        FUN_00917a50(newCapacity); // likely Array::grow(newCapacity)
    }

    // Write the new element at the end of the array
    undefined4 *dataPtr = *(undefined4 **)(this + 0x64); // +0x64: pointer to element array
    dataPtr[currentSize] = value;
    *(int *)(this + 0x68) = currentSize + 1; // increment size
}