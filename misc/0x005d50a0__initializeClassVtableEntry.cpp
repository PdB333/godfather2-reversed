// FUNC_NAME: initializeClassVtableEntry
void initializeClassVtableEntry(void)
{
    // Global registry pointer at DAT_01206880, offset 0x14 holds a pointer to the current write position
    int *currentWritePtr = *(int **)(DAT_01206880 + 0x14); // current write position in preallocated buffer

    // Write the class vtable address into the current slot
    *currentWritePtr = (int)&PTR_LAB_01126b68; // vtable pointer for class (e.g., SomeClass_vtable)

    // Advance write pointer by 4 bytes (size of vtable pointer)
    currentWritePtr++;

    // Align write pointer to next 4-byte boundary (round up to multiple of 4)
    int *alignedPtr = (int *)(((uint32_t)currentWritePtr + 3) & ~3);

    // Write count/reference (1) into the aligned position
    *alignedPtr = 1;

    // Advance past the written count (4 bytes) and store back
    currentWritePtr = alignedPtr + 1;

    // Update the registry's current write pointer
    *(int **)(DAT_01206880 + 0x14) = currentWritePtr;
}