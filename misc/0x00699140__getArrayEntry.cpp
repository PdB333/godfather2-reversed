// FUNC_NAME: getArrayEntry
// Function at 0x00699140: Retrieves data from a global array indexed by param_1.
// Returns a handle/status with low byte set to 1 on success, else returns (index & 0xFFFFFF00).
// Writes to *outValue the value at offset 0x10 of the entry, and sets *outPointer to the address of offset 0x0C.

// Global state: array of pointers at g_arrayBase, count defined by (g_arrayEnd - g_arrayBase) / 4
extern int *g_arrayBase;  // DAT_01129f8c
extern int *g_arrayEnd;   // DAT_01129f90

unsigned int getArrayEntry(int index, unsigned int *outValue, int *outPointer)
{
    int entryPtr;
    int arrayCount;

    // Calculate number of entries in the global array
    arrayCount = (g_arrayEnd - g_arrayBase) >> 2;

    // Validate index range: 0 <= index < arrayCount
    if (index >= 0 && index < arrayCount)
    {
        // Get pointer to the entry from the array
        entryPtr = *(int *)(g_arrayBase + index);

        // Store the value at offset 0x10 of the entry
        *outValue = *(unsigned int *)(entryPtr + 0x10);

        // Compute pointer to offset 0x0C of the entry (likely a pointer field)
        entryPtr += 0x0C;
        *outPointer = entryPtr;

        // Return success handle: low byte = 1, high 24 bits = (entryPtr >> 8)
        // This packs the address of the field at +0x0C with a success flag.
        return (entryPtr & 0xFFFFFF00) | 1;
    }

    // Invalid index: return the index with low byte zeroed (error indicator)
    return (index & 0xFFFFFF00);
}