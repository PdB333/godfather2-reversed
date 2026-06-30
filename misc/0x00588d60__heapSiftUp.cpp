// FUNC_NAME: heapSiftUp
// Address: 0x00588d60
// Role: Binary heap sift-up (bubble-up) operation.
// Inserts a value at a given index in a binary heap array, maintaining the heap property.
// The function assumes a min-heap (or max-heap depending on comparator).
// Parameters:
//   value: new element to insert (pass in register EAX as index? Actually EAX is used as newIndex in decompiled; we include it as parameter 'index')
//   array: pointer to heap array (4-byte elements)
//   baseIndex: typically 0 (root index)
//   newValue: value to be inserted
// Note: decompiled shows 'in_EAX' as a register-based parameter, likely the index of the new element.
// The comparator function FUN_00587780 is assumed to be a binary predicate taking two elements and returning true if parent should be moved down (i.e., parent > child for min-heap).

void heapSiftUp(void* array, int baseIndex, int newValue, int index)
{
    int parentIndex;
    int parentValue;
    bool needMove;

    // If index is already at root, store and return
    if (index <= baseIndex) {
        *(int*)((char*)array + index * 4) = newValue;
        return;
    }

    do {
        // parent = (index - 1) / 2
        parentIndex = (index - 1) / 2;
        parentValue = *(int*)((char*)array + parentIndex * 4);

        // Compare parent and new value; if no need to move, store and return
        needMove = FUN_00587780(newValue /*, parentValue? */);
        if (!needMove) {
            *(int*)((char*)array + index * 4) = newValue;
            return;
        }

        // Shift parent down
        *(int*)((char*)array + index * 4) = parentValue;
        index = parentIndex;
    } while (parentIndex > baseIndex);

    // Final store at the root position
    *(int*)((char*)array + index * 4) = newValue;
}