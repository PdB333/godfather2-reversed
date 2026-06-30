// FUNC_NAME: TNLConnection::adjustSequenceWindowWrapper
// address 0x00465810
// Likely a helper for adjusting sequence numbers within a 32-slot window, returning a combined result.
// The global unaff_ESI represents the window size (commonly 32 in TNL).
// The function takes four parameters:
//   ecx - baseSequence (usually a starting index)
//   edx - startSequence
//   stack[0] - offset (possibly an adjustment value)
//   stack[4] - endSequence
// Returns a 32-bit value where the high byte indicates whether endSequence <= startSequence after adjustments,
// and the lower 24 bits come from (offset >> 8).

int __fastcall adjustSequenceWindow(int baseSequence, int startSequence, int offset, int endSequence)
{
    int windowSize; // unaff_ESI, typically 32
    windowSize = g_slotWindowSize;

    // Step 1: Adjust offset relative to window size
    offset = windowSize - offset;

    // Step 2: Forward adjustments
    baseSequence = baseSequence + 1;
    startSequence = startSequence + offset;
    endSequence   = endSequence + offset;

    // Step 3: Check and re-adjust startSequence if baseSequence <= startSequence
    if (baseSequence <= startSequence)
    {
        offset       = windowSize - baseSequence;
        startSequence = startSequence + offset;
    }

    // Step 4: Additional wrap for startSequence if still below window size
    if (startSequence < windowSize)
    {
        startSequence = startSequence + baseSequence;
    }

    // Step 5: Same logic for endSequence
    if (baseSequence <= endSequence)
    {
        offset     = windowSize - baseSequence;
        endSequence = endSequence + offset;
    }

    // Step 6: Additional wrap for endSequence
    if (endSequence < windowSize)
    {
        endSequence = endSequence + baseSequence;
    }

    // Build return value: high byte = (endSequence <= startSequence), low 24 bits = (offset >> 8)
    return CONCAT31((int3)((uint)offset >> 8), endSequence <= startSequence);
}