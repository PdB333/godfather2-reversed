// FUNC_NAME: eccDecryptKey
// Address: 0x006634b0
// Role: Decrypt using ECC with import of private key from base64 string and verification of shared secret.
// Note: This is a reconstructed version from libtomcrypt, likely ecc_decrypt_key or similar.
// Internal functions are given descriptive names based on their role.

int eccDecryptKey(void* prngState, unsigned int* result) {
    char privateKeyBuffer[16];   // Buffer for private key (ecc_key structure)
    char publicKeyBuffer[16];   // Buffer for public key (ecc_key structure)
    char sharedSecretBuffer[20];// Buffer for shared secret and hash

    // Error message function pointer (for ARGCHK macro)
    char* errorMsg = "_ARGCHK '%s' failure on line %d of file %s\n";
    int file; // from fprintf

    // Validate input pointers
    if (prngState == 0) {
        file = FUN_00b995f7(errorMsg, "pt != NULL", 0x29a, "../src/libtomcrypt/ecc.c");
        _fprintf((FILE*)(file + 0x40), errorMsg);
    }
    if (result == 0) {
        file = FUN_00b995f7(errorMsg, "result != NULL", 0x29b, "../src/libtomcrypt/ecc.c");
        _fprintf((FILE*)(file + 0x40), errorMsg);
    }

    // Initialize ECC state (local buffers and internal contexts)
    int initStatus = eccInit(privateKeyBuffer, publicKeyBuffer, sharedSecretBuffer, 0);
    if (initStatus != 0) {
        return 0xd; // CRYPT_ERROR
    }

    // Import private key from base64 string (indexed by some register value)
    int importStatus = eccImportFromBase64((const char*)(&s_1oUV2vOaSlWbxr6_00e279cc[in_EAX * 7]), 0x40);
    if (importStatus != 0) {
        return 0xd;
    }

    // Prepare random number generator (prng) for key generation
    int rngStatus = eccRngReady(prngState, 3);
    if (rngStatus != 0) {
        return 0xd;
    }

    // Generate ECC key pair (using prng, keysize index 3, store public key in publicKeyBuffer)
    int makeKeyStatus = eccMakeKey(prngState, 3, publicKeyBuffer);
    if (makeKeyStatus != 0) {
        return 0xd;
    }

    // Compute shared secret from private key and received public key
    int sharedSecretStatus = eccComputeSharedSecret(privateKeyBuffer, publicKeyBuffer);
    if (sharedSecretStatus != 0) {
        return 0xd;
    }

    // Hash the shared secret
    int hashStatus = eccHash(privateKeyBuffer);
    if (hashStatus != 0) {
        return 0xd;
    }

    // Import second public key from hardcoded base64 string (G000...)
    int importPubStatus = eccImportFromBase64((const char*)(&s_G00000000000000000000000007_00e279c8[in_EAX * 7]), 0x40);
    if (importPubStatus != 0) {
        return 0xd;
    }

    // Export the shared secret to a buffer
    int exportStatus = eccExport(privateKeyBuffer, sharedSecretBuffer);
    if (exportStatus != 0) {
        return 0xd;
    }

    // First encryption/decryption step (possibly sign or encrypt)
    int encStatus1 = eccEncrypt(sharedSecretBuffer, 1, publicKeyBuffer);
    if (encStatus1 != 0) {
        return 0xd;
    }

    // Double hash application (for verification)
    int doubleHashStatus1 = eccDouble(publicKeyBuffer);
    if (doubleHashStatus1 != 0) {
        return 0xd;
    }

    int doubleHashStatus2 = eccDouble(publicKeyBuffer);
    if (doubleHashStatus2 != 0) {
        return 0xd;
    }

    // Final combine and verification step
    int verifyStatus = eccVerify(privateKeyBuffer, publicKeyBuffer, sharedSecretBuffer, privateKeyBuffer);
    if (verifyStatus != 0) {
        return 0xd;
    }

    // Determine result (non-zero means success? Actually function returns 1 if iVar1 != 0)
    int finalCheck = eccFinalCheck();
    *result = (unsigned int)(finalCheck != 0);
    int errorCode = 0;

    eccCleanup(sharedSecretBuffer, privateKeyBuffer, publicKeyBuffer, 0);
    return errorCode;
}