// FUNC_NAME: yarrow_start

#include <string.h>
#include <stdio.h>

// Yarrow PRNG state structure (from libtomcrypt)
// +0x00: pool index (uint)
// +0x04: cipher index (uint)
// +0x08: 128-byte buffer (0x80 bytes)
struct yarrow_state {
    uint pool_idx;
    uint cipher_idx;
    unsigned char buf[128];
};

// External functions
uint find_hash(const char* name);  // FUN_006603e0
uint find_cipher(const char* name); // FUN_00660590
int _argchk_fail(const char* fmt, const char* arg, int line, const char* file); // FUN_00b995f7

int yarrow_start(yarrow_state* prng)
{
    uint hash_idx;
    uint cipher_idx;

    if (prng == NULL) {
        int argchk_result = _argchk_fail("_ARGCHK '%s' failure on line %d of file %s\n",
                                         "prng != NULL", 0x12, "..\\src\\libtomcrypt\\yarrow.c");
        fprintf((FILE*)(argchk_result + 0x40), "_ARGCHK '%s' failure on line %d of file %s\n");
    }

    hash_idx = find_hash();
    prng->pool_idx = hash_idx;

    if ((hash_idx < 0x20) && (hash_descriptor[hash_idx] != 0)) {
        cipher_idx = find_cipher();
        prng->cipher_idx = cipher_idx;

        if ((cipher_idx < 0x20) && (cipher_descriptor[cipher_idx] != 0)) {
            if (prng->buf == NULL) {
                int argchk_result = _argchk_fail("_ARGCHK '%s' failure on line %d of file %s\n",
                                                 "dst != NULL", 6, "..\\src\\libtomcrypt\\mem.c");
                fprintf((FILE*)(argchk_result + 0x40), "_ARGCHK '%s' failure on line %d of file %s\n");
            }
            memset(prng->buf, 0, 128);
            return CRYPT_OK; // 0
        }
        return CRYPT_INVALID_CIPHER; // 0xb
    }
    return CRYPT_INVALID_HASH; // 10
}