// FUNC_NAME: debugHash4Ints
// Function address: 0x006b6cc0
// Role: Computes a hash from four 32-bit integers using a base-33 polynomial (similar to djb2) and logs the result via debug output.
// The input is interpreted as an array of four uint values; the computation uses 64-bit arithmetic to avoid overflow.
// Likely part of a debug string-hash helper.

void __fastcall debugHash4Ints(uint* ints)
{
    // Base-33 polynomial hash of four consecutive integers
    ulonglong hash = (ulonglong)ints[0] * 0x21 + ints[1];
    hash = hash * 0x21 + ints[2];
    hash = hash * 0x21 + ints[3];

    // Debug log call: level 2, truncated hash value, unknown flags (both 1)
    FUN_00814550(2, (uint)(hash & 0xFFFFFFFF), 1, 1);
}