// FUNC_NAME: CharacterManager::getCharacterHandle
// Function: 0x00424f20
// Role: Returns a handle for a given character identifier (param_2).
// The handle packs the address of the character's slot data (upper 24 bits) with a validity flag (low byte).
// If the identifier maps to an invalid slot index (>= 4), returns an error handle (index with low byte zeroed).

#include <cstdint>

// Forward declarations
class CharacterManager;

// Size: 0x1d0 (464 bytes)
struct CharacterSlot {
    // +0x88: Array of 12-byte substructures
    // We don't know exact type, but first field is a flag/pointer
    uint8_t pad0[0x88];
    // +0x88: SubArray subArray[]; // each element is 12 bytes
    // +0x118: Index into subArray
    int subArrayIndex; // @ 0x118
    // Remainder of slot data...
};

// Asserts
static_assert(sizeof(CharacterSlot) == 0x1d0, "CharacterSlot size mismatch");

class CharacterManager {
public:
    // +0x10: Array of 4 character slots
    CharacterSlot slots[4]; // @ offset 0x10

    // Helper function: maps an identifier to an index (0-3), else returns >= 4
    static uint32_t mapIdentifierToIndex(uint32_t identifier); // FUN_00424c90

    uint32_t getCharacterHandle(uint32_t identifier) // converted from __thiscall
    {
        uint32_t index = mapIdentifierToIndex(identifier);
        if (index < 4) {
            CharacterSlot* slot = &slots[index];
            // Check if the sub-array element at subArrayIndex is non-zero
            bool isActive = *(uint32_t*)((uint8_t*)slot + 0x88 + slot->subArrayIndex * 0xc) != 0;
            // Pack address (clearing low byte) and status flag into return value
            uint32_t handle = (reinterpret_cast<uint32_t>(slot) & 0xFFFFFF00) | (isActive ? 1 : 0);
            return handle;
        }
        // Return error handle: original index with low byte zeroed
        return index & 0xFFFFFF00;
    }
};