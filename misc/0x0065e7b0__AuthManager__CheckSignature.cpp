// FUNC_NAME: AuthManager::CheckSignature
// Address: 0x0065e7b0
// Role: Verifies a signature using a hash (likely SHA-256) and a key comparison.
// Context: Called from another function (0x0065f330) with ESI = this, EDI = dataProvider.
// Assumes that the calling function sets ESI and EDI before the call (non‑standard calling convention).
// The hash context is 208 bytes large; the final hash is 32 bytes.

// Forward declarations for the hashing and verification functions
// FUN_006595c0: Initialize a hash context (SHA-256 init)
// FUN_00659640: Update the hash with two 32‑bit values (pointer + size or two integers)
// FUN_00659730: Finalize the hash, producing a 32-byte digest
// FUN_00664620: Verify the hash against a stored key and an expected value
void hashInit(void* context);
void hashUpdate(void* context, uint32_t val1, uint32_t val2);
void hashFinal(void* context, void* output);
void hashVerify(void* key, void* hash, int* outResult, uint32_t expected);

// Helper structure for the data provider (EDI)
struct AuthData {
    /* +0x00 */ char unknown[0x0c];
    /* +0x0c */ uint32_t field_0x0c;  // first data word
    /* +0x10 */ uint32_t field_0x10;  // second data word
};

// The method that performs the signature check.
// pData points to an object containing an expected value at offset 0x0c.
bool AuthManager::CheckSignature(AuthData* dataProvider, void* pData) {
    char hashContext[208];          // SHA-256 context (208 bytes)
    char hashOutput[32];            // Final hash digest (32 bytes)
    int verificationResult = 0;     // Output from the verification call

    // Initialize the hash context
    hashInit(hashContext);

    // Update the hash with the two 32-bit values from the data provider
    hashUpdate(hashContext,
               dataProvider->field_0x0c,
               dataProvider->field_0x10);

    // Finalize the hash and obtain the 32-byte digest
    hashFinal(hashContext, hashOutput);

    // Verify the hash using the key stored at this+0x10 and the expected value from pData+0x0c.
    hashVerify(*(void**)((char*)this + 0x10),
               hashOutput,
               &verificationResult,
               *(uint32_t*)((char*)pData + 0x0c));

    // Return true if verification succeeded (result != 0)
    return verificationResult != 0;
}