// FUNC_NAME: DataVerifier::checkAndUpdateSignature
// Function at 0x00992d00: Validates a 20-byte signature against a computed hash, updates outputs on mismatch.
uint32_t DataVerifier::checkAndUpdateSignature(void* thisPtr, int32_t* signatureInOut, uint64_t* extraDataOut, char* isValidFlagOut) {
    char computedIsValid;
    int32_t computedSignature[5];   // 20-byte signature
    uint64_t computedData[2];       // 16-byte extra data
    uint32_t computedExtra;         // extra 32-bit hash fragment

    // Compute signature from internal object state
    FUN_00992740(thisPtr, computedSignature, computedData, &computedIsValid);

    // Check if the input signature matches the computed one (low byte comparison for last int)
    if ((signatureInOut[0] == computedSignature[0]) &&
        (signatureInOut[1] == computedSignature[1]) &&
        (signatureInOut[2] == computedSignature[2]) &&
        (signatureInOut[3] == computedSignature[3]) &&
        ((char)signatureInOut[4] == (char)computedSignature[4])) {

        // Flag also matches
        if (*isValidFlagOut == computedIsValid) {
            // If flag is non-zero, require additional verification
            if (*isValidFlagOut != '\0') {
                if (FUN_00991dc0(&computedData) != '\0') {
                    // Additional verification failed; fall through to update
                    goto UPDATE_OUTPUTS;
                }
            }
            // Everything consistent; no update needed
            return 0;
        }
    }

UPDATE_OUTPUTS:
    // Update output data (two 64-bit values + one 32-bit value)
    // The extraDataOut pointer is actually to a struct: { uint64 data0; uint64 data1; uint32 extra; }
    struct {
        uint64_t data0;
        uint64_t data1;
        uint32_t extra;
    }* outputStruct = (decltype(outputStruct))extraDataOut;

    outputStruct->data0 = computedData[0];
    outputStruct->data1 = computedData[1];
    outputStruct->extra  = computedExtra;

    // Update the signature (full ints, though only low byte was checked)
    for (int i = 0; i < 5; ++i) {
        signatureInOut[i] = computedSignature[i];
    }

    *isValidFlagOut = computedIsValid;
    return 1;
}