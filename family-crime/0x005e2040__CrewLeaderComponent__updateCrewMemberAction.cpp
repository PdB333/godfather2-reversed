// FUNC_NAME: CrewLeaderComponent::updateCrewMemberAction

#include <cstdint>

// Forward declarations
uint32_t __thiscall FUN_005dbc10(void);
void __thiscall FUN_005e9440(void);
void __thiscall FUN_005e86e0(void);

// Global constant from data segment
extern const float DAT_00e2b05c;

// Size of each crew member slot
const uint32_t CREW_SLOT_SIZE = 0x4A4; // 1188 bytes

// Flags for return value
const uint32_t RETURN_FLAG_FOUND = 1;
const uint32_t RETURN_FLAG_TIMER_CLEARED = 0x100; // Example

uint32_t __thiscall CrewLeaderComponent::updateCrewMemberAction(int thisPtr, int targetId)
{
    float fVar1;
    uint32_t index;
    int* slotIdPtr;

    // Check global state (e.g., manager initialization)
    if (FUN_005dbc10() == 0) {
        return 0;
    }

    // Check if the slot at index 4 (the last crew member slot) is active
    // Offset 0x1744 is within the 5th slot (slot 4) – likely an "active" flag at slot offset 0x24
    if (*(char*)(thisPtr + 0x1744) == '\0' || targetId == 0) {
        return 0;
    }

    // Search for targetId among the 5 crew member slots
    // Slot ID array starts at this+0x490, each slot is 0x4A4 bytes, ID is first int
    slotIdPtr = (int*)(thisPtr + 0x490);
    for (index = 0; index < 5; ++index)
    {
        if (targetId == *slotIdPtr)
        {
            // Found the slot – compute pointer to the slot's data region
            // The data region starts at offset 4 within the slot (skipping the ID)
            int slotDataPtr = index * CREW_SLOT_SIZE + 4 + thisPtr;

            FUN_005e9440(); // Initialize or update the slot? (unknown)

            fVar1 = *(float*)(targetId + 4); // Float from the target's structure – e.g., a timer value

            // Compare target's float with a global sentinel (e.g., INFINITY or -1)
            // This builds a status byte using comparison flags
            uint8_t statusByte = 0;
            if (fVar1 == DAT_00e2b05c) {
                // If equal, clear two timer fields at slot offset 0x1FC and 0x200
                FUN_005e86e0(); // Reset timer? (first)
                FUN_005e86e0(); // Reset timer? (second)
                *(uint32_t*)(slotDataPtr + 0x1FC) = 0;
                *(uint32_t*)(slotDataPtr + 0x200) = 0;
                statusByte = 0;
            } else {
                // Build status from comparison (fVar1 < DAT_00e2b05c, NaN, etc.)
                statusByte = (fVar1 == DAT_00e2b05c) << 6 |
                             (std::isnan(fVar1) || std::isnan(DAT_00e2b05c)) << 2 |
                             2U |
                             (fVar1 < DAT_00e2b05c);
            }

            return ((uint32_t)statusByte << 8) | RETURN_FLAG_FOUND;
        }
        ++slotIdPtr; // Advance by CREW_SLOT_SIZE / sizeof(int) = 0x4A4/4 = 0x129
        slotIdPtr += 0x128; // Actually the decompiler shows increment by 0x129 ints -> same effect
    }

    // Not found – return masked value (e.g., error code)
    return index & 0xFFFFFF00;
}