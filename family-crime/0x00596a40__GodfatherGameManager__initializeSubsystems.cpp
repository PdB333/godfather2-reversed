// FUNC_NAME: GodfatherGameManager::initializeSubsystems
// Address: 0x00596a40
// This function initializes global subsystem references and a pool of objects (64 entries of 0x74 bytes each).
// It is likely called once during game startup to set up the core managers.

// Global pointer to the game manager singleton
static GodfatherGameManager* g_pGameManager = nullptr; // DAT_012055a4

// Array of 256 unknown entries (probably handles or flags)
static uint32_t g_unknownArray[0x100]; // DAT_0119c6d0

// Counter or state flag
static int32_t g_someCounter; // DAT_01205594

// Pool with 64 entries, each 0x74 bytes. The label points to offset +4 within the first entry,
// so each entry structure has its first member at offset -4 relative to the label pointer.
// Struct layout (size 0x74):
struct PoolEntry
{
    int32_t subsystemPtr1; // offset -4 relative to label start
    int32_t subsystemPtr2; // offset 0
    int32_t subsystemPtr3; // offset 4
    int32_t subsystemPtr4; // offset 8
    uint8_t unknownData[0x6C]; // rest of the entry
};
static PoolEntry* g_pool = reinterpret_cast<PoolEntry*>(reinterpret_cast<uint8_t*>(&DAT_0119ab90) - 4);
// Actually, the global label DAT_0119ab90 points to g_pool[0].subsystemPtr2

// Forward declaration of the per-entry initializer
void poolEntryInit(); // FUN_005992a0

// Parameter: 'this' pointer to a GodfatherGameManager instance (or similar)
// Offset mapping for the class:
// +0x00: unknown (not used here)
// +0x04: pointer to subsystem A (e.g., input manager)
// +0x08: pointer to subsystem B (e.g., audio manager)
// +0x0C: pointer to subsystem C (e.g., network manager)
// +0x10: pointer to subsystem D (e.g., graphics or physics manager)
void GodfatherGameManager::initializeSubsystems(void* this_ptr)
{
    // Store global singleton reference
    g_pGameManager = static_cast<GodfatherGameManager*>(this_ptr);

    // Release existing subsystem objects if they have been allocated
    if (*(void**)((uint8_t*)this_ptr + 4) != nullptr)
    {
        // Call vtable[1] (second virtual function, likely release or destructor)
        (**(code**)(**(int**)((uint8_t*)this_ptr + 4) + 4))();
        // Note: the function signature is assumed to take two parameters (0x20, 0x20, 0x40) based on original call
        // but the exact parameters may vary; this is an approximation.
    }
    if (*(void**)((uint8_t*)this_ptr + 8) != nullptr)
    {
        (**(code**)(**(int**)((uint8_t*)this_ptr + 8) + 4))();
    }
    if (*(void**)((uint8_t*)this_ptr + 0x0C) != nullptr)
    {
        (**(code**)(**(int**)((uint8_t*)this_ptr + 0x0C) + 4))();
    }
    if (*(void**)((uint8_t*)this_ptr + 0x10) != nullptr)
    {
        (**(code**)(**(int**)((uint8_t*)this_ptr + 0x10) + 4))();
    }

    // Zero out the 256-entry array
    for (int i = 0; i < 0x100; ++i)
    {
        g_unknownArray[i] = 0;
    }

    // Reset the global counter
    g_someCounter = 0;

    // Initialize all 64 pool entries
    // The pointer `poolEntryPtr` initially points to g_pool[0].subsystemPtr2 (i.e., offset +4 within first entry)
    PoolEntry* currentEntry = reinterpret_cast<PoolEntry*>(&DAT_0119ab90);
    while (reinterpret_cast<uint8_t*>(currentEntry) < reinterpret_cast<uint8_t*>(&DAT_0119c890)) // 0x119c890 is end of pool+4?
    {
        // Call the per-entry initializer (likely generates or resets the unknown data)
        poolEntryInit();

        // Fill the four subsystem pointers from the main object
        // Note: currentEntry[-1] corresponds to entry->subsystemPtr1
        //       currentEntry[0]  -> entry->subsystemPtr2
        //       currentEntry[1]  -> entry->subsystemPtr3
        //       currentEntry[2]  -> entry->subsystemPtr4
        currentEntry[-1] = *(int32_t*)((uint8_t*)this_ptr + 4);  // subsystem A pointer
        *currentEntry      = *(int32_t*)((uint8_t*)this_ptr + 0x10); // subsystem D pointer
        currentEntry[1]    = *(int32_t*)((uint8_t*)this_ptr + 0x0C); // subsystem C pointer
        currentEntry[2]    = *(int32_t*)((uint8_t*)this_ptr + 8);    // subsystem B pointer

        // Move to the next entry (0x74 bytes forward)
        currentEntry = reinterpret_cast<PoolEntry*>(reinterpret_cast<uint8_t*>(currentEntry) + 0x74);
    }
}