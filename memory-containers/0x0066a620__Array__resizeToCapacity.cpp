// FUNC_NAME: Array::resizeToCapacity
// Function address: 0x0066a620
// Role: Reallocates the data buffer to match the capacity, then updates size to capacity.
// Struct layout: this[0] = capacity, this[1] = size, this[2] = unknown (not used), this[3] = data pointer

int __thiscall Array::resizeToCapacity()
{
    int* thisPtr = reinterpret_cast<int*>(this);
    int capacity = thisPtr[0];      // +0x00: capacity
    int size = thisPtr[1];          // +0x04: current size

    if (size != capacity)
    {
        void* oldData = reinterpret_cast<void*>(thisPtr[3]); // +0x0C: data pointer
        void* newData = _realloc(oldData, capacity * 4);     // 4 bytes per element
        if (newData == nullptr)
        {
            return -2;  // 0xFFFFFFFE: allocation failure
        }
        thisPtr[3] = reinterpret_cast<int>(newData);  // update data pointer
        thisPtr[1] = capacity;                         // set size to new capacity
    }
    return 0;
}