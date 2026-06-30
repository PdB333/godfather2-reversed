// FUNC_NAME: sortThree8ByteRecordsByKey
// Function address: 0x0069c650
// Sorts three 8-byte records in-place by the first byte (key) using a sorting network.
void sortThree8ByteRecordsByKey(uint8_t* recordA, uint8_t* recordB, uint8_t* recordC)
{
    // Each record is 8 bytes: key byte at [0], then 3 bytes padding, then a 32-bit value at [4].
    // The key byte determines ordering; the entire 8-byte block is swapped as two 32-bit halves.

    // Compare first two
    if (*recordB < *recordA) {
        uint32_t temp0 = *(uint32_t*)recordB;
        uint32_t temp1 = *(uint32_t*)(recordB + 4);
        *(uint32_t*)recordB = *(uint32_t*)recordA;
        *(uint32_t*)(recordB + 4) = *(uint32_t*)(recordA + 4);
        *(uint32_t*)recordA = temp0;
        *(uint32_t*)(recordA + 4) = temp1;
    }

    // Compare second and third
    if (*recordC < *recordB) {
        uint32_t temp0 = *(uint32_t*)recordC;
        uint32_t temp1 = *(uint32_t*)(recordC + 4);
        *(uint32_t*)recordC = *(uint32_t*)recordB;
        *(uint32_t*)(recordC + 4) = *(uint32_t*)(recordB + 4);
        *(uint32_t*)recordB = temp0;
        *(uint32_t*)(recordB + 4) = temp1;
    }

    // Re-compare first two (ensures final order)
    if (*recordB < *recordA) {
        uint32_t temp0 = *(uint32_t*)recordB;
        uint32_t temp1 = *(uint32_t*)(recordB + 4);
        *(uint32_t*)recordB = *(uint32_t*)recordA;
        *(uint32_t*)(recordB + 4) = *(uint32_t*)(recordA + 4);
        *(uint32_t*)recordA = temp0;
        *(uint32_t*)(recordA + 4) = temp1;
    }

    return;
}