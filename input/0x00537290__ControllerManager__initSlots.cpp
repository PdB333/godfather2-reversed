// FUNC_NAME: ControllerManager::initSlots
// Address: 0x00537290
// Initializes 16 controller slots (each 92 bytes) with a vtable pointer and zeros all fields.
// Also sets a few global flags.

#include <cstdint>
#include <cstring>

// Externally defined vtable pointers (from data sections)
extern void* PTR_FUN_00e38908;  // ControllerManager vtable
extern void* PTR_LAB_00e40d18;  // ControllerSlot vtable

// Global instance pointer (at 0x0121a380)
extern ControllerManager* g_controllerManager;

// Global flags (addresses from decompilation)
extern int32_t g_someFlag1; // at 0x0121b0a4
extern int32_t g_someFlag2; // at 0x0121b0a8
extern int32_t g_someFlag3; // at 0x0121b0ac
extern int32_t g_someFlag4; // at 0x0121b638
extern int32_t g_someFlag5; // at 0x0121b63c

// External base initialization function (likely a memory or engine init)
extern void someBaseInit(); // at 0x006126d0

// The slot structure: 92 bytes, vtable at offset 0
struct ControllerSlot {
    void* vtable;   // +0x00
    uint32_t data[22]; // +0x04 to +0x5C (92 bytes total)
};

// The slot array starts at DAT_0121a380, but the loop indexes using an offset pointer.
// The array is at memory address 0x0121a380, each slot 92 bytes.
#define SLOTS_BASE reinterpret_cast<ControllerSlot*>(0x0121a380)

ControllerManager* ControllerManager::initSlots()
{
    someBaseInit();

    // Set the global manager instance's vtable to PTR_FUN_00e38908.
    // Manager instance starts at 0x0121a380, but by convention we assign via pointer.
    g_controllerManager = reinterpret_cast<ControllerManager*>(0x0121a380);
    g_controllerManager->vtable = &PTR_FUN_00e38908; // assuming vtable at offset 0

    // The loop uses a pointer into each slot at offset 20 (/0x14) from the slot start.
    // That pointer initially points to DAT_0121a438 (which is 0x0121a380 + 0xB8).
    // Each iteration advances by 92 bytes (0x5C) to the next slot's internal pointer.
    // We can simplify by iterating over the slots directly and using memset + vtable set.

    for (int i = 0; i < 16; ++i)
    {
        ControllerSlot& slot = SLOTS_BASE[i];

        // Clear entire slot to zero
        memset(&slot, 0, sizeof(ControllerSlot));

        // Set the vtable pointer (PTR_LAB_00e40d18) at offset 0
        slot.vtable = &PTR_LAB_00e40d18;
    }

    // Set the global flags to zero (as in original)
    g_someFlag1 = 0;
    g_someFlag2 = 0;
    g_someFlag3 = 0;
    g_someFlag4 = 0;
    g_someFlag5 = 0;

    // Return pointer to the manager instance (same as g_controllerManager)
    return reinterpret_cast<ControllerManager*>(0x0121a380);
}