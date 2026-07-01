// FUNC_NAME: EARSVector::pushBack
// Function address: 0x00830770
// This appears to be a dynamic array (vector) push_back implementation.
// The "this" pointer points to a struct with:
//   +0x00: data pointer
//   +0x04: size (number of elements)
//   +0x08: capacity (allocated count)
// The element size is presumed to be 4 bytes (int/pointer).

void __thiscall EARSVector::pushBack(void* thisPtr, int value) // param_1 = this, param_2 = value to copy
{
    int* dataPtr = *(int**)thisPtr;          // +0x00: pointer to allocated array
    int* sizePtr = (int*)((char*)thisPtr + 4); // +0x04: current number of elements
    int* capPtr  = (int*)((char*)thisPtr + 8); // +0x08: current capacity

    int currentSize = *sizePtr;
    int currentCap = *capPtr;

    if (currentSize == currentCap) {
        // Need to grow the array
        int newCapacity;
        if (currentCap == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCap * 2;
        }
        // Reallocation function (FUN_0082b950) – likely realloc or malloc+copy
        grow(newCapacity);
        // Update the pointer to the new data after growth
        dataPtr = *(int**)thisPtr; // re-read after potential realloc
    }

    // Copy the value into the next slot
    dataPtr[*sizePtr] = value;  // store at position = size
    *sizePtr = (*sizePtr) + 1;  // increment size
}