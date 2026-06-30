// FUNC_NAME: DynamicArray::pushBack

// Function address: 0x0063de40
// Role: Adds an element (12 bytes) to a dynamic array, reallocating if necessary.
// The array is managed via a handle structure at this+0x1c, which contains:
//   +0x00: pointer to array metadata (struct with data pointer at +0x18, capacity at +0x38)
//   +0x30: current element count (index 12 in int array)
// Element size is 0xC (12 bytes).
// Reallocation uses an allocator at this+0x20.

void __thiscall DynamicArray::pushBack(int thisPtr, int element)
{
    int* handle = *(int**)(thisPtr + 0x1c);          // +0x1c: handle to array state
    int* meta = (int*)*handle;                       // handle[0] -> metadata struct
    int capacity = *(int*)(meta + 0x38);             // +0x38: capacity (max elements)
    int count = handle[0xc];                         // handle[12] = current count

    if (capacity < count + 1) {
        // Reallocate: double capacity or grow by some factor
        int newData = FUN_00627930(
            *(int*)(thisPtr + 0x20),                 // allocator
            *(int*)(meta + 0x18),                    // old data pointer
            (int*)(meta + 0x38),                     // pointer to capacity (updated by realloc)
            0xc,                                     // element size
            &DAT_00e2f044                            // static memory pool info
        );
        *(int*)(meta + 0x18) = newData;              // update data pointer
    }

    // Store element at the next slot
    int* data = *(int**)(meta + 0x18);
    data[count * 3] = element;                       // each element is 3 ints (12 bytes)

    handle[0xc] = count + 1;                         // increment count
}