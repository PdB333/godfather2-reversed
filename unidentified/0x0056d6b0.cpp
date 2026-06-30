// FUN_NAME: combineThreeStrings (0x0056d6b0)
// Role: Utility function to concatenate three strings (or data blocks) into a destination buffer.
// Uses an intermediate 28-byte buffer to combine source1+source2, then combines that with source3.
// Underlying helper FUN_0056cba0 likely performs string concatenation.

void combineThreeStrings(char* source1, char* source2, char* source3, char* dest)
{
    char tempBuffer[28]; // temporary space for first concatenation (sized to 28 bytes)

    // Combine the first two sources into the temporary buffer
    FUN_0056cba0(source1, source2, tempBuffer);

    // Now combine the temporary buffer with the third source into the final destination
    FUN_0056cba0(tempBuffer, source3, dest);

    return;
}