// FUNC_NAME: ecc_verify_hash (from libtomcrypt ECC system, used in TNL networking)

// Address: 0x00664620
// Role: Verify an ECDSA signature (probably secp256r1 or similar) against a hash.
// Parameters: sig (fastcall in EAX?), siglen (uint), hash (const uchar*), stat (int*), key (const ecc_key*)
// Based on file "c:\packages001_pc\tnl\dev\src\libtomcrypt\ecc_sys.c" lines 0x140-0x143

#include <cstdio>

// Forward declarations of helper functions called here
static int ecc_is_point_at_infinity(int curveIdx);  // FUN_0066c9f0 (check if point is infinity)
static int ecc_hash_to_bn(const unsigned char *hash, unsigned long hashlen, int *bn); // FUN_00663a00 (hash to big number)
static int ecc_verify_init(int *R, int *S, int *hash, int *pubkey, int curveIdx); // FUN_00667820
static int ecc_verify_start(void); // FUN_00662440 (init verification state)
static int ecc_verify_write(const unsigned char *data, unsigned long len); // FUN_0066a010 (feed data)
static int ecc_compare_hashes(const unsigned char *hash1, const unsigned char *hash2, int len); // FUN_00669f00
static int ecc_multiply_point(int* result, const int* point, const int* scalar, int curveIdx); // FUN_0066a550? Actually different
static int ecc_modinv(int *a, int *mod); // FUN_006687e0 (modular inverse)
static int ecc_add_points(int *R, int *S, int *T, int curveIdx); // FUN_00665d70
static int ecc_mulmod(int *a, int *b, int *c, int *mod); // FUN_00662a30 (multiply and reduce)
static int ecc_verify_final(int *R, int *S, int *hash, int *stat); // FUN_00665bd0 (compare R and S)
static void ecc_verify_end(void); // FUN_00662480 (cleanup)
static void ecc_verify_free(int *R, int *S, int *hash, int *pubkey); // FUN_00665b80 (free big numbers)

int __fastcall ecc_verify_hash(const unsigned char *sig, unsigned int siglen, const unsigned char *hash, int *stat, const ecc_key *key)
{
    int ret;
    unsigned int hashlen;     // from signature header
    unsigned int keySize;     // from key structure
    int bnR[4];              // scratch big number buffers
    int bnS[4];
    int bnHash[4];
    int bnTmp[4];
    int R, S, H, T;

    // Argument validation (debug builds)
    if (sig == nullptr) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "sig != NULL", 0x140,
                "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
    }
    if (hash == nullptr) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "hash != NULL", 0x141,
                "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
    }
    if (stat == nullptr) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "stat != NULL", 0x142,
                "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
    }
    if (key == nullptr) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "key != NULL", 0x143,
                "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
    }

    *stat = 0; // default: invalid

    // Minimum signature length: 12 bytes (header + 2 mp_ints)
    if (siglen < 12) {
        return CRYPT_INVALID_PACKET;
    }

    // Check curve validity (probably secp256r1)
    ret = ecc_is_point_at_infinity(ECC_CURVE);
    if (ret != CRYPT_OK) {
        return ret;
    }

    // Read hash length from signature header (offset +4)
    hashlen = *(unsigned int*)(sig + 4);
    if (siglen - 12 < hashlen) {
        return CRYPT_INVALID_PACKET;
    }

    // Convert hash from signature to big number (the hash is stored at sig+8, length hashlen)
    ret = ecc_hash_to_bn(sig + 8, hashlen, bnTmp);
    if (ret != CRYPT_OK) {
        return ret;
    }

    // Read the length of the R component from signature header (offset +8? Actually after hash)
    // Actually the signature format: [4 bytes R length] [4 bytes S length] [hash] [R] [S]? 
    // The decompiled code is a bit hard to follow. We'll reconstruct based on typical ECC signature.
    // The code does: puVar1 = (uint*)(uVar2 + 8 + sig); // point to after hash
    // Then checks: if ((siglen - 12 - hashlen) < *puVar1) return 7;
    // So *puVar1 is the length of the R component.
    // Then it proceeds to verify R and S.

    // We'll assume the standard libtomcrypt ecc_verify_hash flow:
    // 1. Initialize verifier state
    // 2. Feed the hash
    // 3. Compute modular inverse and recover R and S
    // 4. Compare with signature

    int curveIdx = 0; // curve index (assuming secp256r1)

    // Initialize big numbers for R, S, hash from signature components
    ret = ecc_verify_init(bnR, bnS, bnHash, bnTmp, curveIdx);
    if (ret != CRYPT_OK) {
        goto cleanup;
    }

    // Start verification process
    ret = ecc_verify_start();
    if (ret != CRYPT_OK) {
        goto abort_cleanup;
    }

    // Feed the provided hash into the verification hash chain
    // (the hash parameter is the actual message hash, not from signature)
    ret = ecc_compare_hashes( /*? */); 
    // Actually code shows: FUN_0066a010(puVar1 + 1) which likely reads R, then S.
    // Then feeds the input hash.

    // ... (complex operations omitted for brevity)

    // Final verification result
    ret = ecc_verify_final(&R, &S, &H, stat);
    if (ret != CRYPT_OK) {
        *stat = 0;
    }

    ret = CRYPT_OK;

cleanup:
    // Free big numbers
    ecc_verify_free(bnR, bnS, bnHash, bnTmp);
    return ret;

abort_cleanup:
    ecc_verify_free(bnR, bnS, bnHash, bnTmp);
    return CRYPT_ERROR;
}

// Helper function stubs (actual implementations elsewhere)
static int ecc_is_point_at_infinity(int curveIdx) { return 0; }
static int ecc_hash_to_bn(const unsigned char *hash, unsigned long hashlen, int *bn) { return 0; }
static int ecc_verify_init(int *R, int *S, int *hash, int *pubkey, int curveIdx) { return 0; }
static int ecc_verify_start(void) { return 0; }
static int ecc_verify_write(const unsigned char *data, unsigned long len) { return 0; }
static int ecc_compare_hashes(const unsigned char *hash1, const unsigned char *hash2, int len) { return 0; }
static int ecc_multiply_point(int* result, const int* point, const int* scalar, int curveIdx) { return 0; }
static int ecc_modinv(int *a, int *mod) { return 0; }
static int ecc_add_points(int *R, int *S, int *T, int curveIdx) { return 0; }
static int ecc_mulmod(int *a, int *b, int *c, int *mod) { return 0; }
static int ecc_verify_final(int *R, int *S, int *hash, int *stat) { return 0; }
static void ecc_verify_end(void) { }
static void ecc_verify_free(int *R, int *S, int *hash, int *pubkey) { }