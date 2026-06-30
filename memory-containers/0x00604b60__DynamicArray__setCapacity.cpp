// FUNC_NAME: DynamicArray::setCapacity
// Function at 0x00604b60: Resize internal buffer to accommodate at least newCapacity elements. Only grows.
// This pointer in ESI (unaff_ESI) points to object with layout:
// +0x00: int* mData
// +0x04: int mSize
// +0x08: int mCapacity
void DynamicArray::setCapacity(uint newCapacity) {
    if (mCapacity >= newCapacity) {
        return; // No need to grow
    }

    // Allocate new buffer (size = newCapacity * sizeof(int))
    int* newData = (int*)allocateMemory(newCapacity * sizeof(int));

    // Copy existing elements (only mSize elements, not all of capacity)
    if (mData != nullptr) {
        for (uint i = 0; i < mSize; ++i) {
            if (newData != nullptr) {
                newData[i] = mData[i];
            }
        }
        // Free old buffer
        freeMemory(mData);
    }

    // Update pointers and capacity
    mData = newData;
    mCapacity = newCapacity;
}