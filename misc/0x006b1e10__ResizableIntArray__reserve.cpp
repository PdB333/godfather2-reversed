// FUNC_NAME: ResizableIntArray::reserve
/*
 * Function: 0x006b1e10
 * Role:      Expands the capacity of a dynamically allocated integer array if the requested size exceeds current capacity.
 *            Typical C++ vector-style grow operation.
 * Structure layout:
 *   +0x00: int* data (pointer to allocated memory)
 *   +0x04: int size (number of elements currently stored)
 *   +0x08: int capacity (maximum number of elements without reallocation)
 *
 * This function is called by many subsystems (networking, rendering, AI, etc.) to manage arrays of ints.
 */

void __thiscall ResizableIntArray::reserve(int* thisPtr, uint newCapacity) {
    if ((uint)thisPtr[2] < newCapacity) {
        // Allocate new block: newCapacity * sizeof(int) (4 bytes)
        int* newData = (int*)FUN_009c8e80(newCapacity * 4); // Likely malloc or engine allocator

        if (thisPtr[0] != 0) {
            uint i = 0;
            int* dest = newData;
            if (thisPtr[1] != 0) {
                do {
                    if (dest != (int*)0x0) {
                        *dest = *(int*)(thisPtr[0] + i * 4);
                    }
                    i = i + 1;
                    dest = dest + 1;
                } while (i < (uint)thisPtr[1]);
            }
            // Free old memory
            FUN_009c8f10(thisPtr[0]); // Likely free or operator delete
        }

        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity;
    }
    return;
}