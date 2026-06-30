// FUNC_NAME: yarrow_read
#include <cstdint>
#include <cstdio>

// From LibTomCrypt, error codes used by Yarrow PRNG
#define CRYPT_OK           0
#define CRYPT_ERROR       10
#define CRYPT_INVALID_ARG 11

// Global tables from libtomcrypt (cipher/hash descriptors)
extern uint8_t  DAT_01206008[];   // Hash descriptor validity flags (8-byte entries)
extern uint8_t  DAT_01205a88[];   // Cipher descriptor validity flags (0xB-byte entries)
extern uint8_t  DAT_01206010[];   // Cipher state pointer table (0x20-byte entries)
extern uint8_t  DAT_01205ab0[];   // Cipher function pointer table (0x2C-byte entries)

// Forward declaration of the actual cipher read function (called internally)
int FUN_006649b0(uint idx, uint* out1, uint* out2, uint* prng);

// Debug assertion helper (prints error to stderr)
extern int  _ARGCHK(const char* format, const char* condition, int line, const char* file);
extern int  fprintf(FILE* stream, const char* format, ...);

int yarrow_read(uint* prng)
{
    uint  idxHash;                  // Index into hash descriptor table
    uint  idxCipher;                // Index into cipher descriptor table
    uint* cipherStatePtr;           // Pointer to cipher state (from global table)
    int   result;                   // Return value

    // Validate argument
    if (prng == nullptr) {
        _ARGCHK("_ARGCHK '%s' failure on line %d of file %s\n",
                "prng != NULL", 0x72, "..\\src\\libtomcrypt\\yarrow.c");
    }

    // Check hash descriptor index (prng[1])
    idxHash = prng[1];
    if ((idxHash < 0x20) && (*(uint64_t*)(DAT_01206008 + idxHash * 8) != 0)) {
        // Check cipher descriptor index (prng[0])
        idxCipher = prng[0];
        if ((idxCipher < 0x20) && (DAT_01205a88[idxCipher * 0xB] != 0)) {
            // Retrieve the cipher state pointer from the global table
            cipherStatePtr = *(uint**)(DAT_01206010 + idxHash * 0x20);

            // Call the cipher's "ready" (or "start") function from the descriptor table
            // Passing the address of the cipher state pointer
            typedef int (*CipherReadyFunc)(uint**);
            CipherReadyFunc readyFunc = *(CipherReadyFunc*)(DAT_01205ab0 + idxCipher * 0x2C);
            result = readyFunc(&cipherStatePtr);

            if (result == CRYPT_OK) {
                // Perform the actual random byte read using the cipher/hash indices
                result = FUN_006649b0(*prng, prng + 2, prng + 2, prng);
            }
            return result;
        }
        // Cipher descriptor not found
        return CRYPT_ERROR;
    }
    // Hash descriptor not found
    return CRYPT_INVALID_ARG;
}