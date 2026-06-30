// FUNC_NAME: initRandomTable
// Initializes the random number generator state and pre-computes a table of 20 LCG values (Lehmer/Park-Miller generator with multiplier 16807).
// Global state at 0x01194788, count at 0x0119478c, table at 0x01194790.
void initRandomTable()
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t *puVar3;

    // Seed value
    uVar2 = 0xdecafbad;
    s_randomState = 0xdecafbad;          // +0x01194788
    s_randomTableCount = 20;             // +0x0119478c (0x14)
    puVar3 = s_randomTable;               // +0x01194790
    do {
        // Classic Lehmer generator: state = (state * 16807) mod 2^31
        // Implemented with splitting to avoid overflow
        uVar1 = (s_randomState >> 16) * 0x41a7;
        uVar2 = (uVar2 & 0xffff) * 0x41a7 + (uVar1 & 0x7fff) * 0x10000 + (uVar1 >> 0xf);
        if ((int)uVar2 < 0) {
            uVar2 += 0x80000001; // simulate modulo 2^31 in signed arithmetic
        }
        s_randomState = uVar2;
        *puVar3 = uVar2;
        puVar3++;
    } while ((int)puVar3 < (int)(s_randomTable + 20));
}