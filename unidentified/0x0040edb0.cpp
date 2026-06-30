// 0x0040edb0
// Returns whether the engine is currently in the paused game mode.
//
// The surrounding mode-management code uses mode value 1 for paused, 2 for
// running, and 3 for frozen. This helper is a tiny predicate used by gameplay
// and UI logic to skip simulation work while the game is paused.

#include <cstdint>

extern "C"
{
    // DAT_01205254 in the original binary.
    // Current game-mode selector maintained by the sync helpers in the same
    // subsystem.
    extern std::uint32_t g_CurrentGameMode;
}

// Ghidra: FUN_0040edb0
bool IsGamePaused()
{
    return g_CurrentGameMode == 1;
}
