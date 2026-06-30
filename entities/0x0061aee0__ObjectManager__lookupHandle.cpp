// FUNC_NAME: ObjectManager::lookupHandle
int* __fastcall ObjectManager::lookupHandle(uint handle)
{
    // handle is passed in EAX (custom fastcall)
    // Global table g_objectTable at 0x011a0f38, each entry is 0x38 bytes
    // Checks if handle is valid (< 0x1000) and the entry exists
    if (handle < 0x1000)
    {
        // Compute offset: handle * 0x38 (size of each entry)
        uint entryOffset = handle * 0x38;
        // Bounds check: ensure offset doesn't produce invalid address (Ghidra's negative constant is likely a decompiler artifact, we skip it)
        // Read first uint of the entry as a validity flag
        uint* entryBase = (uint*)((uint)&g_objectTable + entryOffset);
        uint flag = *entryBase;
        if (flag != 0)
        {
            // Offset +0x1c within the entry holds a pointer to a lookup table
            int* tablePtr = *(int**)(entryBase + 0x1c); // cast to int* actually (entryBase is uint*, so +7? No, entryBase is uint*, so +0x1c bytes = 7 uint offsets? Better to cast to byte*)
            // Actually, entryBase points to uint at start, so we need byte-level offset
            // Let's cast to byte* for accuracy:
            byte* entryBytes = (byte*)entryBase;
            int* ptrToTable = *(int**)(entryBytes + 0x1c);
            if (ptrToTable != nullptr)
            {
                // Call function to find an index in the table (likely hash or linear search)
                int index = findEntryInTable(&stack0x00000004); // parameter is stack variable, could be a key
                if (index >= 0)
                {
                    // ptrToTable is a pointer to some base structure
                    // Each entry in the table is 8 bytes
                    // Address of entry: *ptrToTable (first element) + 4 + index * 8
                    byte* entryAddr = (byte*)(*ptrToTable) + 4 + index * 8;
                    if (entryAddr != nullptr)
                    {
                        // Return pointer to offset +0xc within that entry
                        return (int*)(*ptrToTable + 0xc); // Note: *ptrToTable is the base address, not entryAddr
                    }
                }
            }
        }
    }
    // Fallback: return uninitialized register value (likely a bug or unreachable)
    return (int*)unaff_EDI;
}