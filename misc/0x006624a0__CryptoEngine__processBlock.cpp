// FUNC_NAME: CryptoEngine::processBlock
// Address: 0x006624a0
// Role: Core cryptographic block processing function (likely AES/block cipher)
// Takes a context pointer (param_1) and operates on three 16-byte buffers.
// Returns 0 on success, or an error code from a lookup table, defaulting to 1.

int CryptoEngine::processBlock(CryptoContext* context) {
    byte bufA[16];  // +0x00 first buffer
    byte bufB[16];  // +0x10 second buffer
    byte bufC[16];  // +0x20 third buffer

    // Attempt a fast-path initialization with 0 param
    int result = FUN_00667820(bufA, bufB, bufC, 0);
    if (result != 0) {
        // Error code lookup table (3 entries)
        static const int errorCodes[] = { 0x00e2747c, 0x00e2747c+8, 0x00e2747c+16 };
        static const int errorResults[] = { *(int*)0x00e27480, *(int*)0x00e27488, *(int*)0x00e27490 };
        for (int i = 0; i < 3; i++) {
            if (result == errorCodes[i]) {
                return errorResults[i];
            }
        }
        return 1; // default error
    }

    // Main processing chain
    result = FUN_00668da0(context + 0x10, bufB);          // Use context field at +0x10
    if (result != 0) goto error;
    result = FUN_00667910();
    if (result != 0) goto error;
    result = FUN_0066a660(context, bufA);
    if (result != 0) goto error;
    result = FUN_0066a090(bufA);
    if (result != 0) goto error;
    result = FUN_00668f50(bufA, 3, bufA);
    if (result != 0) goto error;
    result = FUN_0066a7f0(bufA, 3, bufA);
    if (result != 0) goto error;
    result = FUN_00665c00();
    if (result == -1) {
        result = FUN_006657c0(bufA);
        if (result != 0) goto error;
    }
    result = FUN_00668ce0(bufA, bufB, bufA);
    if (result != 0) goto error;
    result = FUN_0066a090(bufA);
    if (result != 0) goto error;
    result = FUN_0066a660(bufA, bufC);
    if (result != 0) goto error;
    result = FUN_0066a090(bufC);
    if (result != 0) goto error;
    result = FUN_0066a780(bufC, context);
    if (result != 0) goto error;
    result = FUN_0066a8d0(bufC, context);
    if (result != 0) goto error;
    result = FUN_0066a780(context, bufC);
    if (result != 0) goto error;
    result = FUN_00668ce0(bufB, bufA, bufB);
    if (result != 0) goto error;
    result = FUN_0066a8d0(bufB, context + 0x10);
    if (result != 0) goto error;
    result = FUN_00665ce0();
    if (result == 0) {
        FUN_00665b80(bufC, bufB, bufA, 0);
        return 0;
    }

error:
    // Error code lookup and default
    {
        static const int errorCodes[] = { 0x00e2747c, 0x00e2747c+8, 0x00e2747c+16 };
        static const int errorResults[] = { *(int*)0x00e27480, *(int*)0x00e27488, *(int*)0x00e27490 };
        for (int i = 0; i < 3; i++) {
            if (result == errorCodes[i]) {
                int ret = errorResults[i];
                FUN_00665b80(bufC, bufB, bufA, 0);
                return ret;
            }
        }
    }
    FUN_00665b80(bufC, bufB, bufA, 0);
    return 1;
}