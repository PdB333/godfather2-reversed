// FUNC_NAME: compare8Bytes (0x006549b0)
// Compares two 8-byte buffers (e.g., GUID / UID) and returns -1, 0, or 1.
// __fastcall: first argument (ECX) is right-hand side, second argument (EDX) is left-hand side.

uint __fastcall compare8Bytes(const byte* lhs, const byte* rhs)
{
    uint remaining = 8;

    // Compare as two 32-bit words first (fast path)
    do {
        if (*(const int*)lhs != *(const int*)rhs) {
            goto compareRemaining;
        }
        lhs += 4;
        rhs += 4;
        remaining -= 4;
    } while (remaining > 3);

    if (remaining == 0) {
        return 0; // all 8 bytes equal
    }

compareRemaining:
    // Byte‑by‑byte comparison of the remaining block (up to 4 bytes)
    int diff = *lhs - *rhs;
    if (diff == 0) {
        if (remaining == 1) return 0;
        diff = lhs[1] - rhs[1];
        if (diff == 0) {
            if (remaining == 2) return 0;
            diff = lhs[2] - rhs[2];
            if (diff == 0) {
                if (remaining == 3) return 0;
                diff = lhs[3] - rhs[3];
                if (diff == 0) return 0;
            }
        }
    }

    // Return positive (1) if lhs > rhs, negative (0xFFFFFF01 = -1) if lhs < rhs
    if (diff > 0) return 1;
    return 0xFFFFFF01;
}