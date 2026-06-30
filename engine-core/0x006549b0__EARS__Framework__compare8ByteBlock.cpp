// FUNC_NAME: EARS::Framework::compare8ByteBlock
// Address: 0x006549b0
// Role: Compares two 8-byte blocks (likely hash keys or identifiers) for ordering.
// Returns: -255 (0xffffff01) if a < b, 0 if equal, 1 if a > b.
// Uses __fastcall: first param (a) in ECX, second param (b) in EDX.

uint __fastcall compare8ByteBlock(byte* a, byte* b)
{
    uint remaining; // Number of bytes left to compare (starting at 8)
    int diff;       // Difference between current bytes

    remaining = 8;
    // Compare 4-byte chunks first for speed
    do {
        if (*(int*)a != *(int*)b)
            goto byteCompare; // Mismatch found, fall back to byte-by-byte
        remaining -= 4;
        a += 4;
        b += 4;
    } while (remaining > 3);

    // All 8 bytes matched
    if (remaining == 0) {
        return 0;
    }

byteCompare:
    // Remaining bytes (up to 4) are compared byte-by-byte
    diff = (int)*a - (int)*b;
    if (diff == 0) {
        if (remaining == 1)
            return 0;
        diff = (int)a[1] - (int)b[1];
        if (diff == 0) {
            if (remaining == 2)
                return 0;
            diff = (int)a[2] - (int)b[2];
            if (diff == 0) {
                if (remaining == 3)
                    return 0;
                diff = (int)a[3] - (int)b[3];
                if (diff == 0)
                    return 0;
            }
        }
    }

    // Return sign: 1 if a > b, -255 if a < b
    if (diff < 1)
        return 0xffffff01; // -255
    return 1;
}