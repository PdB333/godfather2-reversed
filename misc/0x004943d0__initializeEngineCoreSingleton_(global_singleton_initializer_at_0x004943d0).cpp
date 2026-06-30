// FUNC_NAME: initializeEngineCoreSingleton (global singleton initializer at 0x004943d0)

#include <cstring>

// Forward declaration of sub-initializer called before setting up the singleton
void initializeCoreSubsystem(); // calls FUN_00490560

// Global singleton – struct placed at fixed address 0x0120ed00 by the linker
struct EngineCoreSingleton {
    // +0x00: vtable pointer (set to &PTR_LAB_00e34d90)
    void* vtable;

    // +0x1C0: unknown int field
    int field_0x1C0;

    // +0x1C4: unknown int field
    int field_0x1C4;

    // Padding to align next fields (unused bytes between 0x1C8 and 0x1D0)
    char _pad_0x1C8[0x1D0 - 0x1C8];

    // +0x1D0: buffer of 64 bytes (zeroed by memset)
    char buffer_0x1D0[0x40];

    // +0x210: unknown int field
    int field_0x210;

    // Padding to align next array at 0x220
    char _pad_0x214[0x220 - 0x214];

    // +0x220: 16‑byte array (zeroed)
    char array_0x220[16];

    // +0x230: unknown int field
    int field_0x230;

    // Padding to align next array at 0x240
    char _pad_0x234[0x240 - 0x234];

    // +0x240: 16‑byte array (zeroed)
    char array_0x240[16];
};

// Global instance declared at the fixed address (represented as a normal variable for reconstruction)
// In the original binary this is placed by the linker at DAT_0120ed00.
EngineCoreSingleton g_engineCoreSingleton;

// ============================================================
// Function: initializeEngineCoreSingleton
// Address:  0x004943d0
// Role:    Sets up the global singleton EngineCoreSingleton (vtable, fields, buffers).
//          Called once during game startup.
// ============================================================
void* initializeEngineCoreSingleton() {
    // Step 1: Call sub‑initializer (likely sets up memory or subsystem prerequisites)
    initializeCoreSubsystem();

    // Step 2: Set the virtual function table pointer to the class's vtable
    g_engineCoreSingleton.vtable = reinterpret_cast<void*>(0x00e34d90);

    // Step 3: Zero out specific fields (offsets +0x1C0, +0x1C4, +0x210, +0x230)
    g_engineCoreSingleton.field_0x1C0 = 0;
    g_engineCoreSingleton.field_0x1C4 = 0;
    g_engineCoreSingleton.field_0x210 = 0;
    g_engineCoreSingleton.field_0x230 = 0;

    // Step 4: Clear the 64‑byte buffer at +0x1D0
    std::memset(g_engineCoreSingleton.buffer_0x1D0, 0, 0x40);

    // Step 5: Clear the two 16‑byte arrays at +0x220 and +0x240
    std::memset(g_engineCoreSingleton.array_0x220, 0, 16);
    std::memset(g_engineCoreSingleton.array_0x240, 0, 16);

    // Return pointer to the singleton (so callers can use it)
    return &g_engineCoreSingleton;
}