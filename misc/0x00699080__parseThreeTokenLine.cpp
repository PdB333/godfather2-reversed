// FUNC_NAME: parseThreeTokenLine
undefined2** parseThreeTokenLine(undefined2** outTokens, int param2, int param3)
{
    char success;
    int length;
    undefined2* tempBuffer;
    int dummy;
    void (*destructor)(undefined2*);

    // Initialize output token array to null pointers
    *outTokens = (undefined2*)0x0;
    outTokens[2] = (undefined2*)0x0;
    outTokens[1] = (undefined2*)0x0;

    // Get length of param2 string (probably strlen)
    length = FUN_004dbef0(param2);
    // Possibly copy or process param2 (e.g., strcpy into global buffer)
    FUN_004dba00(param2, length);

    // Parse a line/string: split param3 by delimiter (global DAT_01129f9c) into up to 3 tokens stored in outTokens
    // tempBuffer receives a pointer to the allocated token storage, may be used for cleanup
    success = FUN_00698f20(param3, &tempBuffer, &DAT_01129f9c, outTokens, 1);

    // Call destructor on tempBuffer if non-null
    if (tempBuffer != (undefined2*)0x0) {
        (*destructor)(tempBuffer);
    }

    // On failure, log error and cleanup
    if (success == '\0') {
        FUN_004dba80(&DAT_00e2f044, 0);       // Log error (e.g., printf)
        if (outTokens != &tempBuffer) {       // Defensive check if outTokens points to tempBuffer itself
            undefined2* cleanupTarget = tempBuffer;
            if (tempBuffer == (undefined2*)0x0) {
                cleanupTarget = &DAT_00e2df14; // Use global default if null
            }
            FUN_004dbb10(cleanupTarget, 0, dummy); // Deallocate or free
        }
        if (tempBuffer != (undefined2*)0x0) {
            (*destructor)(tempBuffer);         // Double cleanup? Might be safe re-initialization
        }
    }

    return outTokens;
}