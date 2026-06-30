// FUNC_NAME: SlotManager::initialize
// Function at 0x0053d680 - Initializes the singleton slot manager.
// Clears 54 slot structures (each 0x6C bytes), sets internal pointer to static table, and returns address of pointer member.
#include <cstdint>

// Forward declaration of an initialization function
extern void systemInit_FUN_006126d0();

// SlotManager static members (global variables)
namespace SlotManager
{
    // +0x00: Pointer to static vtable/table (actually a pointer to a function table)
    static uint32_t* s_pVTable = nullptr;
    // +0x04: Array of 54 slots, each 0x6C bytes (offset 0x01198e80)
    static uint8_t s_slotArray[54 * 0x6C];
    // +0x??: Slot count or initialization flag (offset 0x0121bf2c)
    static int32_t s_slotCount;
}

// Static table located at 0x00e390a8 (provided by linker)
extern uint32_t g_SlotManagerStaticTable[];

uint32_t* SlotManager::initialize()
{
    systemInit_FUN_006126d0();

    // Set the pointer to the static table
    SlotManager::s_pVTable = g_SlotManagerStaticTable;

    // Clear all slots (zero-fill each 0x6C byte block)
    uint32_t offset = 0;
    do
    {
        // Clear one slot by zeroing its first 4 bytes (uint32_t)
        *(uint32_t*)(SlotManager::s_slotArray + offset) = 0;
        offset += 0x6C;
    } while (offset < 0x1734); // 54 * 0x6C = 0x1734

    // Reset slot count
    SlotManager::s_slotCount = 0;

    // Return address of the static vtable pointer (used as a singleton handle)
    return &SlotManager::s_pVTable;
}