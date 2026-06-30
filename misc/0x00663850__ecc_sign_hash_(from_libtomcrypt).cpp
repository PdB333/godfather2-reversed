// FUNC_NAME: ecc_sign_hash (from libtomcrypt)
// Address: 0x00663850
// Role: ECC signature generation (ECDSA) – produces a signature in a custom format
// Sources: libtomcrypt ecc.c, line 0x316-0x318 (ARGCHK)
// Uses: curve table at 0x00e279c0 (7 bytes per curve)
// Parameters:
//   out          - output signature buffer
//   outLen       - [in/out] size of output buffer / actual signature length
//   hashLenOrAlgo - hash length (or algorithm ID byte)
//   key          - ecc_key structure (offset: +0 = type, +1 = curveIdx, +2 = private key point?)

int ecc_sign_hash(void* out, uint* outLen, int hashLenOrAlgo, int* key)
{
    int err;
    int randByteCount;
    int mpStatus;
    uint sigSize;
    char* argMsg;
    uint unknown4; // local_208
    char sigHeader[4]; // local_204 (unknown, possibly version/flag)
    char curveByte;       // local_1ff
    char algoByte;        // local_200
    int randCountInt;     // local_1fe
    // buffer overflow from local_1fa onward (size depends on randByteCount)
    char sigBody[1];      // local_1fa (placeholder, actual size dynamic)
    // Note: local_1fa is the start of the variable-length signature data.
    // The local variables are packed in the actual stack frame.

    unknown4 = 0;

    // Parameter validation (same as libtomcrypt ARGCHK macro)
    if (out == 0) {
        argMsg = "_ARGCHK '%s' failure on line %d of file %s\n";
        err = FUN_00b995f7(argMsg, "out != NULL", 0x316, "..\\src\\libtomcrypt\\ecc.c");
        fprintf((FILE*)(err + 0x40), argMsg);
    }
    if (outLen == 0) {
        argMsg = "_ARGCHK '%s' failure on line %d of file %s\n";
        err = FUN_00b995f7(argMsg, "outlen != NULL", 0x317, "..\\src\\libtomcrypt\\ecc.c");
        fprintf((FILE*)(err + 0x40), argMsg);
    }
    if (key == 0) {
        argMsg = "_ARGCHK '%s' failure on line %d of file %s\n";
        err = FUN_00b995f7(argMsg, "key != NULL", 0x318, "..\\src\\libtomcrypt\\ecc.c");
        fprintf((FILE*)(err + 0x40), argMsg);
    }

    // Check if key is private and hash length is zero (invalid)
    if ((key[0] != 0) && (hashLenOrAlgo == 0)) {
        return 0x0e; // CRYPT_INVALID_ARG
    }

    // Lookup curve descriptor from table (7 bytes per entry)
    // key[1] is the curve index
    curveByte = *(char*)(0x00e279c0 + key[1] * 7);
    algoByte = (char)hashLenOrAlgo;

    // Generate random nonce (number of bytes? or integer?)
    randByteCount = FUN_0066b910(); // likely mp_rand or random byte length
    randCountInt = randByteCount;

    // Validate key's private value (key+2 points to the private scalar)
    mpStatus = FUN_0066a970(key + 2);
    if (mpStatus != 0) {
        return 0x0d; // CRYPT_ERROR
    }

    // Perform ECC point multiplication to get signature component
    // (key+2 is used, result stored in unknown4)
    mpStatus = FUN_006634b0(key + 2, &unknown4);
    if (mpStatus == 0) {
        // Store a byte derived from the multiplication result
        sigBody[randByteCount - 1] = (char)unknown4;

        // Compute total signature size
        sigSize = randByteCount + 0x0b; // base overhead (header + algoByte + curveByte + randCount)

        // If no private key? (this branch seems to handle public-key signature? unusual)
        if (hashLenOrAlgo == 0) {
            int extraRand = FUN_0066b910();
            *(int*)((int)sigBody + randByteCount) = extraRand; // store another random value
            mpStatus = FUN_0066a970(key + 10); // validate something else
            if (mpStatus != 0) {
                return 0x0d;
            }
            sigSize = randByteCount + 0x0f + extraRand; // adjusted size
        }

        // Check output buffer capacity
        if (*outLen < sigSize) {
            return 6; // CRYPT_BUFFER_OVERFLOW
        }

        // Zero memory? (FUN_0066c9b0 likely mp_zero or secure mem wipe)
        FUN_0066c9b0(0);

        // Copy constructed signature to output
        memcpy(out, sigHeader, sigSize);
        *outLen = sigSize;
        err = 0; // CRYPT_OK
    }
    else {
        err = 0x0d; // CRYPT_ERROR
    }

    return err;
}