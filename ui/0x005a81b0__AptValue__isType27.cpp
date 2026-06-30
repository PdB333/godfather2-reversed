// FUNC_NAME: AptValue::isType27
// Function address: 0x005a81b0
// Role: Checks if an AptValue's type field equals 0x1b (27) and that the high bit (bit 15) is clear.
// Debug assertion on null pointer.

bool __cdecl AptValue::isType27(uint* value)
{
    // Debug assertion for null pointer
    if (value == nullptr)
    {
        const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
        int line = 0x1d7; // 471
        // Standard assertion logic (simplified)
        if (DAT_01128fbc != '\0')
        {
            // Output assertion message and breakpoint
            // Thread-local storage usage
            int* tlsPointer = *(int**)(*(int**)(__readfsdword(0x2c) + 0x30));
            if (tlsPointer != nullptr)
            {
                // Call the assertion handler with the failed expression
                // (assertion expression is not captured in this decompilation)
                (*(code**)(*tlsPointer + 8))(&file, &DAT_00e3b9b8);
            }
            // Trigger debug breakpoint
            __debugbreak();
        }
        return false; // Not reached in debug build? Original continues to null check below
    }

    // Check type: lower 15 bits == 0x1b AND bit 15 == 0
    if ((*value & 0x7fff) == 0x1b && ((*value >> 15) & 1) == 0)
    {
        return true;
    }
    return false;
}