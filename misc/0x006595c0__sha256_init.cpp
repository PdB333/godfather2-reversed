// FUNC_NAME: sha256_init
// Address: 0x006595c0
// Role: Initialize SHA-256 hash context (libtomcrypt sha256.c line 183)

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t length_low;   // +0x00
    uint32_t length_high;  // +0x04
    uint32_t state[8];     // +0x08 through +0x24
    uint32_t curlen;       // +0x28
    // uint8_t buf[64];    // +0x2C (not accessed here)
} sha256_state;

void sha256_init(sha256_state* md) {
    if (md == (sha256_state*)0x0) {
        fprintf(stderr, "_ARGCHK 'md != NULL' failure on line %d of file %s\n",
                0xb7, "..\\src\\libtomcrypt\\sha256.c");
    }

    md->curlen = 0;
    md->length_low = 0;
    md->length_high = 0;

    // SHA-256 initial hash values (first 32 bits of fractional parts of square roots of primes 2..19)
    md->state[0] = 0x6a09e667;
    md->state[1] = 0xbb67ae85;
    md->state[2] = 0x3c6ef372;
    md->state[3] = 0xa54ff53a;
    md->state[4] = 0x510e527f;
    md->state[5] = 0x9b05688c;
    md->state[6] = 0x1f83d9ab;
    md->state[7] = 0x5be0cd19;
}