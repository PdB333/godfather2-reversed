// FUNC_NAME: DynamicArray::reserve
class DynamicArray {
    int* mData;      // +0x00: pointer to element array
    int  mCount;     // +0x04: number of elements currently stored
    int  mCapacity;  // +0x08: allocated capacity (max elements)
    // Each element is 12 bytes (e.g., struct of three ints)
public:
    void reserve(uint newCapacity);
};

void DynamicArray::reserve(uint newCapacity) {
    // Only grow if requested capacity exceeds current
    if (mCapacity >= newCapacity)
        return;

    // Allocate new memory: newCapacity * elementSize (12 bytes)
    int* newData = (int*)malloc(newCapacity * 12);
    if (!newData)
        return; // allocation failure (original code does not check)

    // Copy existing elements (if any)
    if (mData != nullptr) {
        for (uint i = 0; i < (uint)mCount; i++) {
            int* src = &mData[i * 3];      // each element occupies 3 ints
            int* dst = &newData[i * 3];
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
        }
    }

    // Free old memory and update pointer/capacity
    free(mData);
    mData = newData;
    mCapacity = newCapacity;
}