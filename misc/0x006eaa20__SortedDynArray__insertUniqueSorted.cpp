// FUNC_NAME: SortedDynArray::insertUniqueSorted
// Address: 0x006eaa20
// Role: Inserts a unique pointer into a sorted dynamic array,
//       maintaining order by a priority value at offset +0x88.
//       Uses helper functions for insertion shift and capacity growth.

void __thiscall SortedDynArray::insertUniqueSorted(void* element) {
    uint index;
    int* arrayPtr;
    int capacity;
    int* currentPtr;
    
    arrayPtr = *reinterpret_cast<int**>(reinterpret_cast<uintptr_t>(this) + 0x30); // +0x30: pointer to array of pointers
    uint size = *reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 0x34); // +0x34: current count
    
    // Linear search for existing element (pointer equality)
    index = 0;
    if (size != 0) {
        currentPtr = arrayPtr;
        do {
            if (*currentPtr == reinterpret_cast<int>(element)) {
                if (index >= 0) {
                    return; // Already present, no insertion
                }
                break;
            }
            index++;
            currentPtr++;
        } while (index < size);
    }
    
    // Find insertion point based on sort key at +0x88 from each element
    index = 0;
    if (size != 0) {
        currentPtr = arrayPtr;
        int elementKey = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(element) + 0x88); // +0x88: sort key / priority
        do {
            if (elementKey < *reinterpret_cast<int*>(*currentPtr + 0x88)) {
                // Insert at this position using helper
                int* insertPos = reinterpret_cast<int*>(_insertAt(index)); // FUN_006ea990: shift right and return insertion slot
                *insertPos = reinterpret_cast<int>(element);
                return;
            }
            index++;
            currentPtr++;
        } while (index < size);
    }
    
    // No insertion point found: append to end
    capacity = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x38); // +0x38: capacity
    if (size == capacity) {
        // Grow capacity (at least 1, otherwise double)
        if (capacity == 0)
            capacity = 1;
        else
            capacity *= 2;
        _reserve(capacity); // FUN_006ea5e0: reallocate array
    }
    
    // Append at end
    int* appendSlot = arrayPtr + size;
    *reinterpret_cast<uint*>(reinterpret_cast<uintptr_t>(this) + 0x34) = size + 1;
    if (appendSlot != nullptr) {
        *appendSlot = reinterpret_cast<int>(element);
    }
    return;
}