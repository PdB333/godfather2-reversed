// FUNC_NAME: defragmentSlotArray

void defragmentSlotArray(void)
{
    // Global array of 15 pointers (indices 0-14), initially may contain nulls.
    // When a non-null pointer is found after nulls, it is moved to the front,
    // and the object's field at offset +0x4 is updated to its new index.
    int destIdx = 0;      // target write index in the array
    int nullCount = 0;    // number of consecutive null slots encountered

    // Loop until all 15 slots have been processed (destIdx + nullCount < 15)
    do {
        // Read pointer from combined index (source = destination + null offset)
        int* ptr = s_slotArray[destIdx + nullCount];
        if (ptr == NULL) {
            // Hit a null slot: increase the null count to skip it
            nullCount = nullCount + 1;
        }
        else {
            // Found a non-null slot
            if (nullCount != 0) {
                // The slot has been shifted: update the object's slot index at +4
                *(int*)(ptr + 1) = destIdx;               // +0x04
                // Move the pointer to the compacted position
                s_slotArray[destIdx] = ptr;
                // Clear the original slot to maintain array consistency
                s_slotArray[destIdx + nullCount] = NULL;
            }
            // Advance destination index
            destIdx = destIdx + 1;
        }
    } while (destIdx + nullCount < 15);
}