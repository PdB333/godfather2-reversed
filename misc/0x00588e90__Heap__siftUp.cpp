// FUNC_NAME: Heap::siftUp
// Address: 0x588E90
// Purpose: Sift up (bubble up) an element in a binary heap after insertion.
//          This is an internal helper called when adding a new element to a priority queue.
// Parameters:
//   - param_1 (ecx?): Pointer to the heap array (int*).
//   - param_2 (edx?): Index of the last valid element before insertion (heap size - 1).
//   - param_3 (stack?): Value to insert into the heap.
//   - in_EAX (register): Index where the new element is initially placed (should be heap size after insertion).
// Notes: The comparison callback at 0x587840 is used to determine ordering.
//        It is called with the parent value and the value being inserted? (Signature unknown).
//        The callback returns non-zero if the child should move up (i.e., child > parent for max-heap).

void __fastcall heapSiftUp(int* heapArray, int lastIndex, int newValue)
{
    // in_EAX is passed via register; we'll model it as an explicit parameter.
    // For clarity, we add a local to simulate the register.
    int childIndex = _EAX; // This must be set by the caller.

    int parentIndex;
    int parentValue;

    childIndex--; // Align to 0-based? Actually code: iVar1 = in_EAX + -1; so childIndex-1.

    // If childIndex <= lastIndex, we are already in the valid heap; store directly? 
    // Actually the condition is childIndex <= lastIndex? Let's follow decompiled logic.
    // The original: if (in_EAX <= param_2) store directly. That means if the starting index is within the existing heap,
    // there is nothing to sift (already in place). So we store and return.
    if (childIndex+1 <= lastIndex) // Actually careful: in_EAX <= param_2: in_EAX is childIndex+1? 
    // We'll keep the original condition as in comment.
    {
        heapArray[childIndex+1] = newValue;
        return;
    }

    do {
        parentIndex = childIndex / 2; // iVar4 = iVar1/2; iVar1 was childIndex.
        parentValue = heapArray[parentIndex];

        // Comparison callback: returns non-zero if child should move up.
        if (heapComparisonCallback(parentValue, newValue) == 0) {
            // Found proper position: store new value at current child index.
            heapArray[childIndex] = newValue;
            return;
        }

        // Move parent down to child position.
        heapArray[childIndex] = parentValue;
        childIndex = parentIndex;
        // Move up: compute new parent.
        childIndex--; // Equivalent to iVar1 = iVar4 + -1.
    } while (lastIndex < childIndex); // Continue while parent index is beyond the original heap.

    // When loop ends, store the new value at the final position.
    heapArray[childIndex] = newValue;
}

// Placeholder for the actual callback at 0x587840.
// This function likely compares two heap values and returns non-zero if the first is "greater" (for max-heap).
inline int __fastcall heapComparisonCallback(int a, int b) {
    // Decompiled call: FUN_00587840();
    // Actual signature unknown; assume two integer args.
    // For illustration: return (a > b) ? 1 : 0;
    return 0; // Stub
}