// FUNC_NAME: startupGameSystems
// Address: 0x0067c990
// Role: Initializes core game subsystems and clears a startup flag in a global manager.

#include <cstdint>

// Assuming a global pointer to a manager object, e.g., GameManager
extern uintptr_t g_pManager; // +0x6c: flags field

// Forward declarations of called initialization functions
void FUN_0091ebb0();
void FUN_0068b580(void* buffer, int value);
void FUN_008ec620();
void FUN_0088d640();
void FUN_0067c4f0();
void FUN_00682860();

void startupGameSystems()
{
    // Temporary buffer for initialization data (20 bytes)
    uint8_t initBuffer[20];

    // Call global init
    FUN_0091ebb0();

    // Initialize buffer with zero (likely clears a structure)
    FUN_0068b580(initBuffer, 0);

    // Next subsystem initializations
    FUN_008ec620();
    FUN_0088d640();
    FUN_0067c4f0();
    FUN_00682860();

    // Clear the lowest bit of the flags word at offset +0x6C in the global manager
    // This likely indicates that a certain initialization phase is complete or a lock is released
    *(uint32_t*)(g_pManager + 0x6C) &= ~0x1;
}