// FUNC_NAME: yarrow_read
// libtomcrypt Yarrow PRNG read function (0x006621b0)
// Reads random bytes from the Yarrow PRNG state

#include <stdio.h>
#include <stdint.h>

// Forward declarations for external tables (assumed)
// Each hash descriptor is 0x20 bytes: { init, process, done, hashsize, ... }
extern uint32_t DAT_01206008; // array of flags for registered hashes (8 bytes per entry)
extern void* DAT_01206018;    // start of hash descriptor array (each 0x20 bytes)
extern void* DAT_01206010;    // maybe hash sizes array

// Yarrow PRNG state (simplified)
struct yarrow_prng {
    int cipher_idx;        // +0x04
    unsigned char pool[64]; // +0x08 (example size, actual from code)
};

// Debug assertion function (custom)
int debugAssert(const char* format, const char* expr, int line, const char* file) {
    // In the original: returns a FILE* based on some global
    return (int)(void*)0; // placeholder
}

// Yarrow read function
// buf: output buffer for random bytes
// len: number of bytes to generate
// prng: pointer to yarrow_prng state
// Returns: 0 on success, 0x0B (CRYPT_ERROR) on failure
int yarrow_read(uint8_t* buf, uint32_t len, struct yarrow_prng* prng) {
    uint32_t idx;
    uint8_t hash_state[212]; // SHA-256 state size (typical)

    // Argument validation (original uses _ARGCHK macro)
    if (buf == 0) {
        (void)debugAssert("_ARGCHK '%s' failure on line %d of file %s\n",
                          "buf != NULL", 0x58, "..\\src\\libtomcrypt\\yarrow.c");
        // Original calls _fprintf with the result of debugAssert
        fprintf(stderr, "_ARGCHK 'buf != NULL' failure on line %d of file %s\n",
                0x58, "..\\src\\libtomcrypt\\yarrow.c");
    }
    if (prng == 0) {
        (void)debugAssert("_ARGCHK '%s' failure on line %d of file %s\n",
                          "prng != NULL", 0x59, "..\\src\\libtomcrypt\\yarrow.c");
        fprintf(stderr, "_ARGCHK 'prng != NULL' failure on line %d of file %s\n",
                0x59, "..\\src\\libtomcrypt\\yarrow.c");
    }

    idx = prng->cipher_idx; // +0x04
    if ((idx < 32) && (*(uint8_t*)(&DAT_01206008 + idx * 8) != 0)) {
        // Call hash init function (offset 0 in descriptor)
        ((void (*)(uint8_t*))(&DAT_01206018 + idx * 0x20))(hash_state);

        // Call hash process on the internal pool
        // Third argument: hash digest size from table (offset +0x10?)
        uint32_t digestSize = *(uint32_t*)(&DAT_01206010 + idx * 0x20);
        ((void (*)(uint8_t*, const uint8_t*, uint32_t))(&DAT_0120601c + idx * 0x20))
            (hash_state, &prng->pool, digestSize);

        // Call hash process on the output buffer (produces hash output into buf)
        ((void (*)(uint8_t*, uint8_t*, uint32_t))(&DAT_0120601c + idx * 0x20))
            (hash_state, buf, len);

        // Call hash done function (offset +8 in descriptor) - stores final hash back to pool?
        ((void (*)(uint8_t*, uint8_t*))(&DAT_01206020 + idx * 0x20))
            (hash_state, &prng->pool);

        return 0;
    }
    return 0x0B; // CRYPT_ERROR_INVALID_PRNGS
}