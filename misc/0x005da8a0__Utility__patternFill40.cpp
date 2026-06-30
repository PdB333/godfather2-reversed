// FUNC_NAME: Utility::patternFill40
void __fastcall Utility::patternFill40(const uint64_t* pattern, const uint64_t* destEnd, uint64_t* dest)
{
    // Copies the 40-byte pattern (5 * uint64_t) from 'pattern' to 'dest',
    // advancing 'dest' by 40 bytes each iteration until it reaches 'destEnd'.
    if (dest != destEnd) {
        do {
            dest[0] = pattern[0];
            dest[1] = pattern[1];
            dest[2] = pattern[2];
            dest[3] = pattern[3];
            dest[4] = pattern[4];
            dest += 5; // Advance by 40 bytes (5 * 8)
        } while (dest != destEnd);
    }
}