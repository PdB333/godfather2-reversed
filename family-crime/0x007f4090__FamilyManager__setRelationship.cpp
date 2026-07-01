// FUNC_NAME: FamilyManager::setRelationship
// Address: 0x007f4090
// Sets a bilateral relationship value between two entities (gang members/families) in a triangular matrix.
// The matrix is stored in a global array at DAT_0112c7bf (size 0x50*0x51/2 = 3240 bytes).
// Entities are identified by a byte at offset +0x1F1C (likely a faction or gang ID).
// If either entity has ID 0x50, the operation is skipped (0x50 probably means neutral/invalid).
// The relationship value = (globalStrength * 2) | (flag & 1)

#include <cstdint>

// Global matrix for storing relationship strengths between entity types.
extern uint8_t gRelationshipMatrix[0x50 * (0x50 + 1) / 2]; // 3240 entries

// Global base strength multiplier (set elsewhere, possibly influences all relationships).
extern uint8_t gRelationshipStrengthMultiplier; // DAT_0112c810

class FamilyManager {
public:
    // Sets the relationship between two entities identified by their faction IDs.
    // @param this: FamilyManager instance (may hold additional state)
    // @param otherEntity: Pointer to another entity object (e.g., NPC, Family)
    // @param flag: Additional flags (only LSB is used, OR'd into relationship value)
    void __thiscall setRelationship(void* otherEntity, uint8_t flag) {
        uint8_t thisFaction = *(uint8_t*)((uintptr_t)this + 0x1F1C); // own faction ID
        uint8_t otherFaction = *(uint8_t*)((uintptr_t)otherEntity + 0x1F1C); // other's faction ID

        // Skip if either faction is invalid (0x50 = neutral/unset)
        if (thisFaction == 0x50 || otherFaction == 0x50)
            return;

        // Ensure larger ID is first for symmetric storage (triangular matrix)
        uint8_t idA, idB;
        if (otherFaction < thisFaction) {
            idA = thisFaction;
            idB = otherFaction;
        } else {
            idA = otherFaction;
            idB = thisFaction;
        }

        // Compute index into the triangular matrix: index = idA*(idA+1)/2 + idB
        // The decompiled formula is equivalent to this after rearrangement.
        uint8_t row = idA;
        uint8_t col = idB;
        // Formula from decomp: (uVar3 - ((-uVar4 + 0x4f) * (-uVar4 + 0x50) >> 1)) - uVar4
        // Reproducing exactly for clarity:
        int index = (uint)row - (((0x4f - (uint)col) * (0x50 - (uint)col)) >> 1) - (uint)col;
        // Note: This index formula matches the standard triangular index due to the specific constants.

        // Compute value: baseStrength * 2 OR'ed with LSB of flag
        uint8_t value = (gRelationshipStrengthMultiplier * 2) | (flag & 1);

        gRelationshipMatrix[index] = value;
    }
};