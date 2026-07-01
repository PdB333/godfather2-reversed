// FUNC_NAME: CopyStringFromLookupTable

// Function at 0x0095f870
// Copies a string from a global lookup table (indexed by param_1) into a destination buffer.
// The table is an array of 0x10-byte entries at DAT_01130870.
// Each entry: +0x00 char* string, +0x04 int length/size.
// If the pointer is null, a default string (DAT_0120546e) is used instead.

void CopyStringFromLookupTable(int index, char* destBuffer)
{
    // Possibly a synchronization or validation call
    FUN_0095ecd0();

    // Compute entry address
    int entryOffset = index * 0x10;
    char** stringPtrPtr = (char**)(DAT_01130870 + entryOffset);
    int* lengthPtr = (int*)(DAT_01130870 + entryOffset + 4);

    // Get source string (fallback to default if null)
    char* sourceStr = *stringPtrPtr;
    if (sourceStr == (char*)0x0) {
        sourceStr = (char*)&DAT_0120546e;  // Default empty/null string
    }

    // Copy string: destBuffer, sourceString, maxSize 0x80, optional length parameter
    FUN_005c4660(destBuffer, sourceStr, 0x80, *lengthPtr);
}