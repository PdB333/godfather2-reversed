// FUNC_NAME: setCurrentPreset

#include <cstdint>

// Global variables accessed by this function
extern uint64_t gCurrentPresetBase;    // 0x00e50bc4
extern uint64_t gPresetBaseConstant;   // 0x00e50bcc
extern uint64_t gPresetFirstArray;     // 0x00e50bd0 (stride 0x14)
extern uint64_t gPresetSecondArray;    // 0x00e50bd8 (stride 0x14)
extern uint32_t gPresetThirdArray;     // 0x00e50be0 (stride 0x14)

// Copies a 20‑byte preset entry (indexed by slotIndex) into the global preset
void setCurrentPreset(int slotIndex)
{
    // Copy the base constant into the current preset base
    gCurrentPresetBase = gPresetBaseConstant;

    // Load the three fields from the preset table at offset slotIndex * 0x14
    // The structure is: uint64 first + uint64 second + uint32 third = 20 bytes
    gCurrentPresetFirst = *(uint64_t*)((uintptr_t)&gPresetFirstArray + slotIndex * 0x14);
    gCurrentPresetSecond = *(uint64_t*)((uintptr_t)&gPresetSecondArray + slotIndex * 0x14);
    gCurrentPresetThird = *(uint32_t*)((uintptr_t)&gPresetThirdArray + slotIndex * 0x14);
}