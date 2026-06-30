// FUNC_NAME: InitializeGameGlobal
// Address: 0x00494830
// Purpose: Initializes the global game state structure (singleton) by setting its vtable pointer, zeroing various fields, and returning a pointer to it.
// Structure fields (offsets relative to base at 0x01215e60):
//   +0x000: vtable pointer
//   +0x2D0: unknown (int32)
//   +0x2D4: unknown (int32)
//   +0x2E0: unknown buffer (64 bytes)
//   +0x320: unknown (int32)
//   +0x330: unknown (16-byte array)
//   +0x340: unknown (int32)
//   +0x350: unknown (16-byte array)

#include <cstring>

// Forward declaration of the global data structure
struct GameGlobalData;

// External globals (defined elsewhere with fixed addresses)
extern GameGlobalData g_GameGlobal; // at 0x01215e60
extern void InitSubsystem(); // FUN_00492030

extern const void* g_VTable; // PTR_LAB_00e34e90

// The reconstructed function
GameGlobalData* InitializeGameGlobal()
{
    // Call subsystem initialization
    InitSubsystem();

    // Set vtable pointer
    g_GameGlobal.vtable = &g_VTable;

    // Zero out fields
    g_GameGlobal.field_0x2D0 = 0;
    g_GameGlobal.field_0x2D4 = 0;
    g_GameGlobal.field_0x320 = 0;
    g_GameGlobal.field_0x340 = 0;

    // Zero out 64-byte buffer at +0x2E0
    memset(&g_GameGlobal.buffer_0x2E0, 0, 0x40);

    // Zero out 16-byte arrays
    memset(&g_GameGlobal.array_0x330, 0, 16);
    memset(&g_GameGlobal.array_0x350, 0, 16);

    // Return pointer to the global instance
    return &g_GameGlobal;
}

// Definition of the global structure (layout matches memory offsets)
struct GameGlobalData {
    const void* vtable;          // +0x000
    // Pad or other fields up to +0x2D0
    char pad_0x004[0x2D0 - 0x004];
    int32_t field_0x2D0;         // +0x2D0
    int32_t field_0x2D4;         // +0x2D4
    // Pad to +0x2E0
    char pad_0x2D8[0x2E0 - 0x2D8];
    uint8_t buffer_0x2E0[0x40]; // +0x2E0, 64 bytes
    // Pad to +0x320
    char pad_0x320[0x320 - (0x2E0 + 0x40)];
    int32_t field_0x320;         // +0x320
    // Pad to +0x330
    char pad_0x324[0x330 - 0x324];
    uint8_t array_0x330[16];    // +0x330, 16 bytes
    // Pad to +0x340
    char pad_0x340[0x340 - (0x330 + 16)];
    int32_t field_0x340;         // +0x340
    // Pad to +0x350
    char pad_0x344[0x350 - 0x344];
    uint8_t array_0x350[16];    // +0x350, 16 bytes
};

// Define the actual global instance
extern GameGlobalData g_GameGlobal; // placed at 0x01215e60

// Dummy external functions for compilation
void InitSubsystem() {} // placeholder for FUN_00492030
const void* g_VTable = nullptr; // placeholder for PTR_LAB_00e34e90