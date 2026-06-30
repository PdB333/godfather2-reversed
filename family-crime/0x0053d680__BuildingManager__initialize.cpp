// FUNC_NAME: BuildingManager::initialize
#include <cstdint>
#include <cstring>

// External function called first for generic setup
extern void someEngineInit(); // FUN_006126d0

// Vtable table for BuildingManager class
extern void* VTABLE_BuildingManager; // PTR_LAB_00e390a8

// Global singleton data area
static void* g_buildingVtablePtr;                  // DAT_0121be88
static uint8_t g_buildingSlots[55 * 0x6c];         // DAT_01198e80 (55 entries, each 0x6c bytes)
static int32_t g_buildingInitFlag;                 // _DAT_0121bf2c

// Initializes the BuildingManager singleton. Returns pointer to its vtable pointer.
void* BuildingManager::initialize() {
    someEngineInit();
    
    // Set vtable pointer for this singleton instance
    g_buildingVtablePtr = &VTABLE_BuildingManager;
    
    // Clear the array of building slots (55 entries, each 0x6c = 108 bytes)
    // These slots likely represent building data (e.g., front businesses, rackets)
    for (uint32_t i = 0; i < 55; i++) {
        uint8_t* slot = &g_buildingSlots[i * 0x6c];
        memset(slot, 0, 0x6c);
    }
    
    // Set initialization flag to 0 (ready state)
    g_buildingInitFlag = 0;
    
    // Return the address of the vtable pointer for external use
    return &g_buildingVtablePtr;
}