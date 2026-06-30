// FUNC_NAME: ecc_verify_hash
// Address: 0x006634b0
// Role: ECDSA signature verification (libtomcrypt ecc_verify_hash)

#include "ltc_ecc.h" // assumed header for libtomcrypt

int ecc_verify_hash(ecc_key *key, int *stat)
{
    int result;
    int err;
    mp_int a, b, c, d; // local_34[16], local_24[16], local_14[20], local_34 reused
    // note: actual sizes are 16/16/20 bytes – mp_int structures

    // ASSERT(param_1 != NULL)
    if (key == NULL) {
        _ARGCHK("pt != NULL", 0x29a, "..\\src\\libtomcrypt\\ecc.c");
        _fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "pt != NULL", 0x29a, "..\\src\\libtomcrypt\\ecc.c");
    }
    // ASSERT(param_2 != NULL)
    if (stat == NULL) {
        _ARGCHK("result != NULL", 0x29b, "..\\src\\libtomcrypt\\ecc.c");
        _fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "result != NULL", 0x29b, "..\\src\\libtomcrypt\\ecc.c");
    }

    // Initialize multiple mp_int objects
    if (mp_init_multi(&a, &b, &c, &d, NULL) != CRYPT_OK) {
        return CRYPT_MEM;
    }

    // Read the curve's base point (or public key) from a magic string using key's curve index
    // The string array likely holds base-64 encoded curve parameters
    if (mp_read_unsigned_bin(&a, curveBaseStringArray[key->idx * 7], 64) != CRYPT_OK) {
        err = CRYPT_MEM;
        goto cleanup;
    }

    // Check that the point is on the curve
    if (ecc_is_point(key, 3) != CRYPT_OK) { // '3' might be the point type flag
        err = CRYPT_INVALID_PACKET;
        goto cleanup;
    }

    // Decrypt or verify – read the signature from key->pubkey or elsewhere
    if (ecc_decrypt(key, 3, &b) != CRYPT_OK) { // '3' might be a hash index
        err = CRYPT_ERROR;
        goto cleanup;
    }

    // Verify the hash
    if (ecc_verify_hash_raw(&a, &b) != CRYPT_OK) {
        err = CRYPT_ERROR;
        goto cleanup;
    }

    // Multiply something (maybe shared secret)
    if (mp_mul(&a, &c) != CRYPT_OK) {
        err = CRYPT_MEM;
        goto cleanup;
    }

    // Read another curve constant (e.g., generator or prime)
    if (mp_read_unsigned_bin(&d, curveZStringArray[key->idx * 7], 64) != CRYPT_OK) {
        err = CRYPT_MEM;
        goto cleanup;
    }

    // Decrypt again or perform ECDSA verification steps
    if (ecc_verify_hash_step2(&c, &d) != CRYPT_OK) {
        err = CRYPT_ERROR;
        goto cleanup;
    }

    // Export something (maybe signature)
    if (ecc_export(&d, 1, &b) != CRYPT_OK) { // '1' might be export type
        err = CRYPT_ERROR;
        goto cleanup;
    }

    // Finalize hash (SHA-256 final?)
    if (sha256_final(&b) != CRYPT_OK) {
        err = CRYPT_ERROR;
        goto cleanup;
    }
    if (sha256_final(&b) != CRYPT_OK) { // second final? possibly a bug or second hash
        err = CRYPT_ERROR;
        goto cleanup;
    }

    // Perform ECDSA verification core
    if (ecc_verify_hash_core(&a, &b, &c, &a) != CRYPT_OK) {
        err = CRYPT_ERROR;
        goto cleanup;
    }

    // Compare result: mp_cmp_d returns 0 if equal, 1 if greater, etc.
    *stat = (mp_cmp_d(&a, 0) != 0); // if a != 0 then valid
    result = CRYPT_OK;
    goto cleanup;

cleanup:
    mp_clear_multi(&d, &c, &b, &a, NULL);
    return result;
}