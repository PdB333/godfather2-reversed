// FUNC_NAME: ecc_sign_or_verify
// Function address: 0x00663680
// This function appears to be a wrapper for ECC signing or verification from libtomcrypt.
// It uses a global index (in_EAX) to select curve parameters from a table.
// param_1: pointer to an ECC key (or NULL for argument check)
// param_2: flag (0 = sign, non-zero = verify)
// Returns 0 on success, 0xD (13) on failure.

#include <cstdio> // for fprintf

// Forward declarations of internal libtomcrypt functions (renamed for clarity)
int ecc_init(unsigned char hash[16], unsigned char sig[16], unsigned char key[20], int mode);
int ecc_load_key(const char *curveStr, int len);
int ecc_check_key(void *key, int type);
int ecc_export_key(void *key, int type, unsigned char out[16]);
int ecc_import_key(unsigned char in[16], void *key);
int ecc_hash_to_scalar(unsigned char hash[16], unsigned char scalar[16]);
int ecc_mulmod(unsigned char a[16], unsigned char b[16], unsigned char result[16]);
int ecc_addmod(unsigned char a[16], unsigned char b[16], unsigned char result[16]);
int ecc_sign_hash(unsigned char hash[16], unsigned char sig[16], unsigned char key[20], unsigned char nonce[16]);
int ecc_verify_hash(unsigned char sig[16], unsigned char hash[16], unsigned char key[20], int *stat);
void ecc_cleanup(unsigned char a[16], unsigned char b[16], unsigned char c[20], int mode);

// Global tables of curve strings (indexed by in_EAX)
extern const char *g_curveStrings[]; // e.g., "1oUV2vOaSlWbxr6"
extern const char *g_basePointStrings[]; // e.g., "G00000000000000000000000007"

int ecc_sign_or_verify(void *key, int mode)
{
    unsigned char hash[16];
    unsigned char sig[16];
    unsigned char privKey[20];
    int result;
    const char *curveStr;
    const char *baseStr;
    int stat;

    // Argument check (libtomcrypt style)
    if (key == NULL) {
        fprintf(stderr, "_ARGCHK '%s' failure on line %d of file %s\n", "pt != NULL", 0x2C5, "..\\src\\libtomcrypt\\ecc.c");
    }

    // Initialize buffers (likely sets up hash, sig, privKey)
    result = ecc_init(hash, sig, privKey, 0);
    if (result != 0) {
        return 0xD; // CRYPT_ERROR
    }

    // Load curve parameters from global table using in_EAX (register variable)
    // in_EAX is not a parameter; it's likely a global index or passed via register.
    // For reconstruction, we assume it's a global variable.
    extern int g_curveIndex; // in_EAX
    curveStr = g_curveStrings[g_curveIndex * 7];
    result = ecc_load_key(curveStr, 0x40); // 64 bytes
    if (result != 0) {
        goto cleanup;
    }

    // Check key type (3 = private key?)
    result = ecc_check_key(key, 3);
    if (result != 0) {
        goto cleanup;
    }

    // Export key to buffer
    result = ecc_export_key(key, 3, sig);
    if (result != 0) {
        goto cleanup;
    }

    // Hash to scalar conversion
    result = ecc_hash_to_scalar(hash, sig);
    if (result != 0) {
        goto cleanup;
    }

    // Load base point
    baseStr = g_basePointStrings[g_curveIndex * 7];
    result = ecc_load_key(baseStr, 0x40);
    if (result != 0) {
        goto cleanup;
    }

    // Multiply hash with base point
    result = ecc_mulmod(hash, privKey, sig);
    if (result != 0) {
        goto cleanup;
    }

    // Add something (nonce?)
    result = ecc_addmod(sig, 1, hash);
    if (result != 0) {
        goto cleanup;
    }

    // Two more operations (likely double-check)
    result = ecc_mulmod(hash, sig, privKey);
    if (result != 0) {
        goto cleanup;
    }

    result = ecc_mulmod(hash, sig, privKey);
    if (result != 0) {
        goto cleanup;
    }

    // Final operation combining hash, sig, privKey
    result = ecc_addmod(hash, sig, privKey, hash);
    if (result != 0) {
        goto cleanup;
    }

    // Branch based on mode
    if (mode == 0) {
        // Signing path
        result = ecc_sign_hash(hash, sig, privKey, NULL);
    } else {
        // Verification path
        result = ecc_verify_hash(sig, hash, privKey, &stat);
    }

    if (result == 0) {
        return 0; // CRYPT_OK
    }

cleanup:
    ecc_cleanup(privKey, hash, sig, 0);
    return 0xD; // CRYPT_ERROR
}