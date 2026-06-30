// FUNC_NAME: Array::reserve
// This function is likely a member of a dynamic array class (e.g., EARSArray or similar),
// managing elements of size 8 bytes. It resizes the internal buffer if the requested capacity is larger.

void Array::reserve(uint newCapacity)
{
    // this pointer implicitly in ESI, fields:
    // +0x00: void* data - pointer to element array
    // +0x04: int size - number of elements currently stored
    // +0x08: int capacity - allocated capacity (in elements)
    int *thisPtr = reinterpret_cast<int*>(this);
    int *data = reinterpret_cast<int*>(thisPtr[0]); // offset +0x00
    int size = thisPtr[1];        // offset +0x04
    int capacity = thisPtr[2];    // offset +0x08

    if ((uint)capacity < newCapacity) {
        // Allocate new buffer: each element is 8 bytes (two 4-byte fields)
        void *newData = malloc(newCapacity * 8);
        if (data != nullptr && size != 0) {
            // Copy existing elements from old buffer to new buffer
            uint i = 0;
            void *dst = newData;
            do {
                if (dst != nullptr) {
                    // Copy two ints (8 bytes) per element
                    *(int *)dst = data[0];
                    *(int *)((char *)dst + 4) = data[1];
                }
                i++;
                data += 2;       // advance by 8 bytes
                dst = (char *)dst + 8;
            } while (i < (uint)size);
        }
        // Free the old buffer
        free(thisPtr[0]);
        // Update pointers and capacity
        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity;
    }
}