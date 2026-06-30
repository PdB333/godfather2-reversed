// FUNC_NAME: ecc_verify_hash
#include <tomcrypt.h> // libtomcrypt headers (assumed)

/**
 * 0x00663c10 - ECC verify hash (signature) function
 *
 * Verifies an ECDSA signature against a given hash/digest.
 * Part of libtomcrypt's ECC module.
 *
 * @param key     Pointer to ECC key structure (ecc_key)
 * @param sig     Pointer to signature structure (typically two mp_int for r,s)
 * @param out     Output buffer for the recovered hash? (unused in this path)
 * @param outlen  [in/out] Length of output buffer; on success set to required size
 * @return CRYPT_OK (0) on success, or an error code
 *
 * Known ECC error codes (libtomcrypt):
 *   CRYPT_OK            =  0
 *   CRYPT_INVALID_ARG   = 14 (0x0E)
 *   CRYPT_MEM           = 13 (0x0D)
 *   CRYPT_BUFFER_OVERFLOW = 6
 *   CRYPT_INVALID_PACKET = 15 (0x0F)
 */
int ecc_verify_hash(ecc_key *key, const unsigned char *sig, unsigned char *out, unsigned long *outlen)
{
    int err;
    int hashSize;
    int sigSize;
    int decodedSize;
    unsigned char *tmpBuf; // local_14, size 20

    // Parameter validation via ASSERT
    if (key == NULL) {
        char *msg = "private_key != NULL";
        int line = 0x391;
        const char *file = "..\\src\\libtomcrypt\\ecc.c";
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", msg, line, file);
    }
    if (sig == NULL) {
        char *msg = "public_key != NULL";
        // similar assertion
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", msg, 0x392, file);
    }
    if (out == NULL) {
        char *msg = "out != NULL";
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", msg, 0x393, file);
    }
    if (outlen == NULL) {
        char *msg = "outlen != NULL";
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", msg, 0x394, file);
    }

    // Check key type: must be private (0) or public (1)? Here expects 0
    if (key->type != 0) {
        return CRYPT_INVALID_PACKET; // 0x0F
    }

    // Check that curve indices match (key->idx == sig->idx)
    if (key->idx != *(int *)(sig + 4)) { // sig has an idx field at offset 4
        return CRYPT_INVALID_ARG; // 0x0E
    }

    // Initialize multiprecision integers (mp_init_multi)
    hashSize = mp_init_multi();
    if (hashSize == 0) {
        return CRYPT_MEM; // 13
    }

    // Check bit count of something (maybe mp_count_bits)
    sigSize = mp_count_bits();
    if (sigSize != 0) {
        mp_clear_multi();
        return CRYPT_MEM;
    }

    // Retrieve curve name/parameters using key->idx as index
    // ltc_ecc_curve_name array at 0x00e279c8 (7 entries per curve?)
    err = ltc_ecc_find_curve(ltc_ecc_curve_name[key->idx * 7], 0x40);
    if (err == 0) {
        // Decode signature: assume sig+8 points to r and s (mp_int structures)
        err = ltc_ecc_decode_sig(key->k, sig + 8, hashSize, tmpBuf); // param_1+10 = key->k, param_2+8 = sig->r
        if (err != 0) goto cleanup;

        sigSize = mp_unsigned_bin_size();
        decodedSize = mp_unsigned_bin_size();
        if (*outlen < (unsigned long)(decodedSize + sigSize)) {
            err = CRYPT_BUFFER_OVERFLOW; // 6
            goto cleanup;
        }
        *outlen = decodedSize + sigSize;

        // Export mp_int values to buffer
        err = mp_to_unsigned_bin(hashSize);
        if ((err == 0) && (hashSize = mp_to_unsigned_bin(hashSize + 16), hashSize == 0)) {
            err = CRYPT_OK; // 0
            goto cleanup;
        }
    }
    err = CRYPT_MEM; // 13

cleanup:
    mp_clear_multi(); // clear temporary mp_ints
    mp_clear_multi(); // clear another set
    return err;
}