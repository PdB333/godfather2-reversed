// FUNC_NAME: prngRead
// Address: 0x006622a0
// Role: PRNG read function (Yarrow implementation) – validates state and generates random bytes via descriptor tables.
#include <cstdio>
#include <cstdint>

// Forward declarations for external functions and global descriptor tables
extern int FUN_00b995f7(const char* fmt, ...);   // debug printf
extern int _fprintf(FILE* stream, const char* format, ...);

// Descriptor tables (defined in the libtomcrypt PRNG module)
extern uint8_t  DAT_01206008[];  // PRNG ready flags? (8‑byte stride)
extern uint8_t  DAT_01205a88[];  // Cipher descriptor existence flags? (11‑byte stride)
extern uint32_t* DAT_01206010[]; // Pointers to internal PRNG/cipher states (32‑byte stride)
extern void*    DAT_01205ab0[];  // Function pointers for cipher operations (44‑byte stride)

// Underlying PRNG output generation
int FUN_006649b0(uint cipherIdx, void* out, void* outlen, void* state);

int prngRead(uint* param_1)
{
    uint* prngState = param_1;
    if (prngState == nullptr)
    {
        const char* format = "_ARGCHK '%s' failure on line %d of file %s\n";
        int iVar4 = FUN_00b995f7(format, "prng != NULL", 0x72, "..\\src\\libtomcrypt\\yarrow.c");
        _fprintf(reinterpret_cast<FILE*>(iVar4 + 0x40), format);
    }

    // +0x04: PRNG ready flag (or secondary index)
    uint uVar1 = prngState[1];
    if ((uVar1 < 0x20) && (DAT_01206008[uVar1 * 8] != 0))
    {
        // +0x00: PRNG descriptor index
        uint uVar2 = *prngState;
        if ((uVar2 < 0x20) && (DAT_01205a88[uVar2 * 11] != 0))
        {
            // Get internal cipher state pointer from the PRNG descriptor
            uint* innerState = *(uint**)(&DAT_01206010 + uVar1 * 0x20);
            // Call the cipher setup/encrypt function from the cipher descriptor
            int result = (*(int(**)(void*))(&DAT_01205ab0 + uVar2 * 0x2c))(&innerState);
            if (result == 0)
            {
                // Call the actual PRNG output generation
                result = FUN_006649b0(*prngState, prngState + 2, prngState + 2, innerState);
            }
            return result;
        }
        return 10; // CRYPT_INVALID_KEYSIZE equivalent
    }
    return 11; // CRYPT_FAIL_TESTVECTOR equivalent
}