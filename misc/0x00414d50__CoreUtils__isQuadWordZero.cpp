// FUNC_NAME: CoreUtils::isQuadWordZero
// Function at 0x00414d50: Checks if a quad-word (4 consecutive ints) is all zero.
// This is used as a null check for resource handles, object IDs, or similar 16-byte tokens in the EARS engine.
// Returns true if all four ints are zero, false otherwise.
bool __fastcall CoreUtils::isQuadWordZero(int* pQuad)
{
    // Check each 32-bit field for zero
    if ((pQuad[0] == 0) && (pQuad[1] == 0) && (pQuad[2] == 0) && (pQuad[3] == 0))
    {
        return true; // Null or empty token
    }
    return false;
}