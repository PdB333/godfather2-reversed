// FUNC_NAME: ctr_start (LibTomCrypt CTR mode initialization)
// Address: 0x006649b0
// Role: Initialize a symmetric CTR encryption context. Sets up the cipher, stores IV, and encrypts first counter block.
// Note: This is from the LibTomCrypt library used by The Godfather 2.

#include <stdio.h>

// Error codes (from libtomcrypt)
#define CRYPT_OK      0
#define CRYPT_INVALID_KEYSIZE 10

// Maximum number of ciphers
#define CIPHER_MAX 32

// Cipher descriptor size in bytes (11 fields + function pointers, heuristic: 0x2c bytes per entry)
// Structure derived from usage:
//   offset 0: some flag? Actually checked with byte at offset 0 of descriptor *11 (strange)
//   offset 0x98? Actually pattern: &DAT_01205a88 + param1 * 0xb (11 bytes per cipher? but then other arrays use 0x2c stride)
// We'll assume the descriptor is 0x2c bytes and contains fields:
//   - setup, encrypt, etc. The exact layout is not critical, we just need function pointers.

// Global array of cipher descriptors (assumed defined elsewhere)
extern int cipher_descriptors[CIPHER_MAX * 0x2c]; // Actually this is a synthetic layout

// Symmetric CTR state structure (based on byte offsets observed in decompiled code)
// Offsets in bytes:
// +0x00: int cipher
// +0x04: int blocklen
// +0x08: int mode
// +0x0C: unsigned char ctr[?]   (initial counter/IV)
// +0x8C: unsigned char pad[?]   (encrypted counter block)
// +0x10C: symmetric_key key     (cipher key schedule)
#pragma pack(push, 1)
typedef struct {
    int cipher;       // +0x00
    int blocklen;     // +0x04
    int mode;         // +0x08
    unsigned char ctr[128]; // +0x0C, enough for any block size (but actual size is blocklen)
    unsigned char pad[128]; // +0x8C
    unsigned char key[256]; // +0x10C (large enough for AES-256 key schedule)
} symmetric_CTR;
#pragma pack(pop)

// Debug assertion helper (from decompiled: FUN_00b995f7)
// Prints formatted assertion message to stderr (via fprintf)
static void argchk_fail(const char *expr, int line, const char *file) {
    // Assuming this function wraps fprintf with a fixed format.
    // The decompiled shows a call to FUN_00b995f7 which returns a FILE* + 0x40 offset (stderr?)
    // For simplicity, we just call fprintf directly.
    fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", expr, line, file);
}

// Main CTR initialization function
int ctr_start(int cipher, const unsigned char *iv, const unsigned char *key, int keylen, symmetric_CTR *ctr) {
    int result;
    int blocklen;

    // Parameter validation (using assertion-like debug prints)
    if (iv == NULL) {
        argchk_fail("count != NULL", 10, "..\\src\\libtomcrypt\\ctr.c");
    }
    if (key == NULL) {
        argchk_fail("key != NULL", 11, "..\\src\\libtomcrypt\\ctr.c");
    }
    if (ctr == NULL) {
        argchk_fail("ctr != NULL", 12, "..\\src\\libtomcrypt\\ctr.c");
    }

    // Check if cipher is valid (index < 32 and cipher registered)
    if (cipher < 0 || cipher >= CIPHER_MAX) {
        return CRYPT_INVALID_KEYSIZE;
    }
    // Check the cipher descriptor flag (first byte of each 11-byte block? but descriptor stride is 0x2c)
    // Actually we use a different array: &DAT_01205a88 + cipher * 0xb
    // But the decompiled checks if the byte at that location is non-zero.
    // We'll assume a simple flag check based on an array 'cipher_active'.
    // For simplicity, we just check if the descriptor is valid by verifying the setup function pointer.
    // This is a placeholder; in real code it uses a different table.
    if (cipher_descriptors[cipher * 0x2c] == 0) { // Assume first word is "present" flag
        return CRYPT_INVALID_KEYSIZE;
    }

    // Get block size from cipher descriptor (source: &DAT_01205a98 + cipher * 0x2c)
    blocklen = cipher_descriptors[cipher * 0x2c + 0x98 - 0x88]; // Heuristic offset; adjust based on real layout
    // Actually from code: in_EAX[1] = *(uint *)(&DAT_01205a98 + param_1 * 0x2c)
    // We'll just store the block size from the descriptor (we don't have the real array, so we hardcode for common ciphers)
    // For AES, blocklen = 16.
    // For now, we trust that the descriptor provides it.

    // Call cipher's setup function: (*(&cipher_desc[cipher].setup))(key, keylen, 0, ctr->key)
    // The function pointer is at &DAT_01205aa0 + cipher * 0x2c
    typedef int (*cipher_setup_fn)(const unsigned char *key, int keylen, int num_rounds, unsigned char *skey);
    cipher_setup_fn setup = (cipher_setup_fn)(&cipher_descriptors[cipher * 0x2c + 0x10]); // arbitrary offset
    result = setup(key, keylen, 0, ctr->key);

    if (result != CRYPT_OK) {
        return result; // Propagate error
    }

    // Initialize CTR state fields
    ctr->cipher = cipher;
    ctr->blocklen = blocklen;
    ctr->mode = 0; // Encrypt mode (or 0 for default)

    // Copy IV into the ctr field (counter initial value)
    for (int i = 0; i < blocklen; i++) {
        ctr->ctr[i] = iv[i];
    }

    // Now encrypt the initial counter block into pad (precomputes first encrypted block)
    // Call: (*(&cipher_desc[cipher].ecb_encrypt))(ctr->ctr, ctr->pad, ctr->key)
    typedef int (*ecb_encrypt_fn)(const unsigned char *pt, unsigned char *ct, const unsigned char *skey);
    ecb_encrypt_fn encrypt = (ecb_encrypt_fn)(&cipher_descriptors[cipher * 0x2c + 0x14]); // another offset
    encrypt(ctr->ctr, ctr->pad, ctr->key);

    return CRYPT_OK;
}