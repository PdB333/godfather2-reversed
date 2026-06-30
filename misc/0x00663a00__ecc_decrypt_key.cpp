// FUNC_NAME: ecc_decrypt_key
// Function at 0x00663a00: ECC decryption routine from libtomcrypt (src/libtomcrypt/ecc.c)
// Decompiled reconstruction with meaningful names and comments.
// This function decrypts a ciphertext encrypted with ECC (ECIES style).
// Parameters:
//   key   - pointer to ecc_key structure (contains private key)
//   inlen - length of input ciphertext (including overhead)
//   out   - output buffer; on success, out[0..1] contain key type and curve index,
//           and subsequent bytes the decrypted plaintext.
// Returns: CRYPT_OK (0) on success, or an error code.

#include <stdio.h> // for fprintf

// Error codes (typical libtomcrypt)
#define CRYPT_OK               0
#define CRYPT_ERROR            1
#define CRYPT_INVALID_KEYSIZE  7  // size too small
#define CRYPT_MEM              3
#define CRYPT_INVALID_ARG      13 // 0x0D

// Forward declarations of called functions (from libtomcrypt)
int ecc_rng_get_random_bytes(int);
int ecc_import(const unsigned char *in, unsigned long inlen, ecc_key *key);
int ecc_shared_secret(ecc_key *private_key, ecc_key *public_key, unsigned char *out, unsigned long *outlen);
int hash_memory(int hash_idx, const unsigned char *in, unsigned long inlen, unsigned char *out, unsigned long *outlen);
int cipher_decrypt(int cipher_idx, const unsigned char *ct, unsigned long ctlen, unsigned char *pt, unsigned long *ptlen);
int ecc_encrypt_key(const unsigned char *pt, unsigned long ptlen, unsigned char *ct, unsigned long *ctlen, ecc_key *key);
int ecc_decrypt_key_sym(const unsigned char *ct, unsigned long ctlen, unsigned char *pt, unsigned long *ptlen, ecc_key *key);

// Placeholder names for the actual functions called:
// FUN_0066c9f0 -> likely crc_check or rng_init
// FUN_00667820 -> ecc_import_point?
// FUN_0066a010 -> hash_memory
// FUN_0066a620 -> cipher_decrypt
// FUN_00663680 -> ecc_shared_secret ?
// FUN_00665b40 -> cleanup for success?
// FUN_00665b80 -> cleanup for error?
// We'll assign them plausible names based on context.

static int rng_init(int n) {
    // Implementation of FUN_0066c9f0: returns 0 on success
    return 0;
}

static int ecc_import_point(unsigned char *outX, unsigned char *outY, unsigned char *outZ, int compress) {
    // FUN_00667820: imports an ECC point from raw bytes. Returns 0 on success.
    return 0;
}

static int hash_something(unsigned char *data) {
    // FUN_0066a010: likely hash a buffer. Returns 0 on success.
    return 0;
}

static int cipher_decrypt_something(void) {
    // FUN_0066a620: decrypt a buffer. Returns 0 on success.
    return 0;
}

static int ecc_shared_secret_from_point(unsigned char *point, int curve_id) {
    // FUN_00663680: compute shared secret from a point and private key. Returns 0 on success.
    return 0;
}

static void ecc_cleanup_success(unsigned char *point) {
    // FUN_00665b40: cleanup on success
}

static void ecc_cleanup_error(unsigned char *pointX, unsigned char *pointY, unsigned char *pointZ, int compress) {
    // FUN_00665b80: cleanup on error
}

// External symbol for fprintf (from stdio)
extern int fprintf(FILE *stream, const char *format, ...);

// The actual decryption function
int ecc_decrypt_key(const ecc_key *key, unsigned long inlen, unsigned char *out)
{
    unsigned char *point;
    int err;
    unsigned long shared_secret_len;
    unsigned char curve_idx;
    unsigned long key_type;
    unsigned char *share;
    int curve_found;
    unsigned char *ciphertext;
    unsigned long ciphertext_len;

    // Argument validation
    if (key == NULL) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "in != NULL", 0x347, "..\\src\\libtomcrypt\\ecc.c");
    }
    if (out == NULL) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "key != NULL", 0x348, "..\\src\\libtomcrypt\\ecc.c");
    }

    // Input must be at least 6 bytes (header)
    if (inlen < 6) {
        return CRYPT_INVALID_KEYSIZE; // 7
    }

    // Initialize RNG (or maybe CRC)
    err = rng_init(0);
    if (err != CRYPT_OK) {
        return err;
    }

    // Parse the point from the ciphertext
    point = out + 2; // +0x8? Actually out[2..] is used for point storage? In decompile: puVar1 = param_3 + 2
    share = out + 6; // param_3 + 6
    ciphertext = out + 10; // param_3 + 0xA

    err = ecc_import_point(point, share, ciphertext, 0); // Compress flag = 0
    if (err != CRYPT_OK) {
        return CRYPT_INVALID_ARG; // 13
    }

    // Retrieve key type (byte at key+0x04)
    key_type = (unsigned long)(key->type); // e.g., PK_PUBLIC or PK_PRIVATE
    out[0] = (unsigned char)key_type; // store in output

    // Determine curve index from key's curve field (byte at key+0x05)
    // Look up in the curve size table at DAT_00e279c0 (array of 7-integer entries)
    // The table contains minimum sizes for curves; find the smallest one >= key->curve_size
    // Actually key->curve_size is at offset +0x05? The decompile reads byte at param_1+5
    unsigned char key_curve_size = *((unsigned char*)key + 5); // +0x05: size of curve coordinate in bytes?
    unsigned int idx = 0;
    unsigned int table_entry_size;
    if (key_curve_size > 0x14) { // 20
        table_entry_size = 0x14;
        do {
            if (table_entry_size == 0) break;
            idx++;
            table_entry_size = ecc_curve_table[idx * 7]; // first element of each table entry
        } while (table_entry_size < key_curve_size);
    }

    // Check if found a curve
    if (ecc_curve_table[idx * 7] == 0) {
        err = CRYPT_MEM; // 3
        goto cleanup;
    }

    // Store curve index in output
    out[1] = (unsigned char)idx;

    // Now handle decryption based on key type (PK_PRIVATE or PK_PUBLIC)
    if (key_type == 1 || key_type == 0) { // PK_PRIVATE? Actually 0 or 1 means private or public? Usually 1 = private
        // Find maximum curve index from table
        int max_curve_idx = 0;
        while (ecc_curve_table[max_curve_idx * 7] != 0) {
            max_curve_idx++;
        }

        if ((int)idx >= 0 && (int)idx < max_curve_idx && inlen > 9) {
            unsigned long key_data_len = *((unsigned long*)((char*)key + 6)); // +0x06: length of key data
            if (key_data_len + 10 <= inlen) {
                // hash the point (or shared secret?)
                err = hash_something((unsigned char*)key + 10); // +0x0A: point data?
                if (err == CRYPT_OK) {
                    err = cipher_decrypt_something();
                }
                if (err == CRYPT_OK) {
                    // Compute shared secret from the point using private key
                    err = ecc_shared_secret_from_point(point, idx);
                }
                if (err != CRYPT_OK) {
                    goto cleanup;
                }
                // If key type is private (1), we then decrypt symmetric payload
                if (key_type != 0) {
                    // Decrypt the encrypted symmetric key? Actually continue
                    // The code goes to LAB_00663bf1:
                    if (key_type == 1) {
                        // Cleanup for success
                        ecc_cleanup_success(point);
                    }
                    return CRYPT_OK;
                }
                // For key_type == 0 (public key?), need to decrypt the rest
                // Actual decryption of ciphertext
                unsigned long start_offset = key_data_len + 15; // +0x0F
                if (inlen >= start_offset && inlen >= start_offset + *((unsigned long*)((char*)key + 0x0B))) {
                    // +0x0B: length of something? Actually the decompile uses param_1+0xB (iVar2+0xB+param_1)
                    // iVar2 = *(int*)(param_1 + 6) = key_data_len
                    // param_2 < *(int*)(param_1 + 0xB) + start_offset
                    // So there is a length field at key + 0x0B (offset of symmetric ciphertext length)
                    unsigned long sym_len = *((unsigned long*)((char*)key + 0x0B));
                    if (inlen >= start_offset + sym_len) {
                        err = hash_something((unsigned char*)key + start_offset);
                        if (err == CRYPT_OK) {
                            err = cipher_decrypt_something();
                        }
                        if (err == CRYPT_OK) {
                            // Then the same as above: decrypt symmetric part
                            if (key_type == 1) {
                                ecc_cleanup_success(point);
                            }
                            return CRYPT_OK;
                        }
                    }
                }
            }
        }
    }

    // If we reach here, error
    err = CRYPT_INVALID_KEYSIZE; // 7
cleanup:
    ecc_cleanup_error(point, share, ciphertext, 0);
    return err;
}

// Note: The above is a reconstruction based on decompiled assembly. Actual libtomcrypt implementations may differ.
// The table DAT_00e279c0 is not defined here; it would be an external array.
extern unsigned long ecc_curve_table[]; // each entry is 7 words (28 bytes)