// Reconstructed from Ghidra export: 0x0040f9c0
//
// Startup helper that toggles the engine's debug-menu gate.
//
// The only known caller is the command-line/bootstrap path at 0x0068d010,
// which passes `1` when the matching launch option is present. The byte is
// later read by the controller/input dispatch code as a global on/off switch.

#include <cstdint>

extern "C"
{
    // Ghidra: DAT_0120524a
    // Inferred as the debug-menu enable flag from startup parsing and the
    // later controller-routing gate in 0x0040fd70.
    extern std::uint8_t g_debugMenuEnabled;
}

// Ghidra: FUN_0040f9c0
extern "C" void __cdecl FUN_0040f9c0(std::uint8_t enabled)
{
    g_debugMenuEnabled = enabled;
}
