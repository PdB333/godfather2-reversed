// FUNC_NAME: GameStartup::initialize
// Address: 0x008439c0
// Role: One-time initialization of startup state for a game system.
// Checks a flag (bit 4) at offset 0x4c to prevent re‑initialization.
// On first call: clears a global flag, copies a default config struct,
// sets a wait time, sets a start mode, branches on the global flag,
// logs a debug string, finalizes, and sets the initialized flag.

#include <cstdint>

// Global state
extern uint8_t g_initComplete;       // DAT_0112dcc0
extern int32_t g_defaultConfigValue; // DAT_0112dcd0

// Forward declarations of called functions (guessed names)
void __cdecl FUN_00408a00(void* buffer, int index);
void __cdecl FUN_008431d0(int waitTime);
void __cdecl FUN_008432b0(int startMode);
void __cdecl FUN_00789480(); // success path
void __cdecl FUN_00789450(); // failure path
void __cdecl FUN_004464d0(const char* message);
void __cdecl FUN_0053f8b0(); // finalize

// String constant at LAB_00843810
extern const char LAB_00843810[];

void __thiscall GameStartup::initialize(int thisPtr) {
    // Check if already initialized (bit 4 of flags at offset 0x4c)
    if ((*(uint8_t*)(thisPtr + 0x4c) & 0x10) == 0) {
        // Reset global init complete flag
        g_initComplete = 0;

        // Temporary config buffer (3 ints)
        struct ConfigBuffer {
            int32_t value; // from global default
            int32_t zero1;
            int32_t zero2;
        } config;
        config.value = g_defaultConfigValue;
        config.zero1 = 0;
        config.zero2 = 0;

        // Copy config buffer (likely memcpy or string copy)
        FUN_00408a00(&config, 0);

        // Set initial wait time (e.g., 200 ms)
        FUN_008431d0(200);

        // Set startup mode to 0
        FUN_008432b0(0);

        // Branch based on global flag (may be altered by previous calls)
        if (g_initComplete) {
            FUN_00789480(); // success
        } else {
            FUN_00789450(); // failure
        }

        // Log a debug string (label at 0x00843810)
        FUN_004464d0(&LAB_00843810);

        // Finalize this initialization step
        FUN_0053f8b0();

        // Set the initialized flag (bit 4 at offset 0x4c)
        *(uint32_t*)(thisPtr + 0x4c) |= 0x10;
    }
}