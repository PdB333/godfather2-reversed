// FUNC_NAME: ResizableArray::reserve(unsigned int)
void __thiscall ResizableArray::reserve(unsigned int newCapacity) 
{
    // param_1 is this pointer, offsets: +0x00 = dataPtr (int*), +0x04 = size (uint), +0x08 = capacity (uint)
    int *thisPtr = (int *)this;

    if ((unsigned int)thisPtr[2] < newCapacity) {
        // Allocate new array of 8-byte elements (each element is two 32-bit values)
        int *newData = (int *)InternalAlloc(newCapacity * 8);
        if (thisPtr[0] != 0) {
            // Copy existing elements
            unsigned int idx = 0;
            int *dest = newData;
            if (thisPtr[1] != 0) {
                do {
                    if (dest != (int *)0x0) {
                        dest[0] = *(int *)(thisPtr[0] + idx * 8);
                        dest[1] = *(int *)(thisPtr[0] + 4 + idx * 8);
                    }
                    idx++;
                    dest += 2; // Advance by two ints (8 bytes)
                } while (idx < (unsigned int)thisPtr[1]);
            }
            // Free old array
            InternalFree((void *)thisPtr[0]);
        }
        // Update pointers and capacity
        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity;
    }
}