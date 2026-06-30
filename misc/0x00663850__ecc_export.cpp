// FUNC_NAME: ecc_export
// Function address: 0x00663850
// Role: Export an ECC public or private key into a binary format (libtomcrypt ecc_export)
// Source: ..\src\libtomcrypt\ecc.c

#include <cstring> // for memcpy

// Forward declarations of libtomcrypt internal functions
int ecc_get_size(void); // FUN_0066b910 - returns size of ECC key in bytes
int mp_init(void* mp); // FUN_0066a970 - initialize a multi-precision integer
int mp_read_unsigned_bin(void* mp, unsigned int* bin, int len); // FUN_006634b0 - read binary into mp_int
void zeromem(void* mem, int size); // FUN_0066c9b0 - zero memory

// ECC key structure (inferred from offsets)
struct ecc_key {
    int type;          // +0x00: key type (0=private, 1=public)
    int idx;           // +0x04: curve index
    unsigned char pubkey[32]; // +0x08: public key mp_int (size assumed 32 bytes)
    unsigned char privkey[32]; // +0x28: private key mp_int (size assumed 32 bytes)
};

// Error codes (positive, custom mapping)
#define CRYPT_OK         0
#define CRYPT_ERROR      1
#define CRYPT_INVALID_ARG 0x0E
#define CRYPT_MEM        0x0D
#define CRYPT_BUFFER_OVERFLOW 6

// Debug assertion macro (simplified)
#define ARGCHK(cond, msg, line, file) \
    if (!(cond)) { \
        int dbg = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n", msg, line, file); \
        fprintf((FILE*)(dbg + 0x40), "_ARGCHK '%s' failure on line %d of file %s\n", msg, line, file); \
    }

int ecc_export(void* out, unsigned int* outlen, int type, ecc_key* key)
{
    int err;
    int size;
    int privSize;
    unsigned int needed;
    unsigned char buf[4]; // temporary buffer for header
    unsigned char exportBuf[512]; // stack buffer for exported data (size estimated)

    // Argument validation
    ARGCHK(out != NULL, "out != NULL", 0x316, "..\\src\\libtomcrypt\\ecc.c");
    ARGCHK(outlen != NULL, "outlen != NULL", 0x317, "..\\src\\libtomcrypt\\ecc.c");
    ARGCHK(key != NULL, "key != NULL", 0x318, "..\\src\\libtomcrypt\\ecc.c");

    // If key type is not set and we are exporting public key, error
    if (key->type != 0 && type == 0) {
        return CRYPT_INVALID_ARG;
    }

    // Build export header
    // local_1ff = curve OID byte from lookup table (indexed by key->idx * 7)
    exportBuf[0] = *(unsigned char*)(&DAT_00e279c0 + key->idx * 7); // curve identifier
    exportBuf[1] = (unsigned char)type; // key type (0=private, 1=public)

    // Get size of ECC key (in bytes)
    size = ecc_get_size();
    exportBuf[2] = (unsigned char)size; // store size byte? Actually local_1fe is int, but stored as byte? The code does local_1fe = size; then later (&local_1fa)[size] = ... That suggests the size is used as an offset. We'll follow the original logic.

    // Initialize the public key mp_int and read from key->pubkey
    err = mp_init(key->pubkey);
    if (err != CRYPT_OK) {
        return CRYPT_MEM;
    }

    // Read the public key binary into the mp_int (size is from local_208)
    unsigned int pubKeySize = 0;
    err = mp_read_unsigned_bin(key->pubkey, &pubKeySize, 0); // Actually the second param is a pointer to size? The decompiled shows &local_208 as second arg.
    if (err != CRYPT_OK) {
        return CRYPT_MEM;
    }

    // Store the public key size byte at offset (size + 3) in export buffer
    exportBuf[size + 3] = (unsigned char)pubKeySize;

    // Calculate total needed size
    needed = size + 11; // base header + public key data

    if (type == 0) {
        // Private key export: include private key
        privSize = ecc_get_size();
        // Store private key size at offset (size + 4) in the stack area? Actually the code does:
        // *(int *)((int)aiStack_1f9 + size) = privSize; // This is storing into the stack buffer at offset size
        // We'll use exportBuf for simplicity, but the original uses a separate stack area.
        // For reconstruction, we'll store it in exportBuf at offset size (but careful with alignment)
        *(int*)(exportBuf + size) = privSize;

        err = mp_init(key->privkey);
        if (err != CRYPT_OK) {
            return CRYPT_MEM;
        }
        needed = size + 15 + privSize; // additional header + private key data
    }

    // Check if output buffer is large enough
    if (*outlen < needed) {
        return CRYPT_BUFFER_OVERFLOW;
    }

    // Zero memory (maybe for security)
    zeromem(0, 0); // The original calls zeromem(0) - likely a bug or placeholder

    // Copy the export buffer to output
    memcpy(out, exportBuf, needed);
    *outlen = needed;

    return CRYPT_OK;
}