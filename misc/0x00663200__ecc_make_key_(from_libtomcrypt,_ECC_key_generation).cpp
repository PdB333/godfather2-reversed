// FUNC_NAME: ecc_make_key (from libtomcrypt, ECC key generation)
int __thiscall ecc_make_key(int prngIdx, int wprng, int keysize, ecc_key *key) {
    // ASSERT: key != NULL
    if (key == nullptr) {
        // _ARGCHK failure
        printf("_ARGCHK '%s' failure on line %d of file %s\n", "key != NULL", 0x253, "..\\src\\libtomcrypt\\ecc.c");
    }

    // Validate keysize (index into curve table)
    // DAT_01206408 is an array of 5-byte curve descriptors, indexed by keysize
    if (keysize > 31 || (curveTable[keysize] == 0)) {
        return CRYPT_INVALID_KEYSIZE; // 0xc
    }

    // Find a PRNG with sufficient strength (in_EAX is from prng descriptor strength)
    int prngIndex = 0;
    int prngStrength = 0; // in_EAX is passed implicitly? Actually from calling convention, it might be from prng descriptor
    // The loop uses global array at 0x00e279c0 (7-element entries) to match strength
    if (prngStrength > 20) {
        int maxStrength = 20;
        // search for a PRNG with strength >= prngStrength
        for (int i = 0; ; i++) {
            if (maxStrength == 0) break;
            prngIndex++;
            maxStrength = prngDescTable[prngIndex * 7]; // each entry has 7 ints
            if (maxStrength == 0) break;
        }
    }

    // Get actual strength from found PRNG
    int actualStrength = prngDescTable[prngIndex * 7];
    if (actualStrength == 0) {
        return CRYPT_PRNG_NOT_FOUND; // 3
    }

    key[1] = prngIndex; // store PRNG index in key struct

    // Generate private key by calling PRNG read function
    int result = prngDescTable[keysize * 0x14 + 0x14] // some offset? Actually (DAT_01206418 + keysize*0x14) calls PRNG read
        (local_84, actualStrength, wprng); // local_84 is buffer for private key
    if (result != actualStrength) {
        return CRYPT_ERROR_READ_PRNG; // 9
    }

    // Initialize multiprecision integers for key calculation
    mp_int *a = key + 2;       // param_3+2
    mp_int *b = key + 6;       // param_3+6
    mp_int *c = key + 10;      // param_3+10 (temp for scalar multiplication?)

    if (mp_init_multi(a, b, c, temp1, 0) != CRYPT_OK) {
        goto error;
    }

    // Allocate memory for temporary mp_int
    mp_int *tmp = (mp_int*)malloc(sizeof(mp_int));
    if (tmp == nullptr) {
        mp_clear_multi(a, b, c, temp1);
        return CRYPT_MEM; // 0xd
    }

    if (mp_init_multi(tmp, tmp + 0x10, 0) != CRYPT_OK) {
        free(tmp);
        mp_clear_multi(a, b, c, temp1);
        return CRYPT_MEM;
    }

    // Set curve parameters from global tables - each curve has fixed Gx, Gy, order, etc.
    // PTR_s_G000000... etc. are curve-specific strings/pointers
    if (ecc_set_gx(prngIdx, key[1] /* curve index? no, prngIdx is wrong? Actually param_3[1] stores prngIndex earlier */, 0x40) != CRYPT_OK ||
        ecc_set_gy(prngIdx, key[1], 0x40) != CRYPT_OK ||
        ecc_set_order(prngIdx, key[1], 0x40) != CRYPT_OK) {
        free(tmp);
        mp_clear_multi(tmp, tmp+0x10);
        mp_clear_multi(a, b, c, temp1);
        return CRYPT_INVALID_ARG; // some error
    }

    // Read private key from buffer into mp_int
    if (ecc_read_radix(local_84, privateKey) != CRYPT_OK) {
        // similar cleanup
    }

    // Compute public key: Q = d * G
    if (ecc_mulmod(c, tmp, a, temp1) != CRYPT_OK) {
        // error handling
    }

    key[0] = 0; // set key type to private/public

    // Perform final validation of key (maybe check point on curve)
    if (ecc_verify_key() != CRYPT_OK || ecc_verify_key() != CRYPT_OK || ecc_verify_key() != CRYPT_OK) {
        // errors
    }

    // Success
    result = CRYPT_OK;
    return result;

error:
    // Cleanup and return error code
    mp_clear_multi(a, b, c, temp1);
    return CRYPT_ERROR; // 0xd
}