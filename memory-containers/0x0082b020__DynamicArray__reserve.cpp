// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity) {
    // Check if we need to grow (mCapacity at +0x08)
    if (mCapacity < newCapacity) {
        // Allocate new buffer (FUN_009c8e80 likely operator new[] or malloc)
        int* newData = (int*)FUN_009c8e80(newCapacity * 4);
        if (mData != 0) {
            // Copy existing elements (mCount at +0x04)
            uint count = mCount;
            for (uint i = 0; i < count; i++) {
                newData[i] = mData[i];
            }
            // Free old buffer (FUN_009c8f10 likely operator delete[] or free)
            FUN_009c8f10(mData);
        }
        mData = newData;     // +0x00
        mCapacity = newCapacity; // +0x08
    }
}