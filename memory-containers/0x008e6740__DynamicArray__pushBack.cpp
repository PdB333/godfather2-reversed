// FUNC_NAME: DynamicArray::pushBack

// Function at 0x008e6740: Adds an element to a dynamic array of 4-byte values.
// Class structure:
//   +0x2c: base pointer (array of elements)
//   +0x30: size (number of elements)
//   +0x34: capacity (allocated count)
// Grow function at 0x008e5cf0: reallocates to new capacity.

void __thiscall DynamicArray::pushBack(void* thisPtr, uint newElement)
{
    int* sizePtr = (int*)((int)thisPtr + 0x30);
    int* capacityPtr = (int*)((int)thisPtr + 0x34);
    int currentSize = *sizePtr;
    int currentCapacity = *capacityPtr;

    // If full, grow the array
    if (currentSize == currentCapacity)
    {
        int newCapacity;
        if (currentCapacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = currentCapacity * 2;
        }
        // Call grow function (assumed to reallocate and copy)
        growArray(newCapacity);  // FUN_008e5cf0
    }

    // Write new element at the end
    uint* basePtr = (uint*)(*(int*)((int)thisPtr + 0x2c));
    basePtr[currentSize] = newElement;

    // Increment size
    (*sizePtr)++;
}