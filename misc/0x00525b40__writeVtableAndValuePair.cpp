// FUNC_NAME: writeVtableAndValuePair
// Address: 0x00525b40
// Role: Writes a vtable pointer and a subsequent value (from XMM0) into a sequential table.
// The table pointer is stored at a global offset (DAT_01206880 + 0x14) and advances after each write.

void writeVtableAndValuePair(void)
{
    // Pointer to the current position in the table (stored as int* at global +0x14)
    int* tablePositionPtr = (int*)(DAT_01206880 + 0x14);
    // Dereference to get the current entry address
    int* entryPtr = (int*)*tablePositionPtr;

    // Write the vtable pointer (global constant) at the current entry
    *(undefined4**)entryPtr = (undefined4*)&PTR_LAB_011251a8; // +0x0: vtable pointer
    // Advance the table pointer by one slot (4 bytes)
    *tablePositionPtr = (int)(entryPtr + 1);

    // Now write the value from XMM0 (likely a float or int) into the next slot
    undefined4* nextEntry = (undefined4*)*tablePositionPtr;
    *nextEntry = in_XMM0_Da; // +0x4: value from XMM0
    // Advance again
    *tablePositionPtr = (int)(nextEntry + 1);
}