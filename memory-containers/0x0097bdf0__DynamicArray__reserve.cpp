//FUNC_NAME: DynamicArray::reserve
// Function address: 0x0097bdf0
// Role: Reserves capacity for a dynamic array of 16-byte elements.
// Structure offsets: +0x00 data pointer, +0x04 element count, +0x08 capacity (in elements)
void __thiscall DynamicArray::reserve(int* thisPtr, uint newCapacity)
{
    int* oldData;
    int* newData;
    int* src;
    int* dst;
    uint i;

    // Only grow if new capacity is larger than current capacity
    if ((uint)thisPtr[2] < newCapacity) {
        // Allocate new block: newCapacity * 16 bytes
        newData = (int*)FUN_009c8e80(newCapacity << 4); // custom allocator

        // Copy existing elements if any
        if (thisPtr[0] != 0) {
            i = 0;
            if (thisPtr[1] != 0) {
                dst = newData;
                src = (int*)thisPtr[0];
                do {
                    // Copy 16 bytes (two 8-byte halves)
                    *dst = *src;
                    dst[1] = src[1];
                    i++;
                    src += 4; // advance by 16 bytes (4 ints)
                    dst += 4;
                } while (i < (uint)thisPtr[1]);
            }
            // Free old memory
            FUN_009c8f10(thisPtr[0]); // custom deallocator
        }

        // Update pointer and capacity
        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity;
    }
    // Note: element count (thisPtr[1]) remains unchanged
}