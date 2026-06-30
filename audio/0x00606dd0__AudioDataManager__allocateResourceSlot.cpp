// FUNC_NAME: AudioDataManager::allocateResourceSlot
// Address: 0x00606dd0
// Allocates a slot in the global resource table (0x38 byte entries, up to 0x1000).
// Returns a handle (slot index) or 0xFFFFFFFF on failure.

struct SlotEntry {
    byte state;          // +0x00: 0=free, 1=allocated, 2=? Only <2 allowed for new allocations
    byte subTypeId;      // +0x01: sub-type or resource type (used when param_5 == 0)
    byte padding[0x36];  // +0x02 to +0x37: rest of structure (0x38 total)
};

// Global table of resource slots
SlotEntry g_slotArray[0x1000]; // address 0x011a0f28

// Forward declarations
uint allocateResourceIndex();    // FUN_00606b50: returns a free slot index or 0xFFFFFFFF
uint allocateResource(uint param_1, uint param_2, uint param_3, uint param_4, uint resourceType, uint slotIndex); // FUN_00606c80

uint __cdecl allocateResourceSlot(uint param_1, uint param_2, uint param_3, uint param_4,
                                   uint resourceType, uint slotIndex, uint param_7, uint param_8)
{
    // Check if resourceType is within valid range (0x1000 slots)
    if (resourceType >= 0x1000) {
        return 0xFFFFFFFF;
    }
    
    // Guard against overflow when computing offset (0x38 * resourceType)
    if (resourceType * 0x38 == (uint)-0x11a0f28) { // -0x11a0f28 = -18455080 (magic overflow check)
        return 0xFFFFFFFF;
    }
    
    // If no explicit slot index given, request a new one
    if (param_8 == 0xFFFFFFFF) {
        param_8 = allocateResourceIndex();
    }
    
    // Validate the new slot index
    if (param_8 >= 0x1000) {
        return 0xFFFFFFFF;
    }
    
    SlotEntry* entry = &g_slotArray[param_8];
    if (entry == nullptr) {
        return 0xFFFFFFFF;
    }
    
    // Slot must be in state < 2 (i.e., free or not fully used)
    if (entry->state >= 2) {
        return 0xFFFFFFFF;
    }
    
    // If resourceType is 0, derive it from the sub-type stored at the resource index
    if (resourceType == 0) {
        // Note: The original code reads from &DAT_011a0f29[param_6 * 0x38]
        // This is offset 1 of slot at index resourceType (which is param_6 in original)
        // That param_6 is actually the 'resourceType' parameter in our reconstruction.
        resourceType = g_slotArray[resourceType].subTypeId; // +0x01
    }
    
    // Proceed to allocate the resource using the resolved parameters
    return allocateResource(param_1, param_2, param_3, param_4, resourceType, param_8);
}