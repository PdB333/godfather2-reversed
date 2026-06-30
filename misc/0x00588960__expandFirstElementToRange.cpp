// FUNC_NAME: expandFirstElementToRange
// Function address: 0x00588960
// Role: Expands the first 4-byte value of a range (start..end) to all subsequent positions,
//       copying from start to each location from end-4 down to start+4, and invoking a per-element callback.
// Parameters: start in EDI, end in EAX (bytes). The range must be at least 8 bytes (2 words).
// Uses: FUN_00588b80 (unknown per-element action)

void expandFirstElementToRange(void)
{
    int byteOffset;          // iVar1
    int* start;              // unaff_EDI (the beginning of the range)
    int* end;                // in_EAX (one past the last element in bytes)

    // byteOffset = end - start (in bytes), i.e., the size of the range.
    // The loop runs while there are at least 2 words left (byteOffset/4 > 1).
    for (byteOffset = (int)end - (int)start; 1 < byteOffset >> 2; byteOffset -= 4)
    {
        // Copy the first word (at start) to the current last word position (start + byteOffset - 4)
        *(int*)((int)start + byteOffset - 4) = *start;

        // Call the per-element initialization or callback function
        FUN_00588b80();
    }
}