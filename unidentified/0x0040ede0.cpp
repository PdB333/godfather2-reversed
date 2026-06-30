// 0x0040ede0 - GetDebugCommandRegistry
// Ghidra reconstruction of the lazy initializer for a shared debug/cheat command
// registry used by the game's debug menu code.
//
// The binary uses a one-time initialization flag, clears several global state slots,
// marks the subsystem as active, registers a shutdown handler with atexit, and then
// returns the base address of the registry storage block.

#include <cstdint>
#include <cstdlib>

// x86 layout inferred from callers:
// - 32 pointer-sized command slots at offsets 0x00..0x7C
// - command count at offset 0x80
struct DebugCommandRegistry
{
    std::uint32_t commandSlots[32];
    std::uint32_t commandCount;
};

extern "C" {
    // One-time initialization guard.
    extern std::uint32_t DAT_01223a78;

    // Internal state cleared during first-time setup.
    extern std::uint32_t DAT_01223a48;
    extern std::uint32_t DAT_01223a4c;
    extern std::uint32_t DAT_01223a50;
    extern std::uint32_t DAT_01223a58;
    extern std::uint32_t DAT_01223a60;
    extern std::uint32_t DAT_01223a68;
    extern std::uint32_t DAT_01223a70;

    // Subsystem enabled flag observed being set to 1 during initialization.
    extern std::uint8_t DAT_01205249;

    // Exit-time cleanup routine registered on the first call.
    void DAT_00d50170(void);

    // Base storage for the registry object returned to callers.
    extern std::uint8_t DAT_012239c8;
}

DebugCommandRegistry* GetDebugCommandRegistry(void)
{
    // Only perform the expensive setup once.
    if ((DAT_01223a78 & 1u) == 0u) {
        DAT_01223a78 |= 1u;

        // Reset the registry's companion state. The exact meaning of these fields
        // is not exposed by the decompilation, but they are consistently zeroed
        // before the debug command list is populated.
        DAT_01223a48 = 0;
        DAT_01205249 = 1;
        DAT_01223a4c = 0;
        DAT_01223a50 = 0;
        DAT_01223a58 = 0;
        DAT_01223a60 = 0;
        DAT_01223a68 = 0;
        DAT_01223a70 = 0;

        // Match the original binary's shutdown registration.
        std::atexit(DAT_00d50170);
    }

    // Return the shared registry block that callers append commands into.
    return reinterpret_cast<DebugCommandRegistry*>(&DAT_012239c8);
}
