// FUNC_NAME: EARS::Array::eraseCurrentElement
undefined4 EARS::Array::eraseCurrentElement(int this)
{
    int *currentElementPtr = *(int **)(this + 0xc);  // +0xC: current iterator pointer
    int *bufferEndPtr = *(int **)(this + 0x8);       // +0x8: pointer to end of buffer (next free slot)
    void *controlBlock = *(void **)(this + 0x10);     // +0x10: pointer to control block (size, capacity)

    // Check if iterator is valid and not at end, and element type > 0
    if ((currentElementPtr < bufferEndPtr) && (currentElementPtr != nullptr) && (*currentElementPtr > 0)) {
        // Determine the element size
        int elementSize;
        if (*currentElementPtr == 4) {
            // Special case: element size is fixed 4 + 0x10? Actually piVar1[1] is a pointer to data? This seems like an offset
            elementSize = currentElementPtr[1] + 0x10;  // +0x10 from the data pointer
        } else {
            // Otherwise, query a function to get size (likely type-dependent)
            elementSize = FUN_00633990(this);
            if (elementSize == 0) {
                elementSize = 0;
            } else {
                elementSize = currentElementPtr[1] + 0x10;
            }
            // Check buffer watermark condition (maybe capacity check)
            if (*(unsigned int *)(*(int *)(this + 0x10) + 0x20) <= *(unsigned int *)(*(int *)(this + 0x10) + 0x24)) {
                FUN_00627360();  // error/assertion handler
            }
        }
        if (elementSize != 0) goto LAB_0062e64c;
    } else {
        // Iterator out of bounds: call debug error
        FUN_00627ac0(PTR_s_string_00e2a8ac);  // maybe "Iterator invalid" error
        elementSize = 0;
    }

    // Attempt to remove the element
LAB_0062e64c:
    int result = FUN_006290c0(elementSize);  // likely calls remove/free
    if (result == 0) {
        return 1;  // success? (no removal needed?)
    }

    // Perform removal: overwrite the current element slot and shift subsequent elements
    // bufferEndPtr points to the end of the array
    **(int **)(this + 0x8) = 0;   // clear the last element? Actually writes 0 at the location pointed by bufferEndPtr
    *(int *)(this + 0x8) = *(int *)(this + 0x8) + 8;  // then increment end pointer by 8 (two ints)

    int *dest = *(int **)(this + 0x8);  // new end after increment
    int *src = dest;                    // src starts at new end
    // Shift elements back by 2 ints (8 bytes) to overwrite the removed element
    // Loop condition: for(src from new end; src-4 < src; src -= 2) ? actually it's tricky
    for (int *tmp = src; src + (-4) < tmp; tmp = tmp + (-2)) {
        *tmp = tmp[-2];
        tmp[1] = tmp[-1];
    }
    // Then copy the two ints from the original end (before increment) to the position of src?
    int *originalEnd = *(int **)(this + 0x8);  // after loop? This is confusing
    // Actually the loop shifts elements from the current iterator position upward?
    // Let's reinterpret: After removing an element, we need to shift all later elements left.
    // The implementation seems to shift from the end backwards.
    // The code uses puVar2 = *(int **)(this+8); then puVar3 = puVar2; loop...
    // Let's rewrite more cleanly based on assembly logic:
    // After incrementing end pointer, we have a gap at the position of the removed element.
    // The loop shifts elements from the old end (now newEnd-8?) to fill the gap.
    // This is messy; we'll preserve the logic as decompiled.

    // Assigning back to original positions:
    int *originalEnd = *(int **)(this + 0x8);
    dest[-4] = *originalEnd;
    dest[-3] = originalEnd[1];

    return 2;  // indicates element was removed
}