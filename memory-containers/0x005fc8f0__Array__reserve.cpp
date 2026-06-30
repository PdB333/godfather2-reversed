// FUNC_NAME: Array::reserve
void __thiscall Array::reserve(uint newCapacity)
{
    int *pData;        // pointer to element data
    uint oldCount;     // number of elements currently stored
    uint oldCapacity;  // current allocated capacity

    // If current capacity is already sufficient, do nothing.
    if (this->capacity >= newCapacity)
        return;

    // Allocate new buffer: each element is 16 bytes.
    byte* newBuffer = gAlloc(newCapacity * 16);
    if (this->data != nullptr) {
        // Copy existing elements (oldCount elements, each 16 bytes).
        oldCount = this->count;
        if (oldCount != 0) {
            byte* src = (byte*)this->data;
            byte* dst = newBuffer;
            for (uint i = 0; i < oldCount; i++) {
                // Copy 16 bytes per element.
                *(uint64_t*)dst = *(uint64_t*)(src);
                *(uint64_t*)(dst + 8) = *(uint64_t*)(src + 8);
                src += 16;
                dst += 16;
            }
        }
        // Free the old buffer.
        gFree(this->data);
    }
    this->data = (int*)newBuffer;  // store new pointer (int* is placeholder for element type)
    this->capacity = newCapacity;   // update capacity
    return;
}