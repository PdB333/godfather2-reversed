// FUNC_NAME: conditionalCopy40Bytes
void __fastcall conditionalCopy40Bytes(int count, const unsigned long long* source, unsigned long long* dest)
{
    // Copies 40-byte (5 * 8) blocks from source to dest, repeated 'count' times.
    // If dest is null, the copy is skipped but the destination pointer is still advanced (original behavior).
    // Note: This may be used to replicate EA EARS engine data structures (e.g., matrix rows or packed vectors).
    if (count != 0) {
        do {
            if (dest != nullptr) {
                dest[0] = source[0];
                dest[1] = source[1];
                dest[2] = source[2];
                dest[3] = source[3];
                dest[4] = source[4];
            }
            --count;
            source += 5;
            dest += 5; // Advance pointer even if null (caution: undefined in standard C++)
        } while (count != 0);
    }
}