// FUNC_NAME: initStateAndConfig
// Function address: 0x0068c5b0
// Role: Initializes a configuration structure from a global default and sets a state field to 2 (active?).
// Known pattern: Often used in EA EARS engine classes to set a default state and configuration.

#include <cstdint>

// Global data from DAT_01129a98 (likely a default config pointer or constant)
extern int32_t gDefaultConfig;

// Unknown initialization function at 0x00408a00
// Takes a pointer to a temporary struct and an integer parameter (0 in this call)
extern void initConfigStruct(void* config, int32_t param);

// Reconstructed member function
void __thiscall initStateAndConfig(void* this_ptr)
{
    // Temporary stack structure (size unknown, likely a config or options struct)
    struct TempConfig {
        int32_t field0;   // +0x00: from global default
        int32_t field4;   // +0x04: always 0
        int8_t  field8;   // +0x08: always 0 (padding or boolean)
    } config;

    config.field0 = gDefaultConfig;
    config.field4 = 0;
    config.field8 = 0;

    // Initialize with the constructed config and a zero parameter
    initConfigStruct(&config, 0);

    // Set state at +0x10 to 2 (likely "active" or "ready")
    *(int32_t*)((uint8_t*)this_ptr + 0x10) = 2;

    return;
}