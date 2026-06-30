// FUNC_NAME: IsEqualGUID (GUID equality comparison, VS2005 CRT implementation)
// Address: 0x0069d430
// Role: Compares two 128-bit GUID structures for equality.
// Implements a byte-by-byte comparison that matches memcmp, but returns bool.

bool __cdecl IsEqualGUID(const GUID& guid1, const GUID& guid2)
{
    // Treat the GUIDs as arrays of 4 DWORDs for bulk comparison.
    const uint32_t* p1 = reinterpret_cast<const uint32_t*>(&guid1);
    const uint32_t* p2 = reinterpret_cast<const uint32_t*>(&guid2);

    // Compare each 4‑byte chunk. If any differs, fall through to byte‑level comparison.
    for (int i = 0; i < 4; i++)
    {
        if (p1[i] != p2[i])
        {
            // Byte‑by‑byte compare from the first differing DWORD boundary.
            // p1 and p2 now point to the start of the mismatched DWORD.
            const uint8_t* pb1 = reinterpret_cast<const uint8_t*>(&p1[i]);
            const uint8_t* pb2 = reinterpret_cast<const uint8_t*>(&p2[i]);

            // Compare each byte in this DWORD (up to 4 bytes).
            for (int j = 0; j < 4; j++)
            {
                if (pb1[j] != pb2[j])
                {
                    // Return false because a difference was found.
                    // The original code also set a "less‑than/greater‑than" flag,
                    // but the bool result only cares about equality.
                    return false;
                }
            }
            // All bytes in this DWORD were equal – should not happen since the DWORDs differed.
            // But for safety, continue the outer loop.
            break;
        }
    }
    return true;
}