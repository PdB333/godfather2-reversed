// FUNC_NAME: swap128Bit
// Swap two 128-bit (16-byte) blocks pointed to by a and b.
// Used for swapping pairs of 64-bit values, e.g., in sorting or container operations.
void __fastcall swap128Bit(uint64_t* a, uint64_t* b) {
    // Load both 64-bit halves of 'a'
    uint64_t tmp0 = a[0];
    uint64_t tmp1 = a[1];

    // Overwrite 'a' with contents of 'b'
    a[0] = b[0];
    a[1] = b[1];

    // Write original 'a' contents to 'b'
    b[0] = tmp0;
    b[1] = tmp1;
}