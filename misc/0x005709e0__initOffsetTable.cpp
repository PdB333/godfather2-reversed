// FUNC_NAME: initOffsetTable
// Address: 0x005709e0
// Description: Relocates a table of offsets by adding the object base address to each entry,
// then clears the first entry (likely a sentinel or count). Used during object initialization.

int __thiscall initOffsetTable(int *this_ptr) {
    int *currentOffset;   // piVar3
    int *targetPointer;   // piVar1
    char *tableBase;      // puVar2

    // Iterate over offsets starting at base + *this_ptr (first offset into table)
    for (currentOffset = (int *)(*this_ptr + (int)this_ptr); *currentOffset != 0; currentOffset++) {
        // For each offset, get the memory location it points to relative to this,
        // then add the base address to that pointer (relocation).
        targetPointer = (int *)(*currentOffset + (int)this_ptr);
        *targetPointer = *targetPointer + (int)this_ptr;
    }

    // Clear the first 4 bytes of the table (likely a count or flag)
    tableBase = (char *)(*this_ptr + (int)this_ptr);
    tableBase[0] = 0;
    tableBase[1] = 0;
    tableBase[2] = 0;
    tableBase[3] = 0;

    return 1;
}