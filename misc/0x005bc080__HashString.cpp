// FUNC_NAME: HashString
// Function address: 0x005bc080
// Computes a hash from a byte array by adding precomputed table values from specific offsets,
// depending on an input seed/length parameter (passed in EAX, byte pointer in ESI).
// Offsets used: 0, 4, 6, 7.
// The global table (0x00e2b338) contains 256 uint16 values.

extern uint16 g_hashTable[256]; // at PTR_DAT_00e2b338

int __fastcall HashString(int seed, const byte* str) {
    int hash = seed;

    // default case (seed == 0 or seed >= 8): use offset 7
    if (seed >= 8 || seed == 0) {
        hash += g_hashTable[str[7]];
    }
    // case 7: use offset 6 (and fall through to subsequent additions)
    if (seed >= 7) {
        hash += g_hashTable[str[6]];
    }
    // cases 5,6: use offset 4
    if (seed >= 5) {
        hash += g_hashTable[str[4]];
    }
    // cases 1,2,3,4: always use offset 0
    if (seed >= 1) {
        hash += g_hashTable[str[0]];
    }

    return hash;
}