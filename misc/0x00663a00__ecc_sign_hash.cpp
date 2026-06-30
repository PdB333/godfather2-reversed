// FUNC_NAME: ecc_sign_hash
// Address: 0x00663a00
// Role: ECC signature generation from libtomcrypt (ecc.c)
// Handles: input validation, curve lookup, mp_int operations, signature output with key metadata

int ecc_sign_hash(ecc_key *key, unsigned long siglen, unsigned char *sig)
{
    unsigned char *sigPtr;
    int result;
    int curveIndex;
    unsigned int type;
    unsigned int curveCount;
    int *curveTablePtr;
    const char *errorStr;
    int *tablePtr;

    // Validate input pointers
    if (key == (ecc_key *)0x0) {
        errorStr = "_ARGCHK '%s' failure on line %d of file %s\n";
        result = FUN_00b995f7(
            "_ARGCHK '%s' failure on line %d of file %s\n",
            "in != NULL", 0x347, "..\\src\\libtomcrypt\\ecc.c"
        );
        _fprintf((FILE *)(result + 0x40), errorStr);
    }
    if (sig == (unsigned char *)0x0) {
        errorStr = "_ARGCHK '%s' failure on line %d of file %s\n";
        result = FUN_00b995f7(
            "_ARGCHK '%s' failure on line %d of file %s\n",
            "key != NULL", 0x348, "..\\src\\libtomcrypt\\ecc.c"
        );
        _fprintf((FILE *)(result + 0x40), errorStr);
    }

    // Minimum signature size check
    if (siglen < 6) {
        return 7; // CRYPT_INVALID_ARG
    }

    // Initialize PRNG or random number generator
    result = FUN_0066c9f0(0);
    if (result != 0) {
        return result;
    }

    // Initialize multiple precision integers at offsets in signature buffer
    sigPtr = sig + 2; // +0x02: mp_int r
    // sig+6 and sig+10 are also mp_int fields (s, maybe curve order)
    result = FUN_00667820(sigPtr, sig + 6, sig + 10, 0);
    if (result != 0) {
        return 0xd; // CRYPT_MEM
    }

    // Extract key type (0 = ECC_PUBLIC, 1 = ECC_PRIVATE)
    *sig = (unsigned int)*(char *)(key + 4); // key->type

    // Find curve index from key->dp or key->idx
    type = 0;
    if (0x14 < *(char *)(key + 5)) { // key->idx (actually byte? maybe packed)
        curveCount = 0x14;
        do {
            if (curveCount == 0) break;
            type = type + 1;
            curveCount = (&ecc_curve_table)[type * 7]; // curve prime size
        } while (curveCount < *(char *)(key + 5));
    }

    // Validate curve found
    if ((&ecc_curve_table)[type * 7] == 0) {
        result = 3; // CRYPT_ERROR
        goto cleanup;
    }

    // Store curve index in signature
    sig[1] = type;

    // Process based on key type
    if ((*sig == 1) || (*sig == 0)) {
        // Count total curves
        result = 0;
        curveTablePtr = &ecc_curve_table;
        do {
            curveTablePtr = curveTablePtr + 7;
            result = result + 1;
        } while (*curveTablePtr != 0);

        // Check index bounds and signature buffer size
        if (((-1 < (int)type) && ((int)type < result)) && (9 < siglen)) {
            int keySize = *(int *)(key + 6); // key->dp or key->size
            if (keySize + 10U <= siglen) {
                // Read key data from key+10 (public key or private key)
                result = FUN_0066a010(key + 10);
                if ((result == 0) && (result = FUN_0066a620(), result == 0)) {
                    // Perform actual ECC signing
                    result = FUN_00663680(sigPtr, *(undefined1 *)(keySize + 10U + key));
                    if (result != 0) goto cleanup;
                    if (*sig != 0) { // private key
                        goto signComplete;
                    } else {
                        // Public key: need to process additional data
                        type = keySize + 0xf;
                        if ((siglen < type) || (siglen < *(int *)(keySize + 0xb + key) + type))
                            goto insufficientSize;
                        result = FUN_0066a010(type + key);
                        if ((result == 0) && (result = FUN_0066a620(), result == 0))
                            goto signComplete;
                    }
                }
                result = 0xd; // CRYPT_MEM
                goto cleanup;
            }
        }
    }

insufficientSize:
    result = 7; // CRYPT_INVALID_ARG

cleanup:
    // Clear temporary mp_int values
    FUN_00665b80(sigPtr, sig + 6, sig + 10, 0);
    return result;

signComplete:
    // Finalize: if private key, clear sensitive data
    if (*sig == 1) {
        FUN_00665b40(); // mp_clear_multi or ecc_free
    }
    return 0;
}