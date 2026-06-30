// FUNC_NAME: eccProcessPoint
// Function address: 0x00663680
// Role: ECC point processing using libtomcrypt (ecec.c) - likely scalar multiplication or verification
// Parameters:
//   curveIdx: index (passed in EAX) to select curve parameters from global table
//   pt: pointer to ecc_point (non-null checked)
//   flag: if 0 performs one final step, else another (compress/decompress/convert)
// Returns 0 on success, 0xd (CRYPT_ERROR) on failure

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations of internal functions (mapped from Ghidra labels)
int mpInitMulti(void* a, void* b, void* c, int dummy);      // FUN_00667820
int mpReadRadix(const char* str, int radix);                 // FUN_00669f00
int mpSetInt(void* mp, int value);                           // FUN_006669a0
int eccCopyPoint(void* src, int offset, void* dst);          // FUN_00668f50
int mpInvMod(void* a, void* b, void* c);                     // FUN_0066a780
int mpIsZero(void* mp);                                      // FUN_006657c0
int mpSubMod(void* a, void* b, void* c, void* d);           // FUN_00668850
int mpMulMod(void* a, int exp, void* b, void* c);            // FUN_00665820
void mpClear(void* mp);                                      // FUN_00666240
int eccMulPoint(void* P, void* k, void* R, void* curve);    // FUN_00666ae0
int eccDecompressPoint(void* R);                             // FUN_00665ce0 (when flag==0)
int eccInvertPoint(void* R);                                 // FUN_00665ce0? Actually different, here it's another call
// Note: The final call is either FUN_00665ce0 or FUN_0066a780 (mpInvMod) depending on flag

// Curve parameter strings (indexed by curveIdx * 7)
extern const char* eccPrimeStr[];    // +0x00e279cc (first table)
extern const char* eccOrderStr[];    // +0x00e279c8 (second table)

int eccProcessPoint(int curveIdx, void* pt, int flag) {
    void* tmp1; // local_34 (16 bytes, mp_int)
    void* tmp2; // local_24 (16 bytes, mp_int)
    void* tmp3; // local_14 (20 bytes, mp_int)
    int result;

    // Validate input point
    if (pt == 0) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n",
                "pt != NULL", 0x2c5, "..\\src\\libtomcrypt\\ecc.c");
    }

    // Initialize temporary mp_ints
    result = mpInitMulti(tmp1, tmp2, tmp3, 0);
    if (result != 0) {
        return 0xd; // CRYPT_ERROR
    }

    // Read curve prime parameter from table (7th entry: prime)
    result = mpReadRadix(eccPrimeStr[curveIdx * 7], 16); // 0x40 = 64 decimal? Actually 0x40=64 => radix 64? But typical is base64. Might be radix 16.
    if (result == 0) {
        // Set small constant (likely curve "a" or "b" coefficient)
        result = mpSetInt(pt, 3); // param_1 points to existing point?
    }
    if (result == 0) {
        // Copy point from source (offset 3 into pt? Actually param_1 is pt, offset 3? Strange)
        result = eccCopyPoint(pt, 3, tmp2); 
    }
    if (result != 0) {
        goto cleanup;
    }

    // Convert projective to affine (or compute modular inverse)
    result = mpInvMod(tmp1, tmp2); // tmp1 = tmp1^{-1} mod tmp2?
    if (result != 0) goto cleanup;

    result = mpIsZero(tmp1);
    if (result != 0) goto cleanup;

    // Read another curve parameter: order (second table)
    result = mpReadRadix(eccOrderStr[curveIdx * 7], 0x40);
    if (result != 0) goto cleanup;

    // Subtract modulo
    result = mpSubMod(tmp1, tmp3); // tmp1 = (tmp1 - tmp3) mod something?
    if (result != 0) goto cleanup;

    // Multiply and modulo
    result = mpMulMod(tmp3, 1, tmp2); // tmp3 = tmp3 * 1 mod tmp2? Actually exponent 1 means copy?
    if (result != 0) goto cleanup;

    // Clear temporary
    mpClear(tmp2);
    if (result != 0) goto cleanup;

    // Clear again (redundant?)
    mpClear(tmp2);
    if (result != 0) goto cleanup;

    // Elliptic curve scalar multiplication: R = k * P where k from tmp3, P from tmp2, result in tmp1
    result = eccMulPoint(tmp1, tmp2, tmp3, tmp1); 
    if (result != 0) goto cleanup;

    // Final step based on flag
    if (flag == 0) {
        result = eccDecompressPoint(tmp1); // assuming FUN_00665ce0 decompresses
    } else {
        result = mpInvMod(tmp3, tmp1); // else compute inverse
    }
    if (result != 0) {
        return 0xd;
    }

    // Success
    result = 0;

cleanup:
    mpInitMulti(tmp3, tmp1, tmp2, 0); // FUN_00665b80: likely mp_clear_multi
    return result;
}