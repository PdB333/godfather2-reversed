// FUNC_NAME: initializeSystemWithFlag
// Address: 0x0068bcd0
// Description: Sets up a vtable pointer at a global structure offset 0x14, optionally initializes a GUID/ID, and calls two cleanup/init functions.
void initializeSystemWithFlag(char flag)
{
    int* pVtablePointer;
    GUID someGuid;  // Reconstructed as GUID (data size: 4+4+1=9 bytes? Actually 16 bytes, but decompiler shows 4+4+1 local variables; adjust accordingly)
    // The decompiler shows three variables: local_c (4 bytes), local_8 (4 bytes), local_4 (1 byte).
    // This could be a partial GUID or a custom struct. We'll treat as a GUID or ID struct.

    // Get pointer to the vtable pointer slot in the global structure (offset 0x14)
    pVtablePointer = (int*)(DAT_01206880 + 0x14);

    // Store the address of the static vtable label at that slot
    *(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_00e50204;

    // Increment the vtable pointer by 4 (skip first entry? adjust for derived class?)
    *pVtablePointer = *pVtablePointer + 4;

    if (flag != '\0') {
        // Load a global GUID/ID value (DAT_0120eca8 is a 4-byte constant, likely the first part)
        someGuid.data1 = DAT_0120eca8;
        someGuid.data2 = 0;
        someGuid.data3 = 0;  // The local_4 is 1 byte, but we fill as 0. Possibly a struct with separate fields.
        // Call a function to initialize something with this GUID/ID (e.g., register a COM object or create an interface)
        FUN_00408a00(&someGuid, 0);
    }

    // Call cleanup/init functions (likely deinit or finalize)
    FUN_0040cd00(0);
    FUN_00485d50();
}