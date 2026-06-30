// Reconstructed from Ghidra export at 0x0040CF60
// Purpose: return the address of the runtime game-root string buffer.
//
// This function is a tiny accessor used by the startup path. The buffer it
// returns is populated earlier by FUN_0040CE40, which reads the EARS_GAMEROOT
// environment variable and writes the resulting path into the global string.

#include <cstdint>

extern "C" {
    // Global NUL-terminated runtime path / configuration string buffer.
    // Ghidra names this as DAT_011625d0 because the original binary has no symbol.
    extern char DAT_011625d0;
}

// Returns a pointer to the first character of the shared runtime string buffer.
// The decompiler showed this as `undefined1 * FUN_0040cf60(void)`.
extern "C" char* GetRuntimeGameRootBuffer()
{
    return &DAT_011625d0;
}

