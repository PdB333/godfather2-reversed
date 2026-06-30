// FUNC_NAME: iterateAndCallFunction

void FUN_00588a80(int* endPtr)
{
    // unaff_EDI is assumed to be set by the caller; it represents the start pointer.
    // The loop count is computed as floor((endPtr - startPtr) / 8) for 8-byte elements.
    int* startPtr = (int*)unaff_EDI;  // unaff_EDI comes from register EDI, set by caller
    int elementCount = ((endPtr - startPtr) >> 2) - ((endPtr - startPtr) >> 0x1f) >> 1;
    // Actually: ((end-start) / 4) - (sign correction) then /2 => (end-start)/8  (floor)

    for (int i = elementCount; i > 0; i--) {
        FUN_00588cb0();  // process each element (likely reads from a global or based on startPtr)
    }
}