// FUNC_NAME: yarrow_read (from libtomcrypt)
// Address: 0x00662350
// Role: Reads random bytes from Yarrow PRNG state. Returns number of bytes read (0 on failure).

#include <cstring> // for memset

// Forward declaration of internal prng read function (likely in same library)
extern uint prng_read(void* buf, uint len); // FUN_00664ad0

// Error printing helper (simplified)
static void _ARGCHK_fail(const char* cond, int line, const char* file) {
    // Internally calls fprintf(stderr,...) but omitted for brevity.
    // The original code used FUN_00b995f7 and fprintf, but we just note the logic.
}

uint yarrow_read(void* buf, uint len, void* prng) {
    // Validate parameters
    if (buf == nullptr) {
        // Line 0x8e from yarrow.c: "buf != NULL"
        _ARGCHK_fail("buf != NULL", 0x8e, "..\\src\\libtomcrypt\\yarrow.c");
    }
    if (prng == nullptr) {
        // Line 0x8f from yarrow.c: "prng != NULL"
        _ARGCHK_fail("prng != NULL", 0x8f, "..\\src\\libtomcrypt\\yarrow.c");
    }
    if (buf == nullptr) {
        // Line 6 from mem.c: "dst != NULL" (duplicate check, possibly due to macro)
        _ARGCHK_fail("dst != NULL", 6, "..\\src\\libtomcrypt\\mem.c");
    }

    // Zero the buffer if requested length is non-zero
    if (len != 0) {
        memset(buf, 0, len);
    }

    // Call the actual PRNG read function
    int result = prng_read(buf, len); // returns 0 on success, non-zero on error

    // Return len on success, 0 on error
    return (result == 0) ? len : 0;
}